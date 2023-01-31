#pragma once
#include <SFML/Graphics.hpp>

#define add_property(name, type) \
virtual type name() { \
return "h";	\
}


/**
 * @brief virtual class - allow functions to be overridden 
*/
class Renderable
{
public:

	//virtual sf::Vector2f GetPosition() {};
	//virtual void SetPosition(sf::Vector2f pos) {};

	
};

