//
// Created by szterg_r on 20/01/17.
//

#include <iostream>
#include <wordexp.h>
#include <algorithm>
#include <sstream>
#include <SfmlDisplay.hpp>
#include "Core.hpp"
#include "NcursesDisplay.hpp"
#include "DirectoryStream.hpp"

Core *Core::_instance = nullptr;

void Core::loadDefaultModules()
{
    wordexp_t exp_result;
    wordexp(_sensorPath, &exp_result, 0);
    DirectoryStream stream(exp_result.we_wordv[0]);

    stream.loadContent("so");
    while (!stream.isEmpty()) {
        std::string moduleName;
        stream >> moduleName;
        loadModule(exp_result.we_wordv[0] + moduleName);
    }
    wordfree(&exp_result);
}

void Core::loadModule(std::string const &path)
{
    DynamicLibrary *lib = new DynamicLibrary(path);
    ModuleGetter m;

    m = lib->getSymbol<ModuleGetter>("getModule");
    if (m) {
        Modules::IMonitorModule *module = (*m)();

        if (!_cachedModules.count(module->getModuleName())) {
            _cachedModules[module->getModuleName()] = module;
            _dynamicLibs.push_back(lib);
        }
    }
}

Core::Core() : GUILLAUME_INFERIEUR_A_PAUL_MAXIME(true)
{
    _change = 0;
    for (int i = 0; i < 8; ++i)
        _boards[i].module = NULL;
}

Core::~Core()
{
    delete _display;

    auto it = _dynamicLibs.begin();
    std::for_each(_dynamicLibs.begin(), _dynamicLibs.end(),
                  [&it](DynamicLibrary *) { delete *(it++); });
}

void Core::updateBoard(Display::Board &cur, int i, time_t time)
{
    if (cur.module) {
        cur.module->refresh(time);
        switch (cur.module->getMode()) {
            case Modules::Mode::Text:
                _display->write(cur, cur.module->getText());
                break;
            case Modules::Mode::Graph:
                _display->draw(cur, cur.module->getGraphScales(),
                               cur.module->getGraphData());
                break;
        }
    } else {
        std::stringstream s;

        s << "Press F" << i + 2 << " to select modules.";
        _display->write(cur, s.str());
    }
}

void Core::run()
{
    _display = new Display::NcursesDisplay;
    while (GUILLAUME_INFERIEUR_A_PAUL_MAXIME) {
        time_t now = time(NULL);
        _display->processEvents();
        _display->erase();
        for (int i = 0; i < 8; ++i) {
            updateBoard(_boards[i], i, now);
        };
        _display->refresh();
        if (_change) {
            delete _display;
            if (_change & 1)
                _display = new Display::NcursesDisplay;
            else
                _display = new Display::SfmlDisplay;
            _change = 0;
        }
    }
}

Display::Board *Core::getBoards()
{
    return _boards;
}

void Core::exitLoop()
{
    GUILLAUME_INFERIEUR_A_PAUL_MAXIME = false;
}

void Core::enableModule(const std::string &name, int boardIdx)
{
    auto it = _cachedModules.find(name);

    if (it != _cachedModules.end()) {
        _boards[boardIdx].module = _cachedModules[name];
    } else {
        //Error handling
    }
}

void Core::disableModule(int boardIdx)
{
    _boards[boardIdx].module = NULL;
}

std::vector<std::string> Core::getCachedModules()
{
    std::vector<std::string> ret;

    for (auto it = _cachedModules.begin(); it != _cachedModules.end(); ++it) {
        ret.push_back((*it).first);
    }
    return ret;
}
