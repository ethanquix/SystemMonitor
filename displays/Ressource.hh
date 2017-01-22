#pragma once

#include <iostream>
#include <string>
#include "Ressource.hpp"

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load_resource(Identifier id,
                                                         std::string const &filename)
{
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error(__func__ + filename);
    }
    insert(id, std::move(resource));
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load_resource(Identifier id,
                                                         std::string const &filename,
                                                         Parameter const &)
{
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error(std::to_string(__func__) + filename);
    }
    insert(id, std::move(resource));
}


template<typename Resource, typename Identifier>
Resource &ResourceHolder<Resource, Identifier>::get_resource(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}

template<typename Resource, typename Identifier>
Resource const &
ResourceHolder<Resource, Identifier>::get_resource(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());
    return *found->second;
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insert(Identifier id,
                                                  std::unique_ptr<Resource> resource)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}
