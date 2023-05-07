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
		
		//Button(Vector2f pos, Vector2f size, button_click_function f = NULL) : func(f) {
			//this->get()->rect.setSize(size);
			//this->get()->rect.setPosition(pos);
			//MouseHandler::GetSingleton()->AddButton(this); -- create Render::CreateButton as well as other renderables. maybe make into 1 function, pass string for type and return type is Renderable? vararg which can be passed to initialiser
		//}
		
		// setLabel function
		void SetLabel(Rendering::Text _t) {
			this->label = _t;
		}

		Rendering::Text GetLabel() {
			return this->label;
		}

		virtual void step(float dT) {
			if (this->label.get() == nullptr) { return; } // dont have a label ? return.

			this->label.GetValue()->setPosition(this->GetValue()->getPosition());
		}

		// create step function for button which updates Button->TextLabel stuff


		/**
		 * @brief called when button is pressed in MouseHandler.h, if a function has been assigned it will be called.
		*/
		void onButtonPress() {
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
		Rendering::Text label;
	};
}