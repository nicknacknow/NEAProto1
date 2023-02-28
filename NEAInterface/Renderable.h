#pragma once
#include <SFML/Graphics.hpp>

#include "Render.h"
#include "LinkedList.h"

namespace Rendering {
	enum render_type {
		tNone,
		tText,
		tRectangleShape
	};

	union RenderValue {
		sf::Text text;
		sf::RectangleShape rect;

		RenderValue() {}
		RenderValue(sf::Text t) : text(t) {}
		RenderValue(sf::RectangleShape t) : rect(t) {}
		//~RenderValue() {}
	};

	/**
	 * @brief virtual class - allow functions to be overridden
	*/
	class Renderable
	{
	public:
		/**
		 * @return returns type of Renderable
		*/
		virtual render_type GetType() { return render_type::tNone; };
		virtual RenderValue* get() { return new RenderValue; }

		void step() {};

		// add a 'addstepfunction' method so different renderables of same type execute different things at step
	private:
		
	};

	//LinkedList<Renderable> renderables;
}
// https://en.sfml-dev.org/forums/index.php?topic=22887.0	
// https://stackoverflow.com/questions/64975510/drawing-from-a-vector-of-objects-using-sfml