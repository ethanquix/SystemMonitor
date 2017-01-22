#ifndef IMONITORDYSPLAY_H_
# define IMONITORDYSPLAY_H_

#include <string>
#include <vector>
#include <IMonitorModule.hpp>

namespace Display
{
    struct Board
    {
        int x;
        int y;
        int width;
        int height;
        Modules::IMonitorModule *module;


        Board(uint32_t x, uint32_t y, uint32_t width, uint32_t height) : x(x), y(y),
                                                                         width(width),
                                                                         height(height),
                                                                         module(NULL)
        {}

        Board() = default;

        ~Board() = default;

    };

    struct IMonitorDisplay
    {
        IMonitorDisplay() = default;

        virtual ~IMonitorDisplay() = default;

        virtual void refresh() = 0;

        virtual void erase() = 0;

        virtual void handleResize() = 0;

        virtual void processEvents() = 0;

        virtual void draw(const Board &, const std::pair<int, int> &,
                          const std::vector<std::pair<int, int>> &,
                          bool fill = true) = 0;

        virtual void write(const Board &, const std::string &) = 0;
    };
}

#endif /* !IMONITORDYSPLAY_H_ */
