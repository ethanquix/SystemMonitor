//
// Created by doom on 20/01/17.
//

#include "DynamicLibrary.hpp"

DynamicLibrary::DynamicLibrary(const std::string &lib, int openMode)
{
    _handle = dlopen(lib.c_str(), openMode);
}

DynamicLibrary::~DynamicLibrary()
{
//    if (_handle != nullptr)
//        dlclose(_handle);
}

bool DynamicLibrary::isLoaded() const
{
    return _handle != nullptr;
}
