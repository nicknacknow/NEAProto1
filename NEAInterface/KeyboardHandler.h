#pragma once
#include "Render.h"
#include "TextBox.h"

using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13

namespace Rendering {
	class KeyboardHandler : public Singleton<KeyboardHandler> {
	public:
		KeyboardHandler() {}

		/**
		 * @brief handles SFML event for TextEntered every step. 
		*/
		void step(Event e) {
			// check if text box is selected... may have to team up with mouse handler for this
			// while text box is selected (not clicked off)
			// check if Keyboard::isKeyPressed(Keyboard::Backspace)

			// check if we have a selected textbox
			// selected_textbox.get still has a value for some reaowsn
			if (selected_textbox.get() != nullptr && this->selected) {
				Rendering::Text l = selected_textbox.GetLabel();
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
					if (t->getString().getSize() < selected_textbox.length_limit)
						t->setString(t->getString().toAnsiString() += e.text.unicode);
					break;
				}
			}

			// idea ! to get selected text box.. what we can do is :
			// call MouseHandler -> get selected button
			// if this button is also in a textbox linkedlist thingy
			// then we can change its Label property to input?
			// this will required extra logic in mousehandler->step.
			// what we can do is.. do same textbox linkedlist check in step func
			// if user is trying to interact with a textbox, 
			// input will be handled differently compared to standard button.


			// when textbox is selected.. this will be from
			// its onButtonPress function,, 
			// highlight it by changing button background color
			// in this function also call a KeyboardHandler func
			// which will consequently set this->selected_textbox to it

			// anyway, to unselect a textbox you must press enter. 
			// in this func maybe call the textbox function 'unselect'? or
			// anyway this func will just change the background color back to normal

		}

		// create TextBox function... add it to MouseHandler too

		void AddTextBox(TextBox b) {
			this->textboxes.AddValue(b);
		}

		void SetSelectedTextBox(TextBox b) {
			this->selected_textbox = b;
			selected = true;
		}

	private:
		LinkedList<TextBox> textboxes;
		bool selected = false;
		TextBox selected_textbox;
	};
}

// textboxes only need to be sf::Text