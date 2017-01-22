#include <fstream>
#include <time.h>
#include <sstream>
#include <sys/sysinfo.h>
#include <iomanip>
#include "SysinfoModule.hpp"

SysinfoModule::SysinfoModule() :
        AMonitorModule("SysinfoModule", Modules::Size::Small,
                       Modules::Mode::Text, false, true)
{
}

void SysinfoModule::getSysinfo()
{
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        std::stringstream ss;

        ss.precision(3);
        ss << "Total RAM : " << std::right << std::setw(20) << info.totalram
           << " (" << (double) info.totalram / 1000000000 << "G)" << std::endl;
        ss << "Free RAM : " << std::right << std::setw(20) << info.freeram << " ("
           << (double) info.freeram / 1000000000 << "G)" << std::endl;
        ss << "Shared RAM : " << std::right << std::setw(20) << info.sharedram
           << " (" << (double) info.sharedram / 1000000000 << "G)" << std::endl;
        ss << "Buffer RAM : " << std::right << std::setw(20) << info.bufferram
           << " (" << (double) info.bufferram / 1000000000 << "G)" << std::endl;
        ss << "Swap size : " << std::right << std::setw(20) << info.totalswap
           << " (" << (double) info.totalswap / 1000000000 << "G)" << std::endl;
        ss << "Processes : " << std::right << std::setw(20) << info.procs
           << std::endl;
        _text = ss.str();
    }
}

const std::vector<std::pair<int, int>> &SysinfoModule::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &SysinfoModule::getGraphScales() const
{
    return _graphScale;
}

const std::string &SysinfoModule::getText() const
{
    return _text;
}

void SysinfoModule::refresh(time_t time)
{
    (void) time;
    getSysinfo();
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new SysinfoModule();
}