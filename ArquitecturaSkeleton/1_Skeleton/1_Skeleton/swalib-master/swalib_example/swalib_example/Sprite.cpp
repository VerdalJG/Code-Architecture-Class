#include "Sprite.h"
#include "RenderManager.h"]

Sprite::Sprite(const std::string spriteName, const std::string path, const bool wrapping, const vec2 dimensions) :
	name(spriteName),
	filePath(path),
	uvWrapping(wrapping),
	size(dimensions),
	referenceCount(0),
	texture(-1)
{
	
}

Sprite::~Sprite()
{

}
