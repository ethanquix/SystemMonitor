/*
** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
// Last update Sun Jan 22 01:40:23 2017 King
*/

#include <time.h>
#include <iostream>
#include "IMonitorModule.hpp"
#include "FlyModule.hpp"

int main()
{
  int i;
  Modules::IMonitorModule *module;

  i = 0;
  module = new Fly();
  std::cout << module->getModuleName() << std::endl;
  while (i < 1000000)
    {
      module->refresh(time(0));
      std::cout << module->getText() << std::endl;
      i++;
    }
  return (0);
}
