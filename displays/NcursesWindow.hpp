//
// Created by szterg_r on 21/01/17.
//

#ifndef CPP_GKRELLM_NCURSESWINDOW_HPP
#define CPP_GKRELLM_NCURSESWINDOW_HPP

#include <string>
#include <ncurses.h>

namespace Display
{
    class NcursesWindow
    {
    public:
        NcursesWindow(int x, int y, int width, int height, bool noDelay = true);

        ~NcursesWindow();

        bool isGood() const;

        int getChar();

        void applyColorPair(int pair);

        void print(int x, int y, int maxX, int maxY, const std::string &);

        void print(int x, int y, const std::string &txt);

        void putchar(int x, int y, int c);

        void verticalLine(int c, int x, int y, int len);

        void horizontalLine(int c, int x, int y, int len);

        void refresh();

        void clear();

        std::string prompt(int i, int i1);

        void setAttribute(chtype i);

        void unsetAttribute(chtype i);

    private:
        WINDOW *_win;
    };
}

#endif //CPP_GKRELLM_NCURSESWINDOW_HPP
