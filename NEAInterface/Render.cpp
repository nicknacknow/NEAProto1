#include "Render.h"
#include "Renderable.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Text.h"

#include "LinkedList.h"
#include "MouseHandler.h"

#include "Button.h"

LinkedList<std::pair<std::string, Font>> fonts; // list of name and font
//LinkedList<Rendering::Renderable*> renderables; // list of Renderable items
LinkedList<Rendering::render_step_function> render_step_functions; // list of functions to be called every render step

using namespace Rendering;

void Render::addRenderable(Renderable* r) {
	renderables.push_back(r);
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

class MainMenuScene : public Singleton<MainMenuScene> {
public:
	virtual void step() {

	}

	inline void setup(Rendering::Render* render) {
		/* MainMenu will consist of :
			* Text - title
			* Button - SHM Scene
			* Button - Simple Pendulum Scene
			* Button - Mass-Spring System Scene
		*/

		Font arial;

		if (!render->findFont("arial", arial)) {
			printf("yo\n");
			return; // error, arial font not found
		}

		Rendering::Text title = render->CreateText();
		sf::Text* text = title.GetValue();
		text->setFont(arial);
		text->setFillColor(Color::Red);
		text->setString("hiya");

		//render->renderables.push_back(&real);
		//printf("whyyyy asdas %p\n", Render::GetSingleton());
		//Rendering::

		//Rendering::Text title = Render::GetSingleton()->CreateText();
		//printf("%p\n", title);
		//sf::Text* text = title.GetValue();
		//text->setFont(arial);
		//text->setFillColor(Color::Red);
		//text->setString("hiya");

		//Rendering::Text title = render->CreateText();
		//{ // new scope to keep variables clean in outer scope
			//sf::Text* text = title.GetValue();
			//text->setFont(arial);
			//text->setFillColor(Color::Red);
			//text->setString("Physics Simulator");
			//text->setPosition(Vector2f(400, 100));
		//}
	}
private:
	//Rendering::Text title;
	// here we will have all values such as buttons etc
};

void Render::main() {
	RenderWindow* window = this->mainWindow;

	Font arial;
	if (!this->findFont("arial", arial)) {
		return; // error, arial font not found
	}

	/*sf::Text miya;
	miya.setFont(arial);
	miya.setPosition(50, 50);
	
	Rendering::Text t = this->CreateText();
	t.GetValue()->setFont(arial);
	t.GetValue()->setPosition(150, 100);
	t.GetValue()->setString("heyyy");

	Rendering::Text texst(miya);
	texst.addstepfunction([](Renderable* val, float dT) {
		val->get()->text.setString(std::to_string(1 / dT));
		});
	renderables.AddValue(&texst);

	sf::Text miya2;
	miya2.setFont(arial);
	miya2.setFillColor(Color::Red);
	miya2.setString("hillo");
	miya2.setPosition(500,200);

	Rendering::Text texst2(miya2);
	renderables.AddValue(&texst2);*/

	//sf::RectangleShape rect;
	//rect.setSize(Vector2f(200, 10));
	//rect.setPosition(Vector2f(500, 200));

	//Rendering::Rectangle r(rect);
	//renderables.AddValue(&r);

	//Button buttoni(Vector2f(500, 200), Vector2f(200,10));
	//renderables.AddValue(&buttoni);

	/*Rendering::Button b = this->CreateButton([](Rendering::Button* self) {
		printf("\nClicked Button b!\n");
		});*/
	/*Rendering::Text label = this->CreateText();
	sf::Text* text = label.GetValue();
	text->setFont(arial);
	text->setFillColor(Color::Red);
	text->setString("hiya");*/
	//text->setPosition(Vector2f(500, 200));

	//b.SetLabel(kmn);

	//b.GetValue()->setSize(Vector2f(200, 10));
	//b.GetValue()->setPosition(Vector2f(500, 200));

	//Rendering::TextBox tb = CreateTextBox(label);
	//tb.GetValue()->setSize(Vector2f(200, 40));
	//tb.GetValue()->setPosition(Vector2f(500, 200));

	//MainMenuScene::GetSingleton()->setup(this);

	/*Rendering::Text title = this->CreateText();
	sf::Text* text = title.GetValue();
	text->setFont(arial);
	text->setFillColor(Color::Red);
	text->setString("hiya");*/



	sf::Clock clock;
	while (window->isOpen()) {
		Event e;
		while (window->pollEvent(e)) {
			if (e.type == Event::Closed) {
				window->close();
			}
			else if (e.type == Event::TextEntered) {
				KeyboardHandler::GetSingleton()->step(e);
			}
		}

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		window->clear(Color(33,33,33));

		for (int xi = 0; xi < render_step_functions.count(); xi++)
			render_step_functions.getValue(xi)(window, time);

		for (int i = renderables.size() - 1; i >= 0; i--) {
			printf("%d\n", i);
			Rendering::Renderable* r = renderables.at(i);
			printf("%p %d\n", r,i);
			//r->step(time);
			
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