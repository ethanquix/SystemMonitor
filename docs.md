Documentation
-------------

***What is a module ?***
- A module acts as a data source.
- A module can provide two different types of data : graph data, or strings.
A module shall provide at least one of these.
- In pure code, a module is a class inheriting publicly from the IMonitorModule interface.

***How are modules loaded ?***
* Modules are loaded at runtime, using a C++ wrapper around libdl's functions.
* This allows full control over the active modules

***How to make a new module ?***

1. Learn C++
2. Take a look at Example.hpp and Example.cpp, which can be found in the src_sensor directory.
3. Start coding :p