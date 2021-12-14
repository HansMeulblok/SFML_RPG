#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setFillColor(sf::Color::White);
	//this->tileShape.setOutlineThickness(1.f);
	//this->tileShape.setOutlineColor(sf::Color::Black);
	this->tileShape.setPosition(x, y);
	this->tileShape.setTexture(&texture);
	this->tileShape.setTextureRect(texture_rect);
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileShape);
}
