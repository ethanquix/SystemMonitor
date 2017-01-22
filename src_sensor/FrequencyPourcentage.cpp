//
// FrequencyPourcentage.cpp for  in /home/king/Rendu/Piscine_Tek2/cpp_gkrellm/src_sensor
// 
// Made by King
// Login   <arthur.cros@epitech.eu>
// 
// Started on  Sun Jan 22 04:10:03 2017 King
// Last update Sun Jan 22 06:42:04 2017 King
//

#include <fstream>
#include <time.h>
#include <sstream>
#include <regex>
#include "FrequencyPourcentage.hpp"

FrequencyPourcentage::FrequencyPourcentage() :
        AMonitorModule("FrequencyPourcentage", Modules::Size::Medium,
                       Modules::Mode::Graph, true, false)
{
    _lastTime = 0;
    _graphScale.first = 60; //TODO Change that depending on module scale
    _graphScale.second = 0;
    _maxValue = 0;
}

void FrequencyPourcentage::getCpuUsage(time_t time)
{

    if (time == _lastTime)
        return;
    _lastTime = time;

    std::ifstream cpuInfo("/proc/cpuinfo");
    if (cpuInfo.fail())
        return;
    std::string line;
    std::vector<int> maxFreq;
    std::vector<int> freq;
    unsigned int nbCore = 0;
    while (std::getline(cpuInfo, line)) {
        if (std::regex_match(line, std::regex("^model\\sname\\s+:.*@.*$"))) {
            int f;
            std::string::size_type d;
            std::string sub = line.substr(line.find("@") + 2);
            f = std::stoi(sub, &d) * 1000;
            f += std::stoi(sub.substr(d + 1)) * 10;
            maxFreq.push_back(f);
        }
        if (std::regex_match(line, std::regex("^cpu\\sMHz\\s+:.*$")))
            freq.push_back(std::stoi(line.substr(line.find(":") + 2)));
        if (std::regex_match(line, std::regex("^processor\\s+:.*$")))
            nbCore += 1;
    }
    if (freq.size() != nbCore || maxFreq.size() != nbCore)
        return;
    int usage = 0;
    for (unsigned int i = 0; i < nbCore; ++i)
        usage += static_cast<double>(static_cast<double>(freq[i]) /
                                     static_cast<double>(maxFreq[i])) * 100;
    usage = usage / nbCore;
    usage -= 50;
    if (usage < 0)
        usage = 0;
    int x = (_graphData.size() > 0) ? _graphData.back().first + 1 : 0;
    std::pair<int, int> p = std::make_pair(x, usage);
    std::vector<std::pair<int, int>>::iterator it;
    it = _graphData.end();
    _graphData.insert(it, p);
    if (_graphData.size() > 90)
        _graphData.erase(_graphData.begin());
}

const std::vector<std::pair<int, int>> &
FrequencyPourcentage::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &FrequencyPourcentage::getGraphScales() const
{
    return _graphScale;
}

const std::string &FrequencyPourcentage::getText() const
{
    return _text;
}

void FrequencyPourcentage::refresh(time_t time)
{
    getCpuUsage(time);
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new FrequencyPourcentage();
}
