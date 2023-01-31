#pragma once
#include <SFML/Graphics.hpp>

#define add_property(name, type) \
virtual type name() { \
return "h";	\
}

enum {

};

/**
 * @brief virtual class - allow functions to be overridden 
*/
class Renderable
{
public:
	add_property(oe, const char*);

	//virtual sf::Vector2f GetPosition() {};
	virtual void SetPosition(sf::Vector2f pos) {};
};

