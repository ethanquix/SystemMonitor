//
// Created by szterg_r on 20/01/17.
//

#include "Example.hpp"

Example::Example() :
        AMonitorModule("Example", Modules::Size::Small, Modules::Mode::Text,
                       false, true)
{}

void Example::refresh(time_t time)
{
    //This function will be called within each UI refresh, so it's here you will update your data
    (void) time;
    return;
}

const std::vector<std::pair<int, int>> &Example::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &Example::getGraphScales() const
{
    return _graphScale;
}

const std::string &Example::getText() const
{
    return _text;
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new Example();
}