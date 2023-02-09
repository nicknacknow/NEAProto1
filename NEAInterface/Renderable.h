#pragma once
#include <SFML/Graphics.hpp>

#include "LinkedList.h"

namespace Rendering {
	enum render_type {
		None,
		Text,
		RectangleShape
	};

	/**
	 * @brief virtual class - allow functions to be overridden
	*/
	class Renderable : public sf::Drawable
	{
	public:
		/**
		 * @return returns type of Renderable
		*/
		virtual render_type GetType() { return render_type::None; };

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{

		}
	};

	//LinkedList<Renderable> renderables;
}
// https://en.sfml-dev.org/forums/index.php?topic=22887.0	
// https://stackoverflow.com/questions/64975510/drawing-from-a-vector-of-objects-using-sfml