#pragma once
#include "Render.h"
#include "Button.h"

namespace Rendering {
	class MouseHandler : public Singleton<MouseHandler> {
	public:
		void step(RenderWindow* r, float dT) {
			if (Mouse::isButtonPressed(Mouse::Left) && !press_locked) {
				press_locked = true;
				// check if any box here, but dont execute

				for (int i = 0; i < buttons.count(); i++) {
					Button b = buttons.getValue(i);
					if (b.IsMouseInArea()) {
						selected = true;
						selected_button = b;
						break;
					}
				}
			}
			else {
				if (press_locked) {
					press_locked = false;
					// check if box still here then execute

					if (selected) {
						selected = false;
						selected_button.onButtonPress();
					}
				}
			}
		}
	private:
		bool press_locked = false;

		LinkedList<Button> buttons;
		bool selected = false;
		Button selected_button;
	};
}