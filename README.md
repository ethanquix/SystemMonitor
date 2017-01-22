**Modules list**
---------------------

- Machine / User Name (+user info) *done*
- OS et Kernel *done*
- Date and Time *done*
- CPU (model / hz / nb cores / activity)
- RAM
- Network load *done*

*Bonus*
--------------------
- Swap
- Disk Read and Write
- Entropy
- Page Fault
- We can also load module during runtime
- Fly

***Implementation***
---------------------
- Container for loaded modules
 - List, we need to loop a lot and fast inside

- Container for unloaded modules
 - Map, we need to search modules inside but not every seconds

**Unit tests for everything**
---------------------


**Keymap**
---------------------
 SFML :

    [LEFT/RIGHT] -> To go from one board to another
    [Enter] -> Select Module to apply on Board
    [UP/DOWN] -> Move inside the module selection dialog
    [P] -> Open Text Dialog Area to specify new module path
    [Return] -> Delete module from current Board
    [M] -> Cool Mode
    [N] -> Go to Ncurses
    [F1-F9] -> Open Module selection dialog on board specify by F[x]
    [X] -> Secret
