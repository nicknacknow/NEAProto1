#pragma once
#include "Renderable.h"

namespace Rendering {
	class Text : public Renderable
	{
	public:
		Text() {}
		Text(sf::Text t) {
			value = new RenderValue(t);
		}

		render_type GetType() override { return render_type::tText; }

		RenderValue* get() override {
			return this->value;
		}
	private:
		RenderValue* value;// = new RenderValue;
	};
}