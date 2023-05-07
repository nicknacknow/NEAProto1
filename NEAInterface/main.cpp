#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <iostream>

#include "Render.h"


#include "Renderable.h"
#include "Circle.h"
#include "Text.h"

#include "MainMenu.h"

#define PROGRAM_NAME "Physics Simulator"

//typedef std::function<void(const char*)> testy;
typedef std::function<void(const char*)> testy;
void call_lambda(testy f) {
	// Call the lambda function
	f("Hello");
}

int main() {
	/*RenderWindow window(VideoMode(800, 600), "Title");

	Font arial;
	if (!arial.loadFromFile("resources/fonts/arial.ttf")) printf("error font");
	
	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed)
				window.close();

		window.clear(Color(33, 33, 33));

		window.display();
	}*/

	//sf::Thread th([]() { Rendering::Render::GetSingleton(PROGRAM_NAME, 800, 600); });
	
	//Rendering::Render::GetSingleton(PROGRAM_NAME, 800, 600);

	Rendering::RENDasdasdER_CLASS->icba("PROGRAM_NAME", 800, 600);

	/*Rendering::Render::GetSingleton()->addRenderStepFunction([](RenderWindow* window, float dT) {
		Vector2i pos = Mouse::getPosition(*window);

		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			printf("Mouse down!");

			sf::CircleShape circ;
			circ.setRadius(5);
			circ.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			circ.setPosition(pos.x, pos.y);

			Rendering::Circle* c = new Rendering::Circle(circ);
			//c->addstepfunction([](Rendering::RenderValue* val, float dT) {
			//	val->circ.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
			//	});

			Rendering::Render::GetSingleton()->addRenderable(c);
		}
	});*/

	//th.launch(); // render in a separate thread



	//haha([&](const char* hi) {
	//	printf("%s\n", hi);
	//});

	int x = 42;
	call_lambda([&x](const char* msg) {
		std::cout << "Message: " << msg << " x: " << x << std::endl;
		});

	system("pause");
	return 1;
}

/*

Tools > Options > Text Editor > C/C++ > CodeStyle > General > Generated documentation comments style

Set this to Doxygen (/**)

*/


/*

to-do:
add a SceneHandler class
Scenes have different functions, one is to build (& initialize variables) and other is render step

for example one scene can be SHM.

*/