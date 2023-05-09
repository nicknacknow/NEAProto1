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

	struct RenderValue {
		sf::Text text;
		sf::CircleShape circ;
		sf::RectangleShape rect;

		RenderValue() {}
		RenderValue(sf::Text t) : text(t) {}
		RenderValue(sf::CircleShape t) : circ(t) {}
		RenderValue(sf::RectangleShape t) : rect(t) {}
		//~RenderValue() {}
	};

	class Renderable; // so can be used in typedef before it's properly defined
	typedef void (*step_function)(Rendering::Renderable*, float);

	/**
	 * @brief virtual class - allow functions to be overridden
	*/
	class Renderable
	{
	public:
		/**
		 * @brief returns type of Renderable
		*/
		virtual render_type GetType() { return render_type::tNone; };
		/**
		 * @brief returns Renderable RenderValue
		*/
		virtual RenderValue* get() { return new RenderValue; }

		virtual void step(float dT) {

		}
	};
}