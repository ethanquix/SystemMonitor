//
// Created by doom on 21/01/17.
//

#ifndef OPTPARSER_DIRECTORYSTREAM_H
#define OPTPARSER_DIRECTORYSTREAM_H


#include <string>
#include <list>
#include <dirent.h>

class DirectoryStream
{
public:
    explicit DirectoryStream(const std::string &path);

    ~DirectoryStream();

    void loadContent(const std::string &filter = "");

    bool isEmpty() const;

    DirectoryStream &operator>>(std::string &);

private:
    std::string _path;
    DIR *_dirPtr;
    std::list<dirent> _files;
};


#endif //OPTPARSER_DIRECTORYSTREAM_H
