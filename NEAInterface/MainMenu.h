#pragma once
#include "SceneManager.h"

namespace Rendering {
	class MainMenuScene : public SceneManager::Scene {
	public:
		virtual void step() {

		}

		virtual void setup() {
			/* MainMenu will consist of :
				* Text - title
				* Button - SHM Scene
				* Button - Simple Pendulum Scene
				* Button - Mass-Spring System Scene
			*/

			title = Rendering::RENDER_CLASS->CreateText();
			{ // new scope to keep variables clean in outer scope
				sf::Text* text = title->GetValue();
				text->setFillColor(Color::Red);
				text->setString("Physics Simulator - Main Menu");
				text->setPosition(Vector2f(200, 50));
			}

			shm_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self) 
			{
				printf("\nClicked shm_button!\n");
			});
			{
				sf::RectangleShape* rect = shm_button->GetValue();
				rect->setSize(Vector2f(330, 40));
				rect->setPosition(Vector2f(245, 100));

				// create label for shm button
				Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
				sf::Text* label_text = label->GetValue();
				label_text->setFillColor(Color::Red);
				label_text->setString("Simple Harmonic Motion");

				shm_button->SetLabel(*label);
			}

			sp_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				printf("\nClicked sp_buton\n");
			});
			{
				sf::RectangleShape* rect = sp_button->GetValue();
				rect->setSize(Vector2f(330, 40));
				rect->setPosition(Vector2f(245, 150));

				// create label for shm button
				Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
				sf::Text* label_text = label->GetValue();
				label_text->setFillColor(Color::Red);
				label_text->setString("Simple Pendulum");

				sp_button->SetLabel(*label);
			}

			mss_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				printf("\nClicked mss_button\n");
			});
			{
				sf::RectangleShape* rect = mss_button->GetValue();
				rect->setSize(Vector2f(330, 40));
				rect->setPosition(Vector2f(245, 200));

				// create label for shm button
				Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
				sf::Text* label_text = label->GetValue();
				label_text->setFillColor(Color::Red);
				label_text->setString("Mass-Spring System");

				mss_button->SetLabel(*label);
			}
		}
	private:
		// here we will have all values such as buttons etc
		Rendering::Text* title;
		Rendering::Button* shm_button;
		Rendering::Button* sp_button;
		Rendering::Button* mss_button;
	};

}



/*

in setup::

sf::CircleShape circ;
			circ.setRadius(5);
			circ.setFillColor(Color::White);
			circ.setPosition(50,50);

			Rendering::Circle* c = new Rendering::Circle(circ);

			Rendering::RENDER_CLASS->addRenderable(c);

			Rendering::Button* b = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self) {
				printf("\nClicked Button b!\n");
				});
			b->GetValue()->setSize(Vector2f(200, 10));
			b->GetValue()->setPosition(Vector2f(500, 200));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			sf::Text* label_text = label->GetValue();
			label_text->setFillColor(Color::Red);
			label_text->setString("hiya");

			Rendering::TextBox* tb = Rendering::RENDER_CLASS->CreateTextBox(*label);
			tb->GetValue()->setSize(Vector2f(200, 40));
			tb->GetValue()->setPosition(Vector2f(500, 500));

			Rendering::Text* pray = Rendering::RENDER_CLASS->CreateText("pray");
			pray->GetValue()->setPosition(Vector2f(420, 69));
			pray->GetValue()->setFillColor(Color::Red);

			sf::Text text;
			text.setFillColor(Color::Red);
			text.setString("plzz");
			text.setPosition(Vector2f(50, 500));

			Rendering::Text* t = new Rendering::Text(text);

			Rendering::RENDER_CLASS->addRenderable(t);
			//Rendering::RENDasdasdER_CLASS->render_text.push_back(text);

			sf::RectangleShape rect;
			rect.setSize(Vector2f(200, 40));
			rect.setPosition(Vector2f(50, 200));
			rect.setFillColor(Color::White);

			Rendering::Rectangle* r = new Rendering::Rectangle(rect);
			Rendering::RENDER_CLASS->addRenderable(r);


*/