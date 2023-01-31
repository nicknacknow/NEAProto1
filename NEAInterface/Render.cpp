#include "Render.h"
#include "Renderable.h"
#include "Text.h"

#include <vector>

std::vector<Renderable> renderables;

bool Render::addFont(std::string filename) {
	Font font;
	if (!font.loadFromFile(filename)) return false;

	return true;
}

void Render::initiate(const char* title, int width, int height) {
	this->mainWindow = new RenderWindow(VideoMode(width, height), title); // instantiates mainWindow property.
	
	if (!this->addFont("resources/fonts/arial.ttf")) {
		exit(0);
	}
}

void Render::main() {
	RenderWindow* window = this->mainWindow;

	

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		window->clear(Color::Magenta);

		window->draw()

		window->display();
	}
}