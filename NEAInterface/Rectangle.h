#pragma once
#include "Renderable.h"

namespace Rendering {
	class Rectangle : public Renderable
	{
	public:
		Rectangle() {
			sf::RectangleShape r;
			value->rect = r;
		}
		Rectangle(sf::RectangleShape r) : value(new RenderValue(r)) {}

		virtual render_type GetType() { return render_type::tCircleShape; }

		virtual RenderValue* get() {
			return this->value;
		}
	private:
		RenderValue* value;
	};
}