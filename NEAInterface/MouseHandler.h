#pragma once
#include "Render.h"
#include "Button.h"

using namespace sf;

namespace Rendering {
	class MouseHandler : public Singleton<MouseHandler> {
	public:
		MouseHandler() {

		}

		/**
		 * @brief loops through the renderables list and returns whether or not the input button is in this list
		*/
		bool IsButtonRendered(Button* b) {
			for (Rendering::Renderable* r : *this->renderables) {
				if (r != nullptr && &(r->get()->rect) == b->GetValue())
					return true;
			}
			return false;
		}

		/**
		 * @brief returns a list of buttons that the mouse is hovering over
		*/
		std::vector<Button*> GetButtonsInMouse(RenderWindow* r) {
			std::vector<Button*> v;

			for (int i = 0; i < buttons.count(); i++) {
				Button* b = buttons.getValue(i); // must check if buttons are actually visible.. check renderables
				if (b->IsMouseInArea(sf::Mouse::getPosition(*r)) && IsButtonRendered(b)) // get mouse position within window
					v.push_back(b);
			}

			return v;
		}

		/**
		 * @brief called every renderstep, checks and processes mouse activity 
		*/
		void step(RenderWindow* r, float dT) {
			if (Mouse::isButtonPressed(Mouse::Left)) { // is LMB down?
				if (!press_locked) {
					press_locked = true;
					// check if any box here, but dont execute
					std::vector<Button*> b = this->GetButtonsInMouse(r);
					if (b.size() != 0) {
						selected = true;
						selected_button = b[0];
					}
				}
			}
			else { // is LMB up?
				if (press_locked) {
					press_locked = false;
					// check if box still here then execute

					if (selected) {
						selected = false;
						for (Button* b : this->GetButtonsInMouse(r)) {
							if (b->get() == selected_button->get()) // had to do this instead of a memcmp for some reason
							{ // check if selected button is still selected by mouse
								
								selected_button->onButtonPress();
								break;
							}
						}
					}
				}
			}
		}

		/**
		 * @brief adds button to the button list
		*/
		void AddButton(Button* b) {
			this->buttons.AddValue(b);
		}

		/**
		 * @brief sets a pointer to the renderables list to be saved for the mouse handler
		*/
		void SetRenderables(std::vector<Rendering::Renderable*>& r) {
			this->renderables = &r;
		}

	private:
		std::vector<Rendering::Renderable*>* renderables;
		bool press_locked = false;

		LinkedList<Button*> buttons;
		bool selected = false;
		Button* selected_button;
	};
}