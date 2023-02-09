#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <iostream>

#include "Render.h"


#include "Renderable.h"
#include "Text.h"

#define PROGRAM_NAME "Nick's NEA Program"

void test(Rendering::Renderable* r) {
	printf("%s\n", r->GetType());
}

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
	th.launch(); // render in a separate thread

	Text a;
	Rendering::Renderable* r = new Rendering::Renderable();

	return 1;
}

/*

Tools > Options > Text Editor > C/C++ > CodeStyle > General > Generated documentation comments style

Set this to Doxygen (/**)

*/