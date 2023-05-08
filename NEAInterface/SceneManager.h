#pragma once
#include "Render.h"

// create SceneManager singleton
// within, create Scene class- this will be used with polymorphism for use of other scenes. 
// will have step function, setup / create function.. all virtual so can be used here

#undef PI
#define PI (3.14159265358979323846)
#define RADIANS_PER_DEGREE (PI/180.0)

#define deg2rad(d) (d * RADIANS_PER_DEGREE)

namespace Rendering {
	class SceneManager : public Singleton<SceneManager> {
	public:
		class Scene {
		public:
			/**
			 * @brief Called every render step, is in charge of rendering and changing variables within the scene
			*/
			virtual void step(float dT) {

			}

			// setup will be called whenever a new scene has been selected.
			// previous scenes will be stopped as the step function will no longer be ran
			// scene step functions will be called from SceneManager -> Step
			// which will simply just call selected scene step
			// when setup is called, Render->Renderables must be emptied
			// and other things such as render step funcs poss?

			/**
			 * @brief in charge of setting up the variables for a scene before it is rendered. i.e. buttons etc will be generated here
			*/
			virtual void setup() {

			}

			std::vector<Renderable*> save;
			bool initialised = false;
		};

		/**
		 * @brief makes the selected scene a new scene. handles saving renderables, caching them if they are to be shown again instead of having to setup a whole scene again.
		 * @param the new scene to be displayed
		*/
		void newScene(Scene* s) {
			if (selected_scene) {
				Scene* old = selected_scene;
				selected_scene = nullptr; // stop step before clearing
				std::vector<Renderable*> save = Rendering::RENDER_CLASS->clearRenderables();
				old->save = save;

				Rendering::selected_textbox = nullptr;
				Rendering::selected = false;
			}

			if (s->initialised) {
				for (Renderable* r : s->save) {
					Rendering::RENDER_CLASS->addRenderable(r);
				}
			}
			else {
				s->setup(); // setup before selected
				s->initialised = true;
			}

			selected_scene = s; // now set up, select & run step
		}

		/**
		 * @brief this is the 'master' scene step function. this will handle calling the step function of the current scene.
		*/
		void step(RenderWindow* window, float dT) {
			if (selected_scene != nullptr) {
				selected_scene->step(dT);
			}
		}

	private:
		Scene* selected_scene; // so can call its step func etc. 
	};
	
	class SHMScene : public SceneManager::Scene {
	public:
		virtual void step(float dT);
		virtual void setup();
	private:
		// here we will have all values such as buttons etc
		Rendering::Text* title;
		Rendering::Button* back_button;
		Rendering::TextBox* amplitude_x_textbox;
		Rendering::TextBox* amplitude_y_textbox;
		Rendering::TextBox* time_period_textbox;
		Rendering::TextBox* phase_angle_textbox;
		Rendering::Button* apply_button;

		std::vector<Rendering::Circle*> points;

		int MAX_DIGITS = 4;

		double amplitude_x_value;
		double amplitude_y_value;
		double time_period_value;
		double phase_angle_value;
		bool simulate = false;
		double t = 0; // time duration of simulation
	};
	class MainMenuScene : public SceneManager::Scene {
	public:
		virtual void step(float dT);
		virtual void setup();
	private:
		// here we will have all values such as buttons etc
		Rendering::Text* title;
		Rendering::Button* shm_button;
		Rendering::Button* sp_button;
		Rendering::Button* mss_button;
	};
	static SHMScene* SHM_SCENE = new SHMScene;
	static MainMenuScene* MAINMENU_SCENE = new MainMenuScene;

	void SHMScene::step(float dT) {
		if (simulate) {
			double omega = (2 * PI) / time_period_value; // scale amplitude up by 10 since we're dealing with pixels

			for (double i = 0; i <= 10; i++) {
				double x = (amplitude_x_value * 10) * cos(deg2rad(omega * (t + i / 10) + phase_angle_value));
				double y = (amplitude_y_value * 10) * cos(deg2rad(omega * (t + i / 10) + phase_angle_value));

				Rendering::Circle* r = points[i];
				Vector2f starting_pos = Vector2f(150 + i * 50, 200);

				sf::CircleShape* rect = r->GetValue();
				rect->setPosition(starting_pos + Vector2f(x, y));
			}

			t += dT;
		}
	}
	void SHMScene::setup() {
		/*
			SHM Scene will consist of :
			 * Text - title
			 * Button - back to main menu
			 * Rectangle list - the points at which SHM will take place on
			 * TextBox - INPUT: Amplitude of motion in the X direction
			 * TextBox - INPUT: Amplitude of motion in the Y direction
			 * TextBox - INPUT: Time period of motion
			 * TextBox - INPUT: Phase angle of motion
			 * Button - apply inputs & error check
		*/

		auto get_value_from_textbox = [](Rendering::TextBox* tb) {
			std::string text = get_string_from_textbox(tb);
			return text.substr(tb->remove_limit, text.length());
		};

		auto validate_double_input = [](std::string _inp, double& out) {
			const char* inp = _inp.c_str();
			char* endptr;
			out = std::strtod(inp, &endptr);
			return !(endptr == inp || *endptr != '\0');
		};

		title = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = title->GetValue();
			text->setFillColor(Color::Red);
			text->setString("Simple Harmonic Motion");
			text->setPosition(Vector2f(220, 10));
		}

		back_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				printf("\nClicked back_button!\n");
				Rendering::SceneManager::GetSingleton()->newScene(MAINMENU_SCENE);
				// now we call SceneManager change scene
			});
		{
			sf::RectangleShape* rect = back_button->GetValue();
			rect->setSize(Vector2f(70, 40));
			rect->setPosition(Vector2f(10, 10));

			// create label for shm button
			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			sf::Text* label_text = label->GetValue();
			label_text->setFillColor(Color::Red);
			label_text->setString("Back");

			back_button->SetLabel(label);
		}

		for (int i = 0; i <= 10; i++) {
			Rendering::Circle* c = Rendering::RENDER_CLASS->CreateCircle();
			sf::CircleShape* circ = c->GetValue();
			circ->setRadius(10);
			circ->setPosition(Vector2f(150 + i * 50, 200));

			points.push_back(c);
		}

		amplitude_x_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = amplitude_x_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(10, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Amplitude X: ");
			}
			amplitude_x_textbox->SetLabel(label);

			int len = strlen("Amplitude X: ");
			amplitude_x_textbox->remove_limit = len;
			amplitude_x_textbox->length_limit = len + MAX_DIGITS; // 3 digits for input
		}

		amplitude_y_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = amplitude_y_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(170, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Amplitude Y: ");
			}
			amplitude_y_textbox->SetLabel(label);

			int len = strlen("Amplitude Y: ");
			amplitude_y_textbox->remove_limit = len;
			amplitude_y_textbox->length_limit = len + MAX_DIGITS; // 3 digits for input
		}

		time_period_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = time_period_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(330, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Time Period: ");
			}
			time_period_textbox->SetLabel(label);

			int len = strlen("Time Period: ");
			time_period_textbox->remove_limit = len;
			time_period_textbox->length_limit = len + MAX_DIGITS; // 3 digits for input
		}

		phase_angle_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = phase_angle_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(490, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Phase Angle: ");
			}
			phase_angle_textbox->SetLabel(label);

			int len = strlen("Phase Angle: ");
			phase_angle_textbox->remove_limit = len;
			phase_angle_textbox->length_limit = len + MAX_DIGITS; // 3 digits for input
		}

		apply_button = Rendering::RENDER_CLASS->CreateButton([&](Rendering::Button* self)
			{
				printf("\nClicked apply_button!\n");

				std::string amplitude_x_text = get_value_from_textbox(amplitude_x_textbox);
				std::string amplitude_y_text = get_value_from_textbox(amplitude_y_textbox);
				std::string time_period_text = get_value_from_textbox(time_period_textbox);
				std::string phase_angle_text = get_value_from_textbox(phase_angle_textbox);

				if (!validate_double_input(amplitude_x_text, amplitude_x_value)) {
					printf("amplitude_x_text is wrong\n");
					return;
				}
				if (!validate_double_input(amplitude_y_text, amplitude_y_value)) {
					printf("amplitude_y_text is wrong\n");
					return;
				}
				if (!validate_double_input(time_period_text, time_period_value)) {
					printf("time_period_text is wrong\n");
					return;
				}
				if (!validate_double_input(phase_angle_text, phase_angle_value)) {
					printf("phase_angle_text is wrong\n");
					return;
				}

				printf("its rur\n");
				//printf("%f %f %f %f\n", amplitude_x_value, amplitude_y_value, time_period_value, phase_angle_value);
				simulate = true;
				//printf("%s %s %s %s\n", amplitude_x_text.c_str(), amplitude_y_text.c_str(), time_period_text.c_str(), phase_angle_text.c_str());
			});
		{
			sf::RectangleShape* rect = apply_button->GetValue();
			rect->setSize(Vector2f(45, 20));
			rect->setPosition(Vector2f(750, 570));
			rect->setFillColor(Color::Green);

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			sf::Text* label_text = label->GetValue();
			label_text->setCharacterSize(17);
			label_text->setFillColor(Color::Red);
			label_text->setString("Apply");

			apply_button->SetLabel(label);
		}
	}
	
	void MainMenuScene::step(float dT) {

	}
	void MainMenuScene::setup() {
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
				Rendering::SceneManager::GetSingleton()->newScene(SHM_SCENE);

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

			shm_button->SetLabel(label);
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

			sp_button->SetLabel(label);
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

			mss_button->SetLabel(label);
		}
	}

	
}