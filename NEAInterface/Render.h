#pragma once
#include <SFML/Graphics.hpp>

#include "Singleton.h"
#include "Renderable.h"

#include "Text.h"

#include "Button.h"

#include "MouseHandler.h"

using namespace sf;

namespace Rendering {
	typedef void (*render_step_function)(RenderWindow* r, float dT);
	class Render : public Singleton<Render>
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

		/**
		 * @brief loads font from file and adds to fonts list
		 * @return true if font loaded, false if error
		*/
		bool addFont(std::string fontname, std::string filename);

		/**
		 * @brief find added fonts 
		 * @param fontname name of font
		 * @param font output for font
		 * @return true if worked false if error
		*/
		bool findFont(std::string fontname, Font& font);

		/**
		 * @brief add a function to be called every render step.
		*/
		void addRenderStepFunction(render_step_function f);

		/**
		 * @brief 
		 * @param r 
		*/
		void addRenderable(Renderable* r);

		Rendering::Text CreateText() {
			sf::Text t; // set initial data (passed thru args) to text here
			
			Rendering::Text real(t);

			this->addRenderable(&real);
			return real;
		}

		Rendering::Button CreateButton(button_click_function f = NULL) {
			Button real;
			real.func = f;

			MouseHandler::GetSingleton()->AddButton(real);
			this->addRenderable(&real);
			return real;
		}
	private:
		void initiate(const char* title, int width, int height);
		void main();

		RenderWindow* mainWindow;
	};
}