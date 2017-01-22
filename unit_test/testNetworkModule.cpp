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
#include "NetworkModule.hpp"
#include <iostream>

int main()
{
  int i;
  __uint32_t cur = 0;
  Modules::IMonitorModule *module;

  i = 0;
  module = new NetworkModule();
  while (i < 100000000)
    {
      module->refresh(time(0));
      if (module->getGraphData().size() > cur)
	{
	  std::cout << "Seconds / Packages : "
		    << module->getGraphData().back().first << " | "
		    << module->getGraphData().back().second << std::endl;
	  cur++;
	}
      i++;
    }
  return (0);
}