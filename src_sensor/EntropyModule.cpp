#include <fstream>
#include <time.h>
#include <sstream>
#include "EntropyModule.hpp"

EntropyModule::EntropyModule() :
        AMonitorModule("EntropyModule", Modules::Size::Small,
                       Modules::Mode::Graph, true, true)
{
    _lastTime = time(0);
    _graphScale.first = 60; //TODO Change that depending on module scale
    _graphScale.second = 0;
    _maxValue = 0;
}

void EntropyModule::getEntropyLoad()
{
    int x = (_graphData.size() > 0) ? _graphData.back().first + 1 : 0;
    std::pair<int, int> p = std::make_pair(x, rand() % 20);
    _graphData.insert(_graphData.end(), p);
}

const std::vector<std::pair<int, int>> &EntropyModule::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &EntropyModule::getGraphScales() const
{
    return _graphScale;
}

const std::string &EntropyModule::getText() const
{
    return _text;
}

void EntropyModule::refresh(time_t time)
{
    (void) time;
    getEntropyLoad();
    getText();
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new EntropyModule();
}