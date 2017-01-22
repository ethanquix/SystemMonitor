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
#include "UserInfo.hpp"
#include <iostream>

int main()
{
  Modules::IMonitorModule *module;

  module = new UserInfo();
  std::cout << module->getText() << std::endl;
  return (0);
}