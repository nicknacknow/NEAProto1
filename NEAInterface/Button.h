#pragma once
#include "Rectangle.h"

#include <functional>


namespace Rendering {
	class Button;
	typedef std::function<void(Button*)> button_click_function;
	//typedef void (*button_click_function)(Button* self);

	class Button : public Rectangle {
	public:
		Button() {}
		
		// getter & setter for Label

		void SetLabel(Rendering::Text* _t) {
			this->label = _t;
		}

		Rendering::Text* GetLabel() {
			return this->label;
		}

		virtual void step(float dT) {
			if (this->label == nullptr || this->label->get() == nullptr) { return; } // dont have a label ? return.

			this->label->GetValue()->setPosition(this->GetValue()->getPosition());
		}


		/**
		 * @brief called when button is pressed in MouseHandler.h, if a function has been assigned it will be called.
		*/
		virtual void onButtonPress() {
			printf("onButtonPress()");
			if (func) func(this);
		}

		/**
		 * @brief checks if mouse is within the bounds of the button
		*/
		bool IsMouseInArea(sf::Vector2i p) {
			sf::RectangleShape* rect = this->GetValue();

			if (p.x > rect->getPosition().x && p.x < rect->getPosition().x + rect->getSize().x)
				if (p.y > rect->getPosition().y && p.y < rect->getPosition().y + rect->getSize().y) {
					return true;
				}
			return false;
		}

		button_click_function func; // could do a linked list but really it can all be put into a func
	private:
		Rendering::Text* label;
	};
}