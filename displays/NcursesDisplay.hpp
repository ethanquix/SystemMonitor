//
// Created by szterg_r on 21/01/17.
//

#ifndef CPP_GKRELLM_NCURSES_HPP
#define CPP_GKRELLM_NCURSES_HPP

#include "IMonitorDisplay.hpp"
#include "NcursesWindow.hpp"

namespace Display
{
    class NcursesDisplay : public Display::IMonitorDisplay
    {
    public:
        NcursesDisplay();

        virtual ~NcursesDisplay();

    public:
        void draw(const Board &board, const std::pair<int, int> &pair,
                  const std::vector<std::pair<int, int>> &vector,
                  bool fill) override;

        void write(const Board &board, const std::string &string) override;

        void erase() override;

        void processEvents() override;

        void refresh() override;

        void handleResize() override;

    private:
        NcursesWindow *_win;
        int _colorPair;

        void reloadBoards();
    };
};

#endif //CPP_GKRELLM_NCURSES_HPP
