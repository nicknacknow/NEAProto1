#include "Render.h"
#include "Renderable.h"
#include "Text.h"

#include "LinkedList.h"

#include <vector>

LinkedList<Rendering::Renderable*> renderables; // list of Renderable 
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
	this->mainWindow->setFramerateLimit(60);

	if (!this->addFont("arial", "resources/fonts/arial.ttf")) { // loads standard Arial font into program
		exit(0);
	}
}

void Render::main() {
	RenderWindow* window = this->mainWindow;

	LinkedList<const sf::Drawable&> drrr;
	printf("%p\n", &drrr);

	Font arial;
	if (!this->findFont("arial", arial)) {
		return; // error, arial font not found
	}

	sf::Text miya;
	miya.setFont(arial);
	miya.setString("hello");
	//miya.setCharacterSize(24);
	//miya.setFillColor(Color::Red);
	//miya.setStyle(sf::Text::Bold );
	miya.setPosition(50, 50);
	
	sf::Clock clock;

	sf::RenderTexture test;
	test.create(800, 600);

	sf::CircleShape circle;
	circle.setRadius(5);

	Rendering::Text texst(miya);
	texst.addstepfunction([](RenderValue* val, float dT) {
		val->text.setString(std::to_string(1 / dT));
		});
	renderables.AddValue(&texst);

	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		//miya.setString(std::to_string(1 / time));

		window->clear(Color(33,33,33));

		Vector2i pos = Mouse::getPosition(*window);


		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			//test.draw(rectangle);
			circle.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			circle.setPosition(pos.x, pos.y);
			drrr.AddValue(circle);
			test.draw(circle);

			printf("%d\n", drrr.count());
			//shapes.AddValue(rectangle);
		}

		//for (int i = 0; i < drrr.count(); i++) {
		//	test.draw(drrr.getValue(i));
		//} dont do this 


		test.display();
		sf::Sprite bg(test.getTexture());

		window->draw(bg);

		//window->draw(texst.get()->text);
		for (int i = 0; i < renderables.count(); i++) {
			Rendering::Renderable* r = renderables.getValue(i);
			r->step(time);
			
			switch (r->GetType()) // now we render the different types of renderable :)
			{
			case Rendering::tText:
				window->draw(r->get()->text);
				break;
			case Rendering::tNone:
			default:
				break;
			}
		}

		

		//window->draw(miya);

		window->display();
	}
}

// https://stackoverflow.com/questions/67190153/sfml-draw-only-once-and-render-forever