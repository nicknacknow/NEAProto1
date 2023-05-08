#pragma once
#include "Renderable.h"

namespace Rendering {
	class Circle : public Renderable
	{
	public:
		Circle() {}
		Circle(sf::CircleShape c) : value(new RenderValue(c)) {}

		virtual render_type GetType() { return render_type::tCircleShape; }

		virtual RenderValue* get() {
			return this->value;
		}

		sf::CircleShape* GetValue() {
			return &(this->get()->circ);
		}
	private:
		RenderValue* value;
	};
}