#include "Sprite.h"
#include "RenderManager.h"]

Sprite::Sprite(std::string spriteName, std::string path, bool wrapping, vec2 dimensions) :
    name(spriteName),
    filePath(path),
    uvWrapping(wrapping),
    size(dimensions),
    texture(-1)
{
    type = SpriteType::Individual;
}

Sprite::Sprite(const std::string spriteName, const std::string path, const bool wrapping, const vec2 dimensions, vec2 spritePadding, vec2 sheetLayout) :
    name(spriteName),
    filePath(path),
    uvWrapping(wrapping),
    size(dimensions),
    texture(-1),
    spriteSheetDimensions(sheetLayout),
    padding(spritePadding)
{
    type = SpriteType::SpriteSheet;
    ProcessSpriteSheet();
}

Sprite::~Sprite()
{
    
}


void Sprite::ProcessSpriteSheet()
{
    int columns = static_cast<int>(spriteSheetDimensions.x);
    int rows = static_cast<int>(spriteSheetDimensions.y);

    // Calculate each sub-sprite’s dimensions, accounting for padding
    float subSpriteWidth = (size.x - (columns - 1) * padding.x) / columns;
    float subSpriteHeight = (size.y - (rows - 1) * padding.y) / rows;

    // Populate UV coordinates for each frame in the currentSprite sheet
    subSpriteUVs.clear();
    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            // Calculate UVs with padding in mind
            float uMin = (column * (subSpriteWidth + padding.x)) / size.x;
            float vMin = (row * (subSpriteHeight + padding.y)) / size.y;
            float uMax = uMin + (subSpriteWidth / size.x);
            float vMax = vMin + (subSpriteHeight / size.y);

            UVMapping mapping = UVMapping(uMin, vMin, uMax, vMax);

            subSpriteUVs.push_back(mapping);
        }
    }
}

// Returns a default UV mapping struct if it has no sub-sprites;
UVMapping Sprite::GetSubSpriteUVs(int frame)
{
    return subSpriteUVs.empty() ? subSpriteUVs[frame] : UVMapping(); 
}
