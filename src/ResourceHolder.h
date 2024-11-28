#pragma once
#include <map>
#include <xutility>
#include <cassert>
#include <exception>
#include <sfml/Graphics/Texture.hpp>
#include <sfml/Graphics/Font.hpp>
#include "ID.h"
template<typename Resource, typename Identifier> 
class ResourceHolder {
public: 
	void load(Identifier id, const std::string& filename); 
	Resource& get(Identifier id); 
	const Resource& get(Identifier id) const; 

private: 
	std::map<Identifier, std::unique_ptr<Resource>> ResourceMap; 
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("Resource holder failed to load: " + filename); 
	}
	auto inserted = ResourceMap.insert(
		std::make_pair(id, std::move(resource)));
	//assert(inserted.second); 
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = ResourceMap.find(id); 
	assert(found != ResourceMap.end()); 
	return *(found->second); 
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = ResourceMap.find(id); 
	assert(found != ResourceMap.end()); 
	return *(found->second); 
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;



