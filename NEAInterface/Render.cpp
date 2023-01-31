#include "Render.h"
#include "Renderable.h"
#include "Text.h"

#include <vector>

std::vector<Renderable> renderables; // list of Renderable 
std::vector<std::pair<std::string, Font>> fonts; // list of pair of string and font

Font Render::findFont(std::string fontname) {
	for (std::pair<std::string, Font> pair : fonts) {
		if (pair.first == fontname) return pair.second;
	}
	return;
}

bool Render::addFont(std::string fontname, std::string filename) {
	Font font;
	if (!font.loadFromFile(filename)) return false;
	fonts.push_back(std::pair< std::string, Font>(fontname, font));

	return true;
}

void Render::initiate(const char* title, int width, int height) {
	this->mainWindow = new RenderWindow(VideoMode(width, height), title); // instantiates mainWindow property.
	
	if (!this->addFont("arial", "resources/fonts/arial.ttf")) { // loads standard Arial font into program
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

		

		window->display();
	}
}