#ifndef IMONITOR_MODULE_H_
# define IMONITOR_MODULE_H_

#include <vector>
#include <string>

namespace Modules
{
    enum class Size : char
    {
        Small, Medium, Large
    };
    enum class Mode : char
    {
        Graph, Text
    };

    struct IMonitorModule
    {
        IMonitorModule() = default;

        virtual ~IMonitorModule() = default;

        virtual const std::string &getModuleName() const = 0;

        virtual Size getSize() const = 0;

        virtual Mode getMode() const = 0;

        virtual bool hasGraph() const = 0;

        virtual const std::vector<std::pair<int, int>> &getGraphData() const = 0;

        virtual const std::pair<int, int> &getGraphScales() const = 0;

        virtual bool hasText() const = 0;

        virtual const std::string &getText() const = 0;

        virtual void refresh(time_t time) = 0;
    };
};

typedef Modules::IMonitorModule *(*ModuleGetter)();

#endif /* !IMONITOR_MODULE_H_ */
