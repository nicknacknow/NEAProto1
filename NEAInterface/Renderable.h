#pragma once
#include <SFML/Graphics.hpp>

#include "Render.h"
#include "LinkedList.h"


namespace Rendering {
	enum render_type {
		tNone,
		tText,
		tCircleShape,
		tRectangleShape
	};

	union RenderValue {
		sf::Text text;
		sf::CircleShape circ;
		sf::RectangleShape rect;

		RenderValue() {}
		RenderValue(sf::Text t) : text(t) {}
		RenderValue(sf::CircleShape t) : circ(t) {}
		RenderValue(sf::RectangleShape t) : rect(t) {}
		//~RenderValue() {}
	};

	typedef void (*step_function)(RenderValue*, float);

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

		void step(float dT) {
			for (int i = 0; i < step_functions.count(); i++)
				step_functions.getValue(i)(this->get(), dT);
		}
		void addstepfunction(step_function f) {
			step_functions.AddValue(f);
		}

		// add a 'addstepfunction' method so different renderables of same type execute different things at step
	private:
		LinkedList<step_function> step_functions;
	};

	//LinkedList<Renderable> renderables;
}
// https://en.sfml-dev.org/forums/index.php?topic=22887.0	
// https://stackoverflow.com/questions/64975510/drawing-from-a-vector-of-objects-using-sfml