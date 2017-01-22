//
// Created by doom on 21/01/17.
//

#include <system_error>
#include <exception>
#include "DirectoryStream.hpp"

DirectoryStream::DirectoryStream(const std::string &path) : _path(path)
{
    _dirPtr = opendir(path.c_str());
}

DirectoryStream::~DirectoryStream()
{
    if (_dirPtr)
        closedir(_dirPtr);
}

void DirectoryStream::loadContent(const std::string &filter)
{
    dirent *cur;

    _files.clear();
    rewinddir(_dirPtr);
    cur = readdir(_dirPtr);
    if (!cur)
        throw std::system_error(); //Directories should always contain at least . and ..
    do {
        if (filter != "") {
            std::string curName(cur->d_name);
            unsigned long pos = curName.find_last_of(".");

            if (pos != std::string::npos && curName.substr(pos + 1) == filter)
                _files.push_front(*cur);
        } else
            _files.push_front(*cur);
    } while ((cur = readdir(_dirPtr)));
}

DirectoryStream &DirectoryStream::operator>>(std::string &out)
{
    if (_files.empty())
        throw std::logic_error("Directory stream is empty");
    out = _files.front().d_name;
    _files.pop_front();
    return *this;
}

bool DirectoryStream::isEmpty() const
{
    return _files.empty();
}