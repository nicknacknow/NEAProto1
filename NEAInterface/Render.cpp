#include "Render.h"
#include "Renderable.h"
#include "Text.h"

#include "LinkedList.h"

#include <vector>

LinkedList<Rendering::Renderable> renderables; // list of Renderable 
LinkedList<std::pair<std::string, Font>> fonts; // list of pair of string and font

using namespace Rendering;

bool Render::findFont(std::string fontname, Font& font) {
	for (int i = 0; i < fonts.count(); i++)
		if (fonts.getValue(i).first == fontname) {
			font = fonts.getValue(i).second;
			return true;
		}
	return false;
}

bool Render::addFont(std::string fontname, std::string filename) {
	Font font;
	if (!font.loadFromFile(filename)) return false;
	fonts.AddValue(std::pair< std::string, Font>(fontname, font));

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

	LinkedList<sf::RectangleShape> shapes;

	LinkedList<const sf::Drawable&> drrr;

	Font arial;
	if (!this->findFont("arial", arial)) {
		return; // error, arial font not found
	}

	sf::Text miya;
	miya.setFont(arial);
	miya.setString("hello");
	//miya.setCharacterSize(24);
	miya.setFillColor(Color::Red);
	miya.setStyle(sf::Text::Bold );
	miya.setPosition(50, 50);
	
	sf::Clock clock;

	sf::RenderTexture test;
	test.create(800, 600);

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		miya.setString(std::to_string(1 / time));

		window->clear(Color(33,33,33));

		Vector2i pos = Mouse::getPosition(*window);
		//rectangle.setPosition(pos.x, pos.y);
		//rectangle.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
		//window->draw(rectangle);

		miya.setPosition(pos.x + 50, pos.y);

		drrr.AddValue(miya);
		const Drawable& drawme = drrr.getValue(0);
		
		window->draw(drawme);
		drrr.RemoveValue(0);

		//window->draw(miya);

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			test.draw(rectangle);
			//shapes.AddValue(rectangle);
		}

		//for (int i = 0; i < shapes.count(); i++) {
		//	window->draw(shapes.getValue(i));
		//}

		test.display();
		sf::Sprite bg(test.getTexture());

		window->draw(bg);

		window->display();
	}
}

// https://stackoverflow.com/questions/67190153/sfml-draw-only-once-and-render-forever