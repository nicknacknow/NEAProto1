#pragma once
#include "Renderable.h"

namespace Rendering {
	class Rectangle : public Renderable
	{
	public:
		Rectangle() {
			sf::RectangleShape r;
			this->value = new RenderValue(r);
		}
		Rectangle(sf::RectangleShape r) : value(new RenderValue(r)) {}

		virtual render_type GetType() { return render_type::tRectangleShape; }

		virtual RenderValue* get() {
			return this->value;
		}

		sf::RectangleShape* GetValue() {
			return &(this->get()->rect);
		}
	private:
		RenderValue* value;
	};
}