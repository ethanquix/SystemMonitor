//
// Created by doom on 20/01/17.
//

#ifndef OPTPARSER_DYNAMICLOADER_HPP
#define OPTPARSER_DYNAMICLOADER_HPP

#include <string>
#include <dlfcn.h>

class DynamicLibrary
{
public:
    explicit DynamicLibrary(const std::string &lib, int openMode = RTLD_LAZY);

    virtual ~DynamicLibrary();

    bool isLoaded() const;

    template<typename T>
    T getSymbol(const std::string &symName)
    {
        if (!_handle)
            return nullptr;
        return (T) dlsym(_handle, symName.c_str());
    }

private:
    void *_handle;
};


#endif //OPTPARSER_DYNAMICLOADER_HPP
