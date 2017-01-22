//
// lol.cpp for  in /home/king/Rendu/Piscine_Tek2/cpp_gkrellm/src_sensor
// 
// Made by King
// Login   <arthur.cros@epitech.eu>
// 
// Started on  Sun Jan 22 05:04:51 2017 King
// Last update Sun Jan 22 06:35:33 2017 King
//

#include <sstream>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include "CpuUsage.hpp"

CpuUsage::CpuUsage()
        : AMonitorModule("CpuUsage", Modules::Size::Medium,
                         Modules::Mode::Graph, true, false)
{
    std::ifstream stat("/proc/stat");
    std::string line;
    std::stringstream sstr;
    while (std::getline(stat, line)) {
        if (std::regex_match(line, std::regex("^cpu\\s+.*$"))) {
            sstr << line.substr(3);
        }
    }
    sstr >> _lastTotalUser;
    sstr >> _lastTotalUserLow;
    sstr >> _lastTotalSys;
    sstr >> _lastTotalIdle;
}

void CpuUsage::getCpuUsage(time_t time)
{
    if (time == _lastTime)
        return;
    _lastTime = time;

    std::ifstream stat("/proc/stat");
    if (stat.fail())
        return;
    std::string line;
    std::stringstream sstr;
    while (std::getline(stat, line)) {
        if (std::regex_match(line, std::regex("^cpu\\s+.*$"))) {
            sstr << line.substr(3);
        }
    }
    unsigned long totalUser;
    unsigned long totalUserLow;
    unsigned long totalSys;
    unsigned long totalIdle;
    sstr >> totalUser;
    sstr >> totalUserLow;
    sstr >> totalSys;
    sstr >> totalIdle;
    double total;
    double percent;

    if (totalUser < _lastTotalUser || totalUserLow < _lastTotalUserLow ||
        totalSys < _lastTotalSys || totalIdle < _lastTotalIdle) {
        percent = 0;
    } else {
        total = (totalUser - _lastTotalUser) +
                (totalUserLow - _lastTotalUserLow) +
                (totalSys - _lastTotalSys);
        percent = total;
        total += (totalIdle - _lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    _lastTotalUser = totalUser;
    _lastTotalUserLow = totalUserLow;
    _lastTotalSys = totalSys;
    _lastTotalIdle = totalIdle;

    int x = (_graphData.size() > 0) ? _graphData.back().first + 1 : 0;
    std::pair<int, int> p = std::make_pair(x, percent);
    std::vector<std::pair<int, int>>::iterator it;
    it = _graphData.end();
    _graphData.insert(it, p);
    if (_graphData.size() > 150)
        _graphData.erase(_graphData.begin());
}

const std::vector<std::pair<int, int>> &CpuUsage::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &CpuUsage::getGraphScales() const
{
    return _graphScale;
}

const std::string &CpuUsage::getText() const
{
    return _text;
}

void CpuUsage::refresh(time_t time)
{
    getCpuUsage(time);
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new CpuUsage();
}
