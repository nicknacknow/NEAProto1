#pragma once
#include <SFML/Graphics.hpp>

#include "Renderable.h"
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
	 * @return true if font loaded, false if error
	*/
	bool addFont(std::string fontname, std::string filename);
	/**
	 * @brief Search through a list 
	 * @return Related font
	*/
	Font findFont(std::string fontname);

	void draw();
private:
	void initiate(const char* title, int width, int height);
	void main();

	RenderWindow* mainWindow;
};