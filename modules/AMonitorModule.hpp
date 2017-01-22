//
// Created by szterg_r on 20/01/17.
//

#ifndef CPP_GKRELLM_AMONITORMODULE_HPP
#define CPP_GKRELLM_AMONITORMODULE_HPP

#include <vector>
#include "IMonitorModule.hpp"

namespace Modules
{
    class AMonitorModule : public Modules::IMonitorModule
    {
    public:
        virtual ~AMonitorModule() override = default;

        //! Constructor && Destructors.
        const std::string &getModuleName() const override
        { return _name; }

        AMonitorModule(const std::string &_name, Size _size, Mode _mode,
                       bool _hasGraph, bool _hasText) :
                _name(_name),
                _size(_size),
                _mode(_mode),
                _hasGraph(_hasGraph),
                _hasText(_hasText)
        {}

        Size getSize() const override
        { return _size; }

        Mode getMode() const override
        { return _mode; }

        virtual bool hasGraph() const override
        { return _hasGraph; }

        virtual const std::vector<std::pair<int, int>> &getGraphData() const = 0;

        virtual const std::pair<int, int> &getGraphScales() const = 0;

        virtual bool hasText() const override
        { return _hasText; }

        virtual const std::string &getText() const = 0;

    protected:
        std::string _name;
        Size _size;
        Mode _mode;
        bool _hasGraph;
        bool _hasText;
    };
};

#endif //CPP_GKRELLM_AMONITORMODULE_HPP
