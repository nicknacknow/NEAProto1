#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <iostream>

#include "Render.h"



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

	Render::GetSingleton();

	return 1;
}