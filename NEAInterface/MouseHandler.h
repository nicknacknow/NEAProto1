#pragma once
#include "Render.h"
#include "Button.h"

using namespace sf;

namespace Rendering {
	class MouseHandler : public Singleton<MouseHandler> {
	public:
		MouseHandler() {

		}

		std::vector<Button*> getButtonsInMouse(RenderWindow* r) {
			std::vector<Button*> v;

			for (int i = 0; i < buttons.count(); i++) {
				Button* b = buttons.getValue(i);
				if (b->IsMouseInArea(sf::Mouse::getPosition(*r))) // get mouse position within window
					v.push_back(b);
			}

			return v;
		}

		void step(RenderWindow* r, float dT) {
			if (Mouse::isButtonPressed(Mouse::Left)) { // is LMB down?
				if (!press_locked) {
					press_locked = true;
					// check if any box here, but dont execute
					std::vector<Button*> b = this->getButtonsInMouse(r);
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
						for (Button* b : this->getButtonsInMouse(r)) {
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

		void AddButton(Button* b) {
			this->buttons.AddValue(b);
		}

	private:
		bool press_locked = false;

		LinkedList<Button*> buttons;
		bool selected = false;
		Button* selected_button;
	};
}