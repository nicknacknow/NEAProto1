#pragma once
#include <SFML/Graphics.hpp>

#include "Singleton.h"

using namespace sf;

class Render : public Singleton<Render>
{
public:
	/**
	 * @brief constructs the render class with a main window
	 * @param title title of main window
	 * @param width width of main window
	 * @param height height of main window
	*/
	Render(const char* title, int width, int height) {
		this->initiate(title, width, height);
		this->main();
	}

	/**
	 * @brief 
	 * @param filename 
	 * @return true if font loaded, false if error
	*/
	bool addFont(std::string filename);
private:
	void initiate(const char* title, int width, int height);
	void main();

	RenderWindow* mainWindow;
};