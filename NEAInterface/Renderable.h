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
// https://en.sfml-dev.org/forums/index.php?topic=22887.0	
// https://stackoverflow.com/questions/64975510/drawing-from-a-vector-of-objects-using-sfml