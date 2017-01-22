#include <fstream>
#include <time.h>
#include <sstream>
#include "NetworkModule.hpp"

NetworkModule::NetworkModule() :
        AMonitorModule("NetworkModule", Modules::Size::Small,
                       Modules::Mode::Graph, true, false)
{
    _lastTime = time(0);
    _graphScale.first = 60; //TODO Change that depending on module scale
    _graphScale.second = 0;
    _maxValue = 0;
}

void NetworkModule::getNetworkLoad(time_t time)
{
    std::stringstream ss;
    int y;

    if (time == _lastTime)
        return;
    std::ifstream file("/proc/net/netstat");
    if (!file.is_open())
        return;
    std::string tmp;
    for (int i = 0; i < 3; i++) {
        getline(file, tmp);
    }
    for (int i = 0; i < 8; i++)
        getline(file, tmp, ' ');
    ss << tmp;
    ss >> y;
    _lastTime = time;
    int x = (_graphData.size() > 0) ? _graphData.back().first + 1 : 0;
    if (_graphData.size() == 0)
        _maxValue = y;
    else if (y > _maxValue)
        _maxValue = (y == 0) ? 1 : y + y / 3;
    std::pair<int, int> p = std::make_pair(x, rand() % 20);
    _graphData.insert(_graphData.end(), p);
}

const std::vector<std::pair<int, int>> &NetworkModule::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &NetworkModule::getGraphScales() const
{
    return _graphScale;
}

const std::string &NetworkModule::getText() const
{
    return _text;
}

void NetworkModule::refresh(time_t time)
{
    getNetworkLoad(time);
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new NetworkModule();
}