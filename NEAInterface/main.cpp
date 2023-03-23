#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <iostream>

#include "Render.h"


#include "Renderable.h"
#include "Circle.h"
#include "Text.h"

#define PROGRAM_NAME "Nick's NEA Program"

int main() {
	/*RenderWindow window(VideoMode(800, 600), "Title");

	Font arial;
	if (!arial.loadFromFile("resources/fonts/arial.ttf")) printf("error font");
	
	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed)
				window.close();

		window.clear(Color(33, 33, 33));

		window.display();
	}*/

	sf::Thread th([]() { Rendering::Render::GetSingleton(PROGRAM_NAME, 800, 600); });

	/*Rendering::Render::GetSingleton()->addRenderStepFunction([](RenderWindow* window, float dT) {
		Vector2i pos = Mouse::getPosition(*window);

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			printf("Mouse down!");

			sf::CircleShape circ;
			circ.setRadius(5);
			circ.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			circ.setPosition(pos.x, pos.y);

			Rendering::Circle* c = new Rendering::Circle(circ);
			c->addstepfunction([](Rendering::RenderValue* val, float dT) {
				val->circ.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
				});

			Rendering::Render::GetSingleton()->addRenderable(c);
		}
	});*/

	th.launch(); // render in a separate thread



	[](const char* hi) {
		printf("%s\n", hi);
	}("olleh");

	return 1;
}

/*

Tools > Options > Text Editor > C/C++ > CodeStyle > General > Generated documentation comments style

Set this to Doxygen (/**)

*/