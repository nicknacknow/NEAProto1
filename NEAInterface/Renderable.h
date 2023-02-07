#pragma once
#include <SFML/Graphics.hpp>

enum render_type {
	None,
	Text,
	RectangleShape
};

/**
 * @brief virtual class - allow functions to be overridden 
*/
class Renderable
{
public:
	virtual render_type GetType() { return render_type::None; };
	//virtual sf::Vector2f GetPosition() {};
	//virtual void SetPosition(sf::Vector2f pos) {};

	
};
// https://en.sfml-dev.org/forums/index.php?topic=22887.0	
// https://stackoverflow.com/questions/64975510/drawing-from-a-vector-of-objects-using-sfml