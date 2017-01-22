//
// Created by szterg_r on 21/01/17.
//

#include <ncurses.h>
#include <iostream>
#include <sstream>
#include "NcursesWindow.hpp"

Display::NcursesWindow::NcursesWindow(int x, int y, int width, int height,
                                      bool noDelay)
{
    _win = newwin(height, width, y, x);
    noecho();
    cbreak();
    keypad(_win, TRUE);
    keypad(_win, TRUE);
    nodelay(_win, noDelay);
}

Display::NcursesWindow::~NcursesWindow()
{
    delwin(_win);
}

bool Display::NcursesWindow::isGood() const
{
    return _win != NULL;
}

int Display::NcursesWindow::getChar()
{
    return wgetch(_win);
}

void Display::NcursesWindow::clear()
{
    werase(_win);
    box(_win, 0, 0);
}

void Display::NcursesWindow::refresh()
{
    wrefresh(_win);
}

void Display::NcursesWindow::print(int x, int y, const std::string &txt)
{
    mvwprintw(_win, y, x, txt.c_str());
}

void Display::NcursesWindow::print(int x, int y, int maxX, int maxY,
                                   const std::string &txt)
{
    std::istringstream is(txt);
    std::string line;

    maxY += y;
    while (std::getline(is, line, '\n') && y < maxY) {
        unsigned long processed = 0;

        while (processed < line.length()) {
            mvwprintw(_win, y++, x, line.substr(processed, maxX - 2).c_str());
            processed += (maxX - 2);
        }
    }
}

void Display::NcursesWindow::horizontalLine(int c, int x, int y, int len)
{
    mvwhline(_win, y, x, c, len);
}

void Display::NcursesWindow::verticalLine(int c, int x, int y, int len)
{
    mvwvline(_win, y, x, c, len);
}

void Display::NcursesWindow::putchar(int x, int y, int c)
{
    mvwaddch(_win, y, x, c);
}

std::string Display::NcursesWindow::prompt(int x, int y)
{
    char input[66] = {0};

    mvwgetnstr(_win, y, x, input, 65);
    return input;
}

void Display::NcursesWindow::applyColorPair(int pair)
{
    wbkgd(_win, COLOR_PAIR(pair));
}

void Display::NcursesWindow::setAttribute(chtype attr)
{
    wattron(_win, attr);
}

void Display::NcursesWindow::unsetAttribute(chtype attr)
{
    wattroff(_win, attr);
}
