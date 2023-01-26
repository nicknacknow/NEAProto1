#pragma once
#include <SFML/Graphics.hpp>

#include "Singleton.h"

using namespace sf;

class Render : public Singleton<Render>
{
public:
	Render(const char* title, int width, int height) {
		this->initiate(title, width, height);
		this->main();
		printf("title\n");
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