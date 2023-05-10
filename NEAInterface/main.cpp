#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <iostream>

#include "Render.h"

#include "Renderable.h"
#include "Circle.h"
#include "Text.h"

#include "SceneManager.h"

#define PROGRAM_NAME "Physics Simulator"

int main() {
	sf::Thread th([]() {
		Rendering::RENDER_CLASS->initialise(PROGRAM_NAME, 800, 600);
		});

	th.launch(); // render in a separate thread
	
	Sleep(1000); // wait for things to load in thread

	Rendering::SceneManager* sceneManager = Rendering::SceneManager::GetSingleton();

	Rendering::RENDER_CLASS->addRenderStepFunction([&](RenderWindow* window, float dT) {
		sceneManager->step(window, dT);
	});

	Rendering::MainMenuScene* mms = Rendering::MAINMENU_SCENE;

	sceneManager->newScene(mms);

	return 1;
}