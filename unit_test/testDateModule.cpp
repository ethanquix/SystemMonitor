/*
** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
** Last update Sun Nov 13 17:47:29 2017 Dimitri Wyzlic
*/

#include "IMonitorModule.hpp"
#include "DateModule.hpp"
#include <iostream>

int main()
{
  int i;
  Modules::IMonitorModule *module;

  i = 0;
  module = new DateModule();
  while (i < 1000)
    {
      module->refresh(0);
      std::cout << module->getText() << std::endl;
      i++;
    }
  return (0);
}