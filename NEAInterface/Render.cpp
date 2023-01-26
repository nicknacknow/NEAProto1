#include "Render.h"

bool Render::addFont(std::string filename) {
	Font font;
	if (!font.loadFromFile(filename)) return false;

	return true;
}

void Render::initiate(const char* title, int width, int height) {
	this->mainWindow = new RenderWindow(VideoMode(width, height), title); // instantiates mainWindow property.
	
	this->addFont("resources/fonts/arial.ttf");
}

void Render::main() {
	RenderWindow* window = this->mainWindow;

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		window->clear(Color::Magenta);

		window->display();
	}
}