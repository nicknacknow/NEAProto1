#pragma once
#include <SFML/Graphics.hpp>

#include "Singleton.h"

using namespace sf;

class Render : public Singleton<Render>
{
public:
	Render() {
		main("Titloe", 800, 600);
	}

	void addFont(std::string filename){}

private:
	void main(const char* title, int width, int height);

	RenderWindow* mainWindow;
};