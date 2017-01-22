//
// Created by szterg_r on 20/01/17.
//

#include <time.h>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include "CpuInfo.hpp"

CpuInfo::CpuInfo() :
        AMonitorModule("CpuInfo", Modules::Size::Large, Modules::Mode::Text,
                       false, true)
{
    _lastTime = 0;
    _text = "[Error]";
}

void CpuInfo::getCpuInfo(time_t time)
{
    if (time == _lastTime)
        return;
    _lastTime = time;
    std::ifstream cpuInfo("/proc/cpuinfo");
    if (cpuInfo.fail())
        return;
    std::string line;
    std::vector<std::string> modelName;
    std::vector<std::string> freq;
    unsigned int nbCore = 0;
    while (std::getline(cpuInfo, line)) {
        if (std::regex_match(line, std::regex("^model\\sname\\s+:.*$")))
            modelName.push_back(line.substr(line.find(":") + 2));
        if (std::regex_match(line, std::regex("^cpu\\sMHz\\s+:.*$")))
            freq.push_back(line.substr(line.find(":") + 2));
        if (std::regex_match(line, std::regex("^processor\\s+:.*$")))
            nbCore += 1;
    }
    if (freq.size() != nbCore || modelName.size() != nbCore)
        return;
    std::stringstream sstr;
    for (unsigned int i = 0; i < nbCore; ++i) {
        sstr << "Processor       : " << i + 1 << std::endl;
        sstr << "Model name      : " << modelName[i] << std::endl;
        sstr << "Frequence (MHz) : " << freq[i] << std::endl;
    }
    _text = sstr.str();
}

void CpuInfo::refresh(time_t time)
{
    //This function will be called each seconds so it's here you will update the output (text or graph)
    getCpuInfo(time);
}

const std::vector<std::pair<int, int>> &CpuInfo::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &CpuInfo::getGraphScales() const
{
    return _graphScale;
}

const std::string &CpuInfo::getText() const
{
    return _text;
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new CpuInfo();
}
