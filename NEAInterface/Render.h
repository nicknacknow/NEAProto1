#pragma once
#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "Renderable.h"

#include "Text.h"

#include "Button.h"

#include "MouseHandler.h"
#include "KeyboardHandler.h"

using namespace sf;

namespace Rendering {
	typedef void (*render_step_function)(RenderWindow* r, float dT);

	LinkedList<std::pair<std::string, Font>> fonts; // list of name and font
//LinkedList<Rendering::Renderable*> renderables; // list of Renderable items
	LinkedList<Rendering::render_step_function> render_step_functions; // list of functions to be called every render step


	class Render
	{
	public:
		Render() {}

		/**
		 * @brief constructs the render class with a main window
		 * @param title title of main window
		 * @param width width of main window
		 * @param height height of main window
		*/
		Render(const char* title, int width, int height) {
			this->initiate(title, width, height);
			this->main();
		}

		// same as function above
		void initialise(const char* title, int width, int height) {
			this->initiate(title, width, height);
			this->main();
		}

		/**
		 * @brief loads font from file and adds to fonts list
		 * @return true if font loaded, false if error
		*/
		bool addFont(std::string fontname, std::string filename) {
			Font font;
			if (!font.loadFromFile(filename)) return false;
			fonts.AddValue(std::pair< std::string, Font>(fontname, font));

			return true;
		}

		/**
		 * @brief find added fonts 
		 * @param fontname name of font
		 * @param font output for font
		 * @return true if worked false if error
		*/
		bool findFont(std::string fontname, Font& font) {
			for (int i = 0; i < fonts.count(); i++)
				if (fonts.getValue(i).first == fontname) {
					font = fonts.getValue(i).second;
					return true;
				}
			return false;
		}

		/**
		 * @brief add a function to be called every render step.
		*/
		void addRenderStepFunction(render_step_function f) {
			render_step_functions.AddValue(f);
		}

		/**
		 * @brief 
		 * @param r 
		*/
		void addRenderable(Renderable* r) {
			renderables.push_back(r);
		}

		Rendering::Text* CreateText(const char* string = "") {
			sf::Text t; // set initial data (passed thru args) to text here

			t.setString(string);
			
			Rendering::Text* real = new Rendering::Text(t);

			this->addRenderable(real);
			return real;
		}

		Rendering::Button* CreateButton(button_click_function f = NULL) {
			Button* real = new Button;
			real->func = f;

			MouseHandler::GetSingleton()->AddButton(real);
			this->addRenderable(real);
			return real;
		}

		Rendering::TextBox* CreateTextBox(Rendering::Text label) {
			TextBox* tb = new TextBox;
			printf("pre %p\n", tb);

			tb->func = [&](Rendering::Button* ab) {
				//printf("%p\n", ab);
				//KeyboardHandler::GetSingleton()->SetSelectedTextBox(tb);
			};
			
			tb->SetLabel(label);

			MouseHandler::GetSingleton()->AddButton(tb);
			this->addRenderable(tb);
			return tb;
		}

		std::vector<Rendering::Renderable*> renderables;

		
	//private:
		void initiate(const char* title, int width, int height) {
			this->mainWindow = new RenderWindow(VideoMode(width, height), title, Style::Close); // instantiates mainWindow property.
			this->mainWindow->setFramerateLimit(60);

			if (!this->addFont("arial", "resources/fonts/arial.ttf")) { // loads standard Arial font into program
				exit(0);
			}

			this->addRenderStepFunction([](RenderWindow* window, float dT) {
				Rendering::MouseHandler::GetSingleton()->step(window, dT);
				});
		}
		void main() {
			RenderWindow* window = this->mainWindow;

			Font arial;
			if (!this->findFont("arial", arial)) {
				return; // error, arial font not found
			}

			sf::Clock clock;
			while (window->isOpen()) {
				Event e;
				while (window->pollEvent(e)) {
					if (e.type == Event::Closed) {
						window->close();
					}
					else if (e.type == Event::TextEntered) {
						KeyboardHandler::step(e);
					}
				}

				float time = clock.getElapsedTime().asSeconds();
				clock.restart();

				window->clear(Color(33, 33, 33));

				for (int xi = 0; xi < render_step_functions.count(); xi++)
					render_step_functions.getValue(xi)(window, time);

				// create a list / vector for just text and render through there?
				// see what issues come from that

				for (Renderable* r : renderables) {//for (int i = renderables.size() - 1; i >= 0; i--) {
					//printf("%d\n", i);
					//Rendering::Renderable* r = renderables.at(i);
					//printf("%p %d\n", r, i);
					r->step(time);

					switch (r->GetType()) // now we render the different types of renderable :)
					{
					case Rendering::tText: {
						sf::Text t = r->get()->text;
						if (t.getFont() == NULL) t.setFont(arial); // font must be set directly
						window->draw(t);
						break;
					}
					case Rendering::tCircleShape:
						window->draw(r->get()->circ);
						break;
					case Rendering::tRectangleShape:
						window->draw(r->get()->rect);
						break;
					case Rendering::tNone:
					default:
						break;
					}
				}

				window->display();
			}
		}

		RenderWindow* mainWindow;
	};

	static Render* RENDER_CLASS = new Render();
}

