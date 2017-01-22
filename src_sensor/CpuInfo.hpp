//
// Created by szterg_r on 20/01/17.
//

#ifndef CPP_GKRELLM_CPUINFO_HPP
#define CPP_GKRELLM_CPUINFO_HPP

#include "AMonitorModule.hpp"

class CpuInfo : public Modules::AMonitorModule
{
public:
    CpuInfo();

    virtual const std::vector<std::pair<int, int>> &getGraphData() const override;

    virtual const std::pair<int, int> &getGraphScales() const override;

    virtual const std::string &getText() const override;

    virtual void refresh(time_t time) override;

    void getCpuInfo(time_t time);

private:
    std::pair<int, int> _graphScale;
    std::vector<std::pair<int, int>> _graphData;
    std::string _text;
    time_t _lastTime;
};

#endif //CPP_GKRELLM_CPUINFO_HPP
