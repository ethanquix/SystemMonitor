//
// Created by szterg_r on 20/01/17.
//

#include <time.h>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include "FlyModule.hpp"

Fly::Fly() :
        AMonitorModule("Fly", Modules::Size::Large, Modules::Mode::Text, false,
                       true)
{
    _lastTime = 0;
    _text = "[Error]";
}

void Fly::getFly(time_t time)
{
    if (time == _lastTime)
        return;
    _lastTime = time;
    if (time % 2)
        _text = "       *     /x\\       /x\\        \n            /v\\x\\  *  /v\\/\\       \n      *     \\><\\x\\   /></x/       \n         *   \\><\\x\\ /></x/   *    \n     __ __  __\\><\\x/></x/____     \n    /##_##\\/       \\</x/     \\    \n   |###|###|  \\   DAN   \\    /    \n    \\##|##/ \\__\\____\\____\\__/     \n      |_|   |  |  | |  | |     *  \n      \\*/   \\  |  | |  | /        \n    *          /    /       *     ";
    else
        _text = "                                  \n            _____     _____       \n      *    /\\><\\x\\   /\\x\\><\\      \n        *  \\_\\><\\x\\ /><\\x\\><\\  *  \n     __ __  __\\><\\x/></ -----     \n    /##_##\\/       \\   \\     \\    \n   |###|###|  \\   DAN   \\    /    \n  /  ##|##/ \\__\\____\\____\\__/     \n  |*/        |  |  | |  | |       \n         *   /  |  / |  / \\   *   \n      *          \\    \\           ";

}

void Fly::refresh(time_t time)
{
    //This function will be called each seconds so it's here you will update the output (text or graph)
    getFly(time);
}

const std::vector<std::pair<int, int>> &Fly::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &Fly::getGraphScales() const
{
    return _graphScale;
}

const std::string &Fly::getText() const
{
    return _text;
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new Fly();
}
