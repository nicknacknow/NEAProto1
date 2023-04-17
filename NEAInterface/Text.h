#pragma once
#include "Renderable.h"

namespace Rendering {
	class Text : public Renderable
	{
	public:
		Text() {}
		Text(sf::Text t) : value(new RenderValue(t)) {}

		virtual render_type GetType() { return render_type::tText; }

		virtual RenderValue* get() {
			return this->value;
		}

		sf::Text* GetValue() { // put this in other renderable classes too
			return &(this->get()->text);
		}
	private:
		RenderValue* value;// = new RenderValue;
	};
}