#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Renderable 
{
public:
	virtual void render() = 0;
};