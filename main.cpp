#include <iostream>
#include "core/Core.hpp"

int main()
{
    Core *core = Core::getInstance();

    core->loadDefaultModules();
    core->run();
    delete core;
    return 0;
}