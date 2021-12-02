#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

class TileMap
{
private:
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector < std::vector < std::vector < Tile > > > map;
public:
	TileMap();
	~TileMap();
};
#endif 


