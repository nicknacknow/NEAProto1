#include "Render.h"
#include "Renderable.h"
#include "Text.h"

#include "LinkedList.h"

#include <vector>

LinkedList<Renderable> renderables; // list of Renderable 
LinkedList<std::pair<std::string, Font>> fonts; // list of pair of string and font

static Font EmptyFont = Font();

Font Render::findFont(std::string fontname) {
	for (int i = 0; i < fonts.count(); i++)
		if (fonts.getValue(i).first == fontname) return fonts.getValue(i).second;
	printf("error font");
	return EmptyFont; // can be compared on return to see whether or not fail
}

bool Render::addFont(std::string fontname, std::string filename) {
	Font font;
	if (!font.loadFromFile(filename)) return false;
	fonts.AddValue(std::pair< std::string, Font>(fontname, font));
	printf("%p\n", &font);
	return true;
}

void Render::initiate(const char* title, int width, int height) {
	this->mainWindow = new RenderWindow(VideoMode(width, height), title, Style::Close); // instantiates mainWindow property.
	//this->mainWindow->setFramerateLimit(60);

	if (!this->addFont("arial", "resources/fonts/arial.ttf")) { // loads standard Arial font into program
		exit(0);
	}
}



void Render::main() {
	RenderWindow* window = this->mainWindow;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setPosition(10, 20);

	LinkedList<RectangleShape> shapes;

	Font arial = this->findFont("arial");

	Text miya;
	miya.setFont(arial);
	miya.setString("hello");
	miya.setCharacterSize(24);
	miya.setFillColor(Color::Red);
	miya.setStyle(sf::Text::Bold | sf::Text::Underlined);

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		window->clear(Color(33,33,33));

		Vector2i pos = Mouse::getPosition(*window);
		rectangle.setPosition(pos.x, pos.y);
		rectangle.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
		//window->draw(rectangle);

		miya.setPosition(pos.x + 50, pos.y);

		window->draw(miya);

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			shapes.AddValue(rectangle);
		}

		for (int i = 0; i < shapes.count(); i++) {
			window->draw(shapes.getValue(i));
		}

		window->display();
	}
}