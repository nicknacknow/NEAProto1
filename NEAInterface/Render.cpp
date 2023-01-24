#include "Render.h"

void Render::main(const char* title, int width, int height) {
	printf("helo");
	this->mainWindow = new RenderWindow(VideoMode(width, height), title);
	RenderWindow* window = this->mainWindow; // make the code look nicer

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		window->clear(Color::Magenta);

		window->display();
	}
}