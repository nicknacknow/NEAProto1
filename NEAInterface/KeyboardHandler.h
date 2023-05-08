#pragma once
//#include "TextBox.h"
#include "Render.h"

using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13

#define get_string_from_textbox(tb) (tb->GetLabel()->GetValue()->getString().toAnsiString())	

namespace Rendering {
	class TextBox; // forward declare so can use selected_textbox
	TextBox* selected_textbox;
	bool selected;

	class TextBox : public Button {
	public:
		TextBox() {}

		virtual void step(float dT) {
			if (this == selected_textbox) { // simple selection highlighting
				this->GetValue()->setFillColor(Color::Cyan);
			}
			else if (this->GetValue()->getFillColor() != Color::White) {
				this->GetValue()->setFillColor(Color::White);
			}


			Rendering::Text* label = this->GetLabel();
			if (label == nullptr || label->get() == nullptr) { return; } // dont have a label ? return.

			label->GetValue()->setPosition(this->GetValue()->getPosition());
		}

		virtual void onButtonPress() {
			printf("onButtonPress() textbox\n");

			selected_textbox = this;
			selected = true;

			if (func) func(this);
		}

		int remove_limit = 0; // marks the minimum character user can delete
		int length_limit = 10;
	};

	namespace KeyboardHandler {

		void step(Event e) {
			printf("step %p\n", selected_textbox);

			if (selected_textbox == nullptr) return;
			if (selected_textbox->get() != nullptr && selected) {
				printf("here 1\n");
				Rendering::Text* l = selected_textbox->GetLabel();
				sf::Text* t = l->GetValue();
				printf("here 2 %d\n", e.text.unicode);

				switch (e.text.unicode) {
				case DELETE_KEY: // remove last character of textbox
				{
					int size = t->getString().getSize();
					if (size != 0 && size - 1 >= selected_textbox->remove_limit)
						t->setString(t->getString().substring(0, size - 1));
					break;
				}
				case ENTER_KEY: // exit current textbox
				{
					selected_textbox = nullptr;
					selected = false;
					break;
				}
				default: // input any other text into selected textbox
					printf("hello\n");
					if (t->getString().getSize() < selected_textbox->length_limit) {
						printf("%s\n", get_string_from_textbox(selected_textbox));
						t->setString(t->getString().toAnsiString() += e.text.unicode);
					}
					break;
				}
			}
		}
	}
}