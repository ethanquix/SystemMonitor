/*
** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
// Last update Sun Jan 22 06:43:35 2017 King
*/

#include "IMonitorModule.hpp"
#include "CpuUsage.hpp"
#include <iostream>

int main()
{
  int i;
  int cur = 0;
  Modules::IMonitorModule *module;

  i = 0;
  module = new CpuUsage();
  while (i < 1000000000)
    {
      module->refresh(time(0));
      if (module->getGraphData().back().first > cur)
	{
	  std::cout << "cpu Usage (%) : "
		    << module->getGraphData().back().first << " | "
		    << module->getGraphData().back().second << std::endl;
	  cur++;
	}
      i++;
    }
  return (0);
}
