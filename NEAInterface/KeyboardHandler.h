#pragma once
//#include "TextBox.h"
#include "Render.h"

using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13

namespace Rendering {
	class TextBox; // forward declare so can use selected_textbox
	TextBox* selected_textbox;
	bool selected;

	class TextBox : public Button {
	public:
		TextBox() {}

		virtual void onButtonPress() {
			printf("onButtonPress() textbox\n");

			//Rendering::RENDER_CLASS;

			//KeyboardHandler::SetSelectedTextBox(this);

			printf("%p\n", selected_textbox);

			selected_textbox = this;
			selected = true;


			printf("%p\n", selected_textbox);

			if (func) func(this);
		}

		int length_limit = 10;
	};

	namespace KeyboardHandler {

		void step(Event e) {
			printf("step %p\n", selected_textbox);
			if (selected_textbox == nullptr) return;
			if (selected_textbox->get() != nullptr && selected) {
				Rendering::Text l = selected_textbox->GetLabel();
				sf::Text* t = l.GetValue();

				switch (e.text.unicode) {
				case DELETE_KEY: // remove last character of textbox
					if (t->getString().getSize() != 0)
						t->setString(t->getString().substring(0, t->getString().getSize() - 1));
					break;
				case ENTER_KEY: // exit current textbox
					selected = false;
					break;
				default: // input any other text into selected textbox
					if (t->getString().getSize() < selected_textbox->length_limit)
						t->setString(t->getString().toAnsiString() += e.text.unicode);
					break;
				}
			}
		}
	}
}