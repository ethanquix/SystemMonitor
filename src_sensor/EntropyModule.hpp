/*
** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
** Last update Sun Nov 13 17:47:29 2017 Dimitri Wyzlic
*/

#ifndef CPP_GKRELLM_EntropyMODULE_HPP
#define CPP_GKRELLM_EntropyMODULE_HPP


#include "AMonitorModule.hpp"

class EntropyModule : public Modules::AMonitorModule
{
public:
    EntropyModule();

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

    void getEntropyLoad();
};


#endif //CPP_GKRELLM_EntropyMODULE_HPP
