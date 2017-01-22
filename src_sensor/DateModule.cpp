#include <ctime>
#include <iostream>
#include <sstream>
#include "DateModule.hpp"

DateModule::DateModule() :
        AMonitorModule("DateModule", Modules::Size::Small, Modules::Mode::Text,
                       false, true)
{
    _text = getDate();
}

void DateModule::refresh(time_t time)
{
    (void) time;
    _text = getDate();
}

const std::vector<std::pair<int, int>> &DateModule::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &DateModule::getGraphScales() const
{
    return _graphScale;
}

const std::string &DateModule::getText() const
{
    return _text;
}

std::string DateModule::getDate()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    std::strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
    std::string str(buffer);

    return str;
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new DateModule();
}
