//
// Created by szterg_r on 20/01/17.
//

#ifndef CPP_GKRELLM_CORE_HPP
#define CPP_GKRELLM_CORE_HPP

#include <list>
#include <map>
#include <memory>
#include "NcursesDisplay.hpp"
#include "IMonitorModule.hpp"
#include "DynamicLibrary.hpp"
#include "IMonitorDisplay.hpp"
#include "SfmlDisplay.hpp"

class Core
{
public:
    ~Core();

    void loadDefaultModules();

    void loadModule(std::string const &path);

    void run();

    void updateBoard(Display::Board &cur, int i, time_t time);

    void exitLoop();

    void changeDisplay(bool isCurses)
    {
        _change = 1;
        if (isCurses)
            _change += 1;
    }

    static Core *getInstance()
    {
        if (_instance == nullptr) {
            _instance = new Core;
        }
        return _instance;
    }

    Display::Board *getBoards();

    void enableModule(const std::string &name, int boardIdx);

    std::vector<std::string> getCachedModules();

private:
    bool GUILLAUME_INFERIEUR_A_PAUL_MAXIME;
    int _change;
    std::map<std::string, Modules::IMonitorModule *> _cachedModules;
    Display::Board _boards[8];
    std::list<DynamicLibrary *> _dynamicLibs;
    static Core *_instance;
    Display::IMonitorDisplay *_display;

    Core();

public:
    static constexpr const char *_sensorPath = "~/.sensor/";

    void disableModule(int i);
};

#endif //CPP_GKRELLM_CORE_HPP
