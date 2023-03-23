#pragma once
#include "Render.h"

namespace Rendering {
	typedef void (*button_click_function)();
	class Button {
	public:
		Button() {}
		
		Button(Vector2f pos, Vector2f size, button_click_function f = NULL) : func(f) {
			r.get()->rect.setSize(size);
			r.get()->rect.setPosition(pos);
		}

		/**
		 * @brief called when button is pressed in MouseHandler.h, if a function has been assigned it will be called.
		*/
		void onButtonPress() {
			if (func) func();
		}

		/**
		 * @brief checks if mouse is within the bounds of the button
		*/
		bool IsMouseInArea() {
			Vector2i p = Rendering::Render::GetSingleton()->GetMousePosition();
			sf::RectangleShape rect = r.get()->rect;

			if (p.x > rect.getPosition().x && p.x < rect.getPosition().x + rect.getSize().x)
				if (p.y > rect.getPosition().y && p.y < rect.getPosition().y + rect.getSize().y) {
					return true;
				}
			return false;
		}

		button_click_function func; // could do a linked list but really it can all be put into a func
	private:
		Rendering::Rectangle r;
	};
}