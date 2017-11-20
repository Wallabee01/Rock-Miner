#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace SPH {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//Look up texture, see if its in map
		auto mit = _textureMap.find(texturePath); // auto is used to look at the return type of find and match it; returns std::map<std::string, GLTexture>::iterator

		//Check if its not in map
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			// Insert texture into map
			//std::pair<std::string, GLTexture> newPair(texturePath, newTexture); // Create pair
			//_textureMap.insert(newPair); // Insert takes a pair

			//Short-Cut
			_textureMap.insert(make_pair(texturePath, newTexture));

			return newTexture;
		}
		return mit->second; // If it gets to this return, we are guarenteed that mit is pointing to the element we want, so we want to return mit, since mit is a pointer, use -> to access
	}						// When you access mit, it is a pointer with a pair of elements, so you either access first or second
							// first = texturePath, which is the key, second = newTexture, which is the texture

}