#include "Render.h"
#include "Renderable.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Text.h"

#include "LinkedList.h"
#include "MouseHandler.h"

#include "Button.h"

LinkedList<std::pair<std::string, Font>> fonts; // list of name and font
LinkedList<Rendering::Renderable*> renderables; // list of Renderable items
LinkedList<Rendering::render_step_function> render_step_functions; // list of functions to be called every render step

using namespace Rendering;

Vector2i Render::GetMousePosition() {
	return Mouse::getPosition(*mainWindow);
}

void Render::addRenderable(Renderable* r) {
	renderables.AddValue(r);
}

void Render::addRenderStepFunction(render_step_function f) {
	render_step_functions.AddValue(f);
}

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

	this->addRenderStepFunction([](RenderWindow* window, float dT) {
		Rendering::MouseHandler::GetSingleton()->step(window, dT);
		});
}

void Render::main() {
	RenderWindow* window = this->mainWindow;

	Font arial;
	if (!this->findFont("arial", arial)) {
		return; // error, arial font not found
	}

	sf::Text miya;
	miya.setFont(arial);
	miya.setPosition(50, 50);

	Rendering::Text texst(miya);
	texst.addstepfunction([](RenderValue* val, float dT) {
		val->text.setString(std::to_string(1 / dT));
		});
	renderables.AddValue(&texst);

	sf::Text miya2;
	miya2.setFont(arial);
	miya2.setString("hillo");
	miya2.setPosition(100, 100);

	Rendering::Text texst2(miya2);
	renderables.AddValue(&texst2);

	sf::RectangleShape rect;
	rect.setSize(Vector2f(200, 10));
	rect.setPosition(Vector2f(500, 200));

	//Rendering::Rectangle r(rect);
	//renderables.AddValue(&r);

	Button buttoni(Vector2f(500, 200), Vector2f(200,10));
	renderables.AddValue(&buttoni);

	sf::Clock clock;
	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e))
			if (e.type == Event::Closed)
				window->close();

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		window->clear(Color(33,33,33));

		for (int i = 0; i < render_step_functions.count(); i++)
			render_step_functions.getValue(i)(window, time);

		for (int i = renderables.count() - 1; i >= 0; i--) {
			Rendering::Renderable* r = renderables.getValue(i);
			r->step(time);
			
			switch (r->GetType()) // now we render the different types of renderable :)
			{
			case Rendering::tText:
				window->draw(r->get()->text);
				break;
			case Rendering::tCircleShape:
				window->draw(r->get()->circ);
				break;
			case Rendering::tRectangleShape:
				window->draw(r->get()->rect);
				break;
			case Rendering::tNone:
			default:
				break;
			}
		}

		window->display();
	}
}

// add render step functions for per render... then add MouseHandler etc which can be used by Buttons.
// in mouseHandler i can use foreground checks etc... here we should only bother with rendering

// to make a remove drawable from list function, loop thru and cmp dword value of RenderValue property

// https://stackoverflow.com/questions/67190153/sfml-draw-only-once-and-render-forever