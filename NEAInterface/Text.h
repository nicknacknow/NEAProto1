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

		void addstepfunction(step_function f) {
			step_functions.push_back(f);
		}

		virtual void step(float dT) {
			for (int i = 0; i < step_functions.size(); i++)
				step_functions.at(i)(this, dT);
		}
	private:
		RenderValue* value;// = new RenderValue;
		std::vector<step_function> step_functions;
	};
}