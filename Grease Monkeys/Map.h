#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable
{
public:

	Map(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	// add functions to play with the entity's geometry / colors / texturing...

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &m_tileset;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};