/*#include "Render.h"
#include "Renderable.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Text.h"

#include "LinkedList.h"
#include "MouseHandler.h"

#include "Button.h"


using namespace Rendering;*/

/*void Render::main() {
	RenderWindow* window = this->mainWindow;

	Font arial;
	if (!this->findFont("arial", arial)) {
		return; // error, arial font not found
	}
	*/
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


/*
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
}*/

// add render step functions for per render... then add MouseHandler etc which can be used by Buttons.
// in mouseHandler i can use foreground checks etc... here we should only bother with rendering

// to make a remove drawable from list function, loop thru and cmp dword value of RenderValue property

// https://stackoverflow.com/questions/67190153/sfml-draw-only-once-and-render-forever