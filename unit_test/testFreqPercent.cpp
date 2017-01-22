/*
1;4402;0c** file.c for CLION in /clion_ide/
**
** Made by Dimitri Wyzlic
** Login   <wyzlic_a@epitech.net>
**
** Started on  Fri Nov 11 12:07:39 2017 Dimitri Wyzlic
// Last update Sun Jan 22 06:42:49 2017 King
*/

#include "IMonitorModule.hpp"
#include "FrequencyPourcentage.hpp"
#include <iostream>

int main()
{
  int i;
  int cur = 0;
  Modules::IMonitorModule *module;

  i = 0;
  module = new FrequencyPourcentage();
  while (i < 100000000)
    {
      module->refresh(time(0));
      if (module->getGraphData().back().first > cur)
	{
	  std::cout << "Frequency Cpu (%) : "
		    << module->getGraphData().back().first << " | "
		    << module->getGraphData().back().second << std::endl;
	  cur++;
	}
      i++;
    }
  return (0);
}
