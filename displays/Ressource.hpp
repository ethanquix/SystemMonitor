#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include <cassert>


enum class Textures
{
    Lune
};

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
    //! Default constructor
    ResourceHolder()
    {};

    //! Copy constructor
    ResourceHolder(const ResourceHolder &other);

    //! Move constructor
    ResourceHolder(ResourceHolder &&other) noexcept;

    //! Destructor
    virtual ~ResourceHolder() noexcept
    {};

    //! Copy assignment operator
    ResourceHolder &operator=(const ResourceHolder &other);

    //! Move assignment operator
    ResourceHolder &operator=(ResourceHolder &&other) noexcept;

public:
    //! Function
    void load_resource(Identifier id, std::string const &filename);

    template<typename Parameter>
    void
    load_resource(Identifier id, std::string const &filename, Parameter const &);

    Resource &get_resource(Identifier id);

    Resource const &get_resource(Identifier id) const;

    void insert(Identifier id, std::unique_ptr<Resource> resource);

protected:
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "Ressource.hh"
