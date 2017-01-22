//
// Created by szterg_r on 20/01/17.
//

#include <string>
#include <sstream>
#include <memory>
#include <pwd.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <iostream>
#include "UserInfo.hpp"

UserInfo::UserInfo() :
        AMonitorModule("UserInfo", Modules::Size::Small, Modules::Mode::Text,
                       false, true)
{
    struct passwd *pws;
    struct utsname uts;
    std::stringstream ss;

    if ((pws = getpwuid(geteuid()))) {
        ss << "Username: " << pws->pw_name << std::endl << "UID: " << pws->pw_uid
           << "    ";
        ss << "GID: " << pws->pw_gid << std::endl;
        ss << "Shell : " << pws->pw_shell << std::endl;
        ss << "Home directory : " << pws->pw_dir << std::endl;
    } else
        ss << "Unable to get user data" << std::endl;
    if (uname(&uts) == 0)
        ss << "\nOS: " << uts.sysname << "\nRelease: " << uts.release << " / "
           << uts.version << std::endl;
    else
        ss << "Unable to get OS data" << std::endl;
    _text = ss.str();
}

void UserInfo::refresh(time_t time)
{
    (void) time;
    return;
}

const std::vector<std::pair<int, int>> &UserInfo::getGraphData() const
{
    return _graphData;
}

const std::pair<int, int> &UserInfo::getGraphScales() const
{
    return _graphScale;
}

const std::string &UserInfo::getText() const
{
    return _text;
}

extern "C" Modules::IMonitorModule *getModule()
{
    return new UserInfo();
}
