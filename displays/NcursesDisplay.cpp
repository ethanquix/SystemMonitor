//
// Created by szterg_r on 21/01/17.
//

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <wordexp.h>
#include "NcursesDisplay.hpp"
#include "../core/Core.hpp"

Display::NcursesDisplay::NcursesDisplay()
{
    newterm(NULL, stdout, stdin);
    curs_set(0);
    _win = new NcursesWindow(0, 0, 0, 0);
    _colorPair = 0;
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_YELLOW, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLUE);
    init_pair(7, COLOR_GREEN, COLOR_WHITE);
    init_pair(8, COLOR_MAGENTA, COLOR_GREEN);
    reloadBoards();
}

Display::NcursesDisplay::~NcursesDisplay()
{
    delete _win;
    endwin();
}

void Display::NcursesDisplay::reloadBoards()
{
    Display::Board *_boards = Core::getInstance()->getBoards();

    for (int i = 0; i < 2; ++i) {
        _boards[i].x = 1;
        _boards[i].y = 1 + i * (LINES / 2);
        _boards[i].width = (COLS - 2) / 2;
        _boards[i].height = (LINES - 2) / 2;
    }
    for (int i = 2; i < 4; ++i) {
        _boards[i].x = COLS / 2 + 2;
        _boards[i].y = 1 + (i - 2) * ((LINES - 2) / 4 + 1);
        _boards[i].width = (COLS - 2) / 2;
        _boards[i].height = (LINES - 2) / 4;
    }
    for (int i = 4; i < 6; ++i) {
        _boards[i].x = COLS / 2 + 2;
        _boards[i].y = 2 + 2 * (LINES - 2) / 4 + (i - 4) * ((LINES - 2) / 4 + 1);
        _boards[i].width = (COLS - 2) / 4;
        _boards[i].height = (LINES - 2) / 4;
    }
    for (int i = 6; i < 8; ++i) {
        _boards[i].x = COLS / 4 * 3 + 3;
        _boards[i].y = 2 + 2 * (LINES - 2) / 4 + (i - 6) * ((LINES - 2) / 4 + 1);
        _boards[i].width = (COLS - 2) / 4;
        _boards[i].height = (LINES - 2) / 4;
    }
}

void Display::NcursesDisplay::draw(const Display::Board &board,
                                   const std::pair<int, int> &pair,
                                   const std::vector<std::pair<int, int>> &vector,
                                   bool fill)
{
    auto it = vector.end();
    if ((int) vector.size() < board.width - 2)
        it = vector.begin();
    else
        it -= (board.width - 2);

    auto max_elem = std::max_element(it, vector.end(),
                                     [](const std::pair<int, int> &left,
                                        const std::pair<int, int> &right) {
                                         return left.second < right.second;
                                     });
    (void) pair;
    (void) fill;
    int max = (*max_elem).second;
    int div = 1;
    while (max / div > board.height - 2)
        div += 1;
    int x = board.x + 1;
    for (; it != vector.end(); ++it) {
        for (int i = 0; i < (*it).second / div; ++i)
            _win->print(x, board.y + board.height - 1 - i, "|");
        _win->print(x++, board.y + board.height - 1 - (*it).second / div, "+");
    }

}

void Display::NcursesDisplay::write(const Display::Board &board,
                                    const std::string &string)
{
    _win->print(board.x, board.y, board.width, board.height, string);
}

void Display::NcursesDisplay::refresh()
{
    _win->refresh();
    ::refresh();
}

void Display::NcursesDisplay::erase()
{
    reloadBoards();
    _win->applyColorPair(_colorPair + 1);
    _win->clear();

    _win->verticalLine(0, COLS / 2, 1, LINES - 2);
    _win->horizontalLine(0, 1, LINES / 2, COLS - 2);

    _win->verticalLine(0, COLS / 4 * 3 + 1, LINES / 2 + 1, LINES / 2 - 2);
    _win->horizontalLine(0, COLS / 2 + 1, LINES / 4 * 3, COLS / 2 - 2);

    _win->horizontalLine(0, COLS / 2 + 1, LINES / 4, COLS / 2 - 2);
}

void Display::NcursesDisplay::handleResize()
{
}

void Display::NcursesDisplay::processEvents()
{
    int input = _win->getChar();

    switch (input) {
        case 'q':
        case 27:
            Core::getInstance()->exitLoop();
            break;
        case KEY_F(2):
        case KEY_F(3):
        case KEY_F(4):
        case KEY_F(5):
        case KEY_F(6):
        case KEY_F(7):
        case KEY_F(8):
        case KEY_F(9): {
            std::vector<std::string> modules = Core::getInstance()->getCachedModules();
            modules.insert(modules.begin(), "Remove module");
            NcursesWindow subwin(1, 1, COLS / 4,
                                 std::min(LINES - 2, (int) modules.size() + 2),
                                 false);

            int cur = 0;
            int key = 0;
            do {
                if (key == KEY_DOWN)
                    cur = (cur == (int) modules.size() - 1) ? 0 : cur + 1;
                else if (key == KEY_UP)
                    cur = (cur == 0) ? modules.size() - 1 : cur - 1;
                subwin.clear();
                subwin.applyColorPair(_colorPair + 1);
                subwin.refresh();
                int i = 1;
                for (auto it = modules.begin(); it != modules.end(); ++it) {
                    if (i - 1 == cur)
                        subwin.setAttribute(A_REVERSE);
                    subwin.print(2, i++, (*it));
                    subwin.unsetAttribute(A_REVERSE);
                }
                subwin.refresh();
            } while ((key = subwin.getChar()) != 'q' && key != 10);
            if (cur == 0)
                Core::getInstance()->disableModule(input - KEY_F(2));
            else if (key != 'q')
                Core::getInstance()->enableModule(modules[cur], input - KEY_F(2));
        }
            break;
        case 'n':
            Core::getInstance()->changeDisplay(true);
            break;
        case 't':
            ++_colorPair;
            _colorPair %= 8;
            _win->applyColorPair(_colorPair + 1);
            break;
        case 'p':
            NcursesWindow subwin(COLS / 4, LINES / 8, COLS / 2, 3, false);
            std::string in;

            echo();
            subwin.clear();
            subwin.applyColorPair(_colorPair + 1);
            subwin.print(1, 1, "Module path : ");
            subwin.refresh();
            in = subwin.prompt(15, 1);

            if (in != "") {
                wordexp_t exp_result;

                if (wordexp(in.c_str(), &exp_result, 0) == 0) {
                    Core::getInstance()->loadModule(exp_result.we_wordv[0]);
                    wordfree(&exp_result);
                    noecho();
                    break;
                }
            }
    }
}
