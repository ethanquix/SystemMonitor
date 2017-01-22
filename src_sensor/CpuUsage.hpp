/*
** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
// Last update Sun Jan 22 06:18:39 2017 King
*/

#ifndef CPP_GKRELLM_TRUE_CPUUSAGE_HPP
#define CPP_GKRELLM_TRUE_CPUUSAGE_HPP


#include "AMonitorModule.hpp"

class CpuUsage : public Modules::AMonitorModule
{
public:
    CpuUsage();

    const std::vector<std::pair<int, int>> &getGraphData() const override;

    const std::pair<int, int> &getGraphScales() const override;

    const std::string &getText() const override;

    void refresh(time_t time) override;

private:
    std::pair<int, int> _graphScale;
    std::vector<std::pair<int, int>> _graphData;
    std::string _text;
    time_t _lastTime;
    int _maxValue;
    unsigned long _lastTotalUser;
    unsigned long _lastTotalUserLow;
    unsigned long _lastTotalSys;
    unsigned long _lastTotalIdle;

    void getCpuUsage(time_t time);
};

#endif //CPP_GKRELLM_TRUE_CPUUSAGE_HPP
