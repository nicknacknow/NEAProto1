#pragma once
#include <format>

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
			virtual void step(RenderWindow* window, float dT) {

			}

			/**
			 * @brief will be called whenever a new scene has been selected. in charge of setting up the variables for a scene before it is rendered. i.e. buttons etc will be generated here
			*/
			virtual void setup() {

			}

			std::vector<Renderable*> save; // cache of renderables on scene after setup
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
				selected_scene->step(window, dT);
			}
		}

	private:
		Scene* selected_scene; // so can call its step func etc. 
	};

	/**
	 * @brief gets the string value from a textbox, and applies textbox limits to it to get expected value
	*/
	auto get_value_from_textbox = [](Rendering::TextBox* tb) {
		std::string text = get_string_from_textbox(tb);
		return text.substr(tb->remove_limit, text.length());
	};

	/**
	 * @brief use of std::strtod to validate input, converting to number
	*/
	auto validate_double_input = [](std::string _inp, double& out) {
		const char* inp = _inp.c_str();
		char* endptr;
		out = std::strtod(inp, &endptr);
		return !(endptr == inp || *endptr != '\0');
	};
	
	class MainMenuScene : public SceneManager::Scene {
	public:
		virtual void step(RenderWindow* window, float dT);
		virtual void setup();
	private:
		// here we will have all values such as buttons etc
		Rendering::Text* title;
		Rendering::Button* shm_button;
		Rendering::Button* sp_button;
		Rendering::Button* mss_button;
	};
	class SHMScene : public SceneManager::Scene {
	public:
		virtual void step(RenderWindow* window, float dT);
		virtual void setup();
	private:
		// here we will have all values such as buttons etc
		Rendering::Text* title;
		Rendering::Button* back_button;
		Rendering::TextBox* amplitude_x_textbox;
		Rendering::TextBox* amplitude_y_textbox;
		Rendering::TextBox* time_period_textbox;
		Rendering::TextBox* phase_angle_textbox;
		Rendering::TextBox* system_mass_textbox;
		Rendering::Text* kinetic_energy;
		Rendering::Button* apply_button;

		std::vector<Rendering::Circle*> points;

		int MAX_DIGITS = 4;

		double amplitude_x_value;
		double amplitude_y_value;
		double time_period_value;
		double phase_angle_value;
		double system_mass_value;
		bool simulate = false;
		double t = 0; // time duration of simulation
	};
	class SPScene : public SceneManager::Scene {
	public:
		virtual void step(RenderWindow* window, float dT);
		virtual void setup();
	private:
		Rendering::Text* title;
		Rendering::Button* back_button;
		Rendering::TextBox* pendulum_length_textbox;
		Rendering::TextBox* gravity_constant_textbox;
		Rendering::TextBox* initial_angle_textbox;
		Rendering::Circle* pendulum_bob;
		Rendering::Circle* pendulum_anchor;
		Rendering::TextBox* system_mass_textbox;
		Rendering::Text* kinetic_energy;
		Rendering::Button* apply_button;

		int MAX_DIGITS = 4;

		double pendulum_length_value;
		double gravity_constant_value;
		double initial_angle_value;
		double system_mass_value;

		double angle_velocity = 0;
		double angle_acceleration = 0;
		bool simulate = false;
	};
	class MSScene : public SceneManager::Scene {
	public:
		virtual void step(RenderWindow* window, float dT);
		virtual void setup();
	private:
		Rendering::Text* title;
		Rendering::Text* info;
		Rendering::Text* kinetic_energy_text;
		Rendering::Text* potential_energy_text;
		Rendering::Button* back_button;
		Rendering::Circle* system_point;
		Rendering::Circle* anchor_point;
		Rendering::TextBox* system_mass_textbox;
		Rendering::TextBox* gravity_constant_textbox;
		Rendering::TextBox* spring_constant_x_textbox;
		Rendering::TextBox* spring_constant_y_textbox;
		Rendering::TextBox* damping_constant_x_textbox;
		Rendering::TextBox* damping_constant_y_textbox;
		Rendering::Button* apply_button;

		// dont forget kinetic energy !

		int MAX_DIGITS = 4;
		Vector2f origin = Vector2f(400, 200);

		/*
			MS will consist of :
				* Title
				* back button
				* Circle spring end point
				* Circle anchor point
				* INPUT : textbox - mass of system
				* INPUT : textbox - gravity constant
				* INPUT : textbox - spring constant     vvvvvvvvvvv
				* INPUT : textbox - damping constant (maybe diff for x & y?)
				* apply button
			* input: mouse, when held down set spring end point to mouse pos. do this in step, using mouse held down thingy for right mouse button !!
		*/

		double system_mass_value;
		double gravity_constant_value;
		double spring_constant_x_value;
		double spring_constant_y_value;
		double damping_constant_x_value;
		double damping_constant_y_value;

		double velocityX = 0;
		double velocityY = 0;
		bool simulate = false;
	};

	static MainMenuScene* MAINMENU_SCENE = new MainMenuScene;
	static SHMScene* SHM_SCENE = new SHMScene;
	static SPScene* SP_SCENE = new SPScene;
	static MSScene* MS_SCENE = new MSScene;

	void MainMenuScene::step(RenderWindow* window, float dT) {

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
				Rendering::SceneManager::GetSingleton()->newScene(SP_SCENE);
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
				Rendering::SceneManager::GetSingleton()->newScene(MS_SCENE);
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

	void SHMScene::step(RenderWindow* window, float dT) {
		if (simulate) {
			double omega = (2 * PI) / time_period_value; 

			for (double i = 0; i <= 10; i++) { // scale amplitude up by 10 since we're dealing with pixels
				double x = (amplitude_x_value * 10) * cos(deg2rad(omega * (t + i / 10) + phase_angle_value));
				double y = (amplitude_y_value * 10) * cos(deg2rad(omega * (t + i / 10) + phase_angle_value));

				if (i == 0) { // retrieve kinetic energy values of one point
					double vx = -(amplitude_x_value) * omega * sin(deg2rad(omega * t + phase_angle_value)); // velocities of x and y component
					double vy = -(amplitude_y_value) * omega * sin(deg2rad(omega * t + phase_angle_value));

					double kex = 0.5 * system_mass_value * vx * vx; // kinetic energies of x and y components
					double key = 0.5 * system_mass_value * vy * vy;
					
					kinetic_energy->GetValue()->setString("total kinetic energy: " + std::format("{:.2f} J", kex + key));
				}

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
			 * Circle list - the points at which SHM will take place on
			 * TextBox - INPUT: Amplitude of motion in the X direction
			 * TextBox - INPUT: Amplitude of motion in the Y direction
			 * TextBox - INPUT: Time period of motion
			 * TextBox - INPUT: Phase angle of motion
			 * TextBox - INPUT: Mass of system (for ke)
			 * Button - apply inputs & error check
		*/

		title = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = title->GetValue();
			text->setFillColor(Color::Red);
			text->setString("Simple Harmonic Motion");
			text->setPosition(Vector2f(220, 10));
		}

		back_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				Rendering::SceneManager::GetSingleton()->newScene(MAINMENU_SCENE);
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
			amplitude_x_textbox->length_limit = len + MAX_DIGITS; 
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
			amplitude_y_textbox->length_limit = len + MAX_DIGITS; 
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
			time_period_textbox->length_limit = len + MAX_DIGITS; 
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
			phase_angle_textbox->length_limit = len + MAX_DIGITS; 
		}

		system_mass_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = system_mass_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(10, 540));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("System Mass: ");
			}
			system_mass_textbox->SetLabel(label);

			int len = strlen("System Mass: ");
			system_mass_textbox->remove_limit = len;
			system_mass_textbox->length_limit = len + MAX_DIGITS; 
		}

		kinetic_energy = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = kinetic_energy->GetValue();
			text->setPosition(Vector2f(170, 540));
			text->setCharacterSize(17);
			text->setFillColor(Color::Red);
			text->setString("total kinetic energy: ");
		}

		apply_button = Rendering::RENDER_CLASS->CreateButton([&](Rendering::Button* self)
			{
				std::string amplitude_x_text = get_value_from_textbox(amplitude_x_textbox);
				std::string amplitude_y_text = get_value_from_textbox(amplitude_y_textbox);
				std::string time_period_text = get_value_from_textbox(time_period_textbox);
				std::string phase_angle_text = get_value_from_textbox(phase_angle_textbox);
				std::string system_mass_text = get_value_from_textbox(system_mass_textbox);
				
				double pre_amplitude_x_value;
				if (!validate_double_input(amplitude_x_text, pre_amplitude_x_value)) {
					printf("Invalid Amplitude X Value\n");
					return;
				}

				double pre_amplitude_y_value;
				if (!validate_double_input(amplitude_y_text, pre_amplitude_y_value)) {
					printf("Invalid Amplitude Y Value\n");
					return;
				}

				double pre_time_period_value;
				if (!validate_double_input(time_period_text, pre_time_period_value)) {
					printf("Invalid Time Period Value\n");
					return;
				}

				double pre_phase_angle_value;
				if (!validate_double_input(phase_angle_text, pre_phase_angle_value)) {
					printf("Invalid Phase Angle Value\n");
					return;
				}

				double pre_system_mass_value;
				if (!validate_double_input(system_mass_text, pre_system_mass_value)) {
					printf("Invalid System Mass Value\n");
					return;
				}

				// set simulation variables now after error checking
				system_mass_value = pre_system_mass_value;
				phase_angle_value = pre_phase_angle_value;
				time_period_value = pre_time_period_value;
				amplitude_y_value = pre_amplitude_y_value;
				amplitude_x_value = pre_amplitude_x_value;

				simulate = true;
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
	
	void SPScene::step(RenderWindow* window, float dT) {
		if (!simulate) return;
		double force = gravity_constant_value * sin(initial_angle_value);
		angle_acceleration = -force / pendulum_length_value;
		angle_velocity += angle_acceleration;
		initial_angle_value += angle_velocity;

		double linear_velocity = angle_velocity * pendulum_length_value;
		double ke = 0.5 * system_mass_value * linear_velocity * linear_velocity;

		kinetic_energy->GetValue()->setString("total kinetic energy: " + std::format("{:.2f} J", ke));

		sf::CircleShape* c = pendulum_bob->GetValue();
		c->setPosition(Vector2f(400, 200) + Vector2f(pendulum_length_value * sin(initial_angle_value), pendulum_length_value * cos(initial_angle_value)));
	}
	void SPScene::setup() {
		/*
			SP Scene will consist of :
				* Text - title
				* Button - back to main menu
				* TextBox - INPUT: length of pendulum arm
				* TextBox - INPUT: gravity constant
				* TextBox - INPUT: initial angle of pendulum (convert from degrees input to radians)
				* TextBox - INPUT: Mass of system (for ke)
				* Circle - pendulum bob
		*/

		title = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = title->GetValue();
			text->setFillColor(Color::Red);
			text->setString("Simple Pendulum");
			text->setPosition(Vector2f(280, 10));
		}

		back_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				Rendering::SceneManager::GetSingleton()->newScene(MAINMENU_SCENE);
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

		pendulum_length_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = pendulum_length_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(10, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Length: ");
			}
			pendulum_length_textbox->SetLabel(label);

			int len = strlen("Length: ");
			pendulum_length_textbox->remove_limit = len;
			pendulum_length_textbox->length_limit = len + MAX_DIGITS; 
		}

		gravity_constant_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = gravity_constant_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(170, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Gravity: ");
			}
			gravity_constant_textbox->SetLabel(label);

			int len = strlen("Gravity: ");
			gravity_constant_textbox->remove_limit = len;
			gravity_constant_textbox->length_limit = len + MAX_DIGITS; 
		}

		initial_angle_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = initial_angle_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(330, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Initial Angle: ");
			}
			initial_angle_textbox->SetLabel(label);

			int len = strlen("Initial Angle: ");
			initial_angle_textbox->remove_limit = len;
			initial_angle_textbox->length_limit = len + MAX_DIGITS; 
		}

		pendulum_bob = Rendering::RENDER_CLASS->CreateCircle();
		{
			sf::CircleShape* circ = pendulum_bob->GetValue();
			circ->setRadius(10);
			circ->setPosition(Vector2f(400, 200));
		}

		pendulum_anchor = Rendering::RENDER_CLASS->CreateCircle();
		{ // just a static circle for visualisation
			sf::CircleShape* circ = pendulum_anchor->GetValue();
			circ->setRadius(5);
			circ->setFillColor(Color::Cyan);
			circ->setPosition(Vector2f(405, 205));
		}

		system_mass_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = system_mass_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(10, 540));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("System Mass: ");
			}
			system_mass_textbox->SetLabel(label);

			int len = strlen("System Mass: ");
			system_mass_textbox->remove_limit = len;
			system_mass_textbox->length_limit = len + MAX_DIGITS; 
		}

		kinetic_energy = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = kinetic_energy->GetValue();
			text->setPosition(Vector2f(170, 540));
			text->setCharacterSize(17);
			text->setFillColor(Color::Red);
			text->setString("total kinetic energy: ");
		}

		apply_button = Rendering::RENDER_CLASS->CreateButton([&](Rendering::Button* self)
			{
				std::string pendulum_length_text = get_value_from_textbox(pendulum_length_textbox);
				std::string gravity_constant_text = get_value_from_textbox(gravity_constant_textbox);
				std::string initial_angle_text = get_value_from_textbox(initial_angle_textbox);
				std::string system_mass_text = get_value_from_textbox(system_mass_textbox);

				double pre_pendulum_length_value;
				if (!validate_double_input(pendulum_length_text, pre_pendulum_length_value)) {
					printf("Invalid Pendulum Length Value\n");
					return;
				}

				double pre_gravity_constant_value;
				if (!validate_double_input(gravity_constant_text, pre_gravity_constant_value)) {
					printf("Invalid Gravity Constant Value\n");
					return;
				}

				double pre_initial_angle_value;
				if (!validate_double_input(initial_angle_text, pre_initial_angle_value)) {
					printf("Invalid Initial Angle Value\n");
					return;
				}

				double pre_system_mass_value;
				if (!validate_double_input(system_mass_text, pre_system_mass_value)) {
					printf("Invalid System Mass Value\n");
					return;
				}

				// set the simulations values now after error checking
				system_mass_value = pre_system_mass_value;
				initial_angle_value = deg2rad(pre_initial_angle_value);
				gravity_constant_value = pre_gravity_constant_value;
				pendulum_length_value = pre_pendulum_length_value;

				angle_velocity = 0;
				angle_acceleration = 0;
				simulate = true;
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

	void MSScene::step(RenderWindow* window, float dT) {
		if (!simulate) return;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
			Vector2i p = Mouse::getPosition(*window);
			origin = Vector2f(p.x, p.y);
			anchor_point->GetValue()->setPosition(origin + Vector2f(5, 5));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			Vector2i p = Mouse::getPosition(*window);
			system_point->GetValue()->setPosition(Vector2f(p.x, p.y));

			velocityX = 0;
			velocityY = 0;
		}
		else {
			Vector2f pos = system_point->GetValue()->getPosition();

			double springForceX = -spring_constant_x_value * (pos.x - origin.x);
			double springForceY = -spring_constant_y_value * (pos.y - origin.y);

			double dampingForceX = damping_constant_x_value * velocityX;
			double dampingForceY = damping_constant_y_value * velocityY;

			double forceX = springForceX - dampingForceX;
			double forceY = springForceY + system_mass_value * gravity_constant_value - dampingForceY; // must account for weight

			double accelerationX = forceX / system_mass_value;
			double accelerationY = forceY / system_mass_value;

			velocityX = velocityX + accelerationX * dT;
			velocityY = velocityY + accelerationY * dT;

			double kinetic_energy_x = 0.5 * system_mass_value * velocityX * velocityX;
			double kinetic_energy_y = 0.5 * system_mass_value * velocityY * velocityY;
			double kinetic_energy = kinetic_energy_x + kinetic_energy_y;

			kinetic_energy_text->GetValue()->setString("Kinetic Energy: " + std::format("{:.2f} J", kinetic_energy));

			double potential_energy_x = 0.5 * (-springForceX) * (pos.x - origin.x);
			double potential_energy_y = 0.5 * (-springForceY) * (pos.y - origin.y);
			double potential_energy = potential_energy_x + potential_energy_y;

			potential_energy_text->GetValue()->setString("Potential Energy: " + std::format("{:.2f} J", potential_energy));

			// may have to add dampening to velocities here
			system_point->GetValue()->setPosition(Vector2f(pos.x + velocityX, pos.y + velocityY));
		}
	}
	void MSScene::setup() {
		title = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = title->GetValue();
			text->setFillColor(Color::Red);
			text->setString("Mass-Spring System");
			text->setPosition(Vector2f(200, 10));
		}

		info = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = info->GetValue();
			text->setFillColor(Color::Red);
			text->setCharacterSize(17);
			text->setString("Right Mouse Button to move point\nMiddle Mouse Button to move origin");
			text->setPosition(Vector2f(500, 10));
		}

		kinetic_energy_text = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = kinetic_energy_text->GetValue();
			text->setFillColor(Color::Red);
			text->setCharacterSize(17);
			text->setString("Kinetic Energy: ");
			text->setPosition(Vector2f(10, 540));
		}

		potential_energy_text = Rendering::RENDER_CLASS->CreateText();
		{
			sf::Text* text = potential_energy_text->GetValue();
			text->setFillColor(Color::Red);
			text->setCharacterSize(17);
			text->setString("Potential Energy: ");
			text->setPosition(Vector2f(10, 515));
		}

		back_button = Rendering::RENDER_CLASS->CreateButton([](Rendering::Button* self)
			{
				Rendering::SceneManager::GetSingleton()->newScene(MAINMENU_SCENE);
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

		system_point = Rendering::RENDER_CLASS->CreateCircle();
		{
			sf::CircleShape* circ = system_point->GetValue();
			circ->setRadius(10);
			circ->setPosition(origin);
		}

		anchor_point = Rendering::RENDER_CLASS->CreateCircle();
		{ // just a static circle for visualisation
			sf::CircleShape* circ = anchor_point->GetValue();
			circ->setRadius(5);
			circ->setFillColor(Color::Cyan);
			circ->setPosition(origin + Vector2f(5, 5)); // to account for radius
		}

		system_mass_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = system_mass_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(10, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Mass: ");
			}
			system_mass_textbox->SetLabel(label);

			int len = strlen("Mass: ");
			system_mass_textbox->remove_limit = len;
			system_mass_textbox->length_limit = len + MAX_DIGITS; 
		}

		gravity_constant_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = gravity_constant_textbox->GetValue();
			r->setSize(Vector2f(150, 20));
			r->setPosition(Vector2f(170, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Gravity: ");
			}
			gravity_constant_textbox->SetLabel(label);

			int len = strlen("Gravity: ");
			gravity_constant_textbox->remove_limit = len;
			gravity_constant_textbox->length_limit = len + MAX_DIGITS; 
		}

		spring_constant_x_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = spring_constant_x_textbox->GetValue();
			r->setSize(Vector2f(190, 20));
			r->setPosition(Vector2f(330, 540));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Spring Constant X: ");
			}
			spring_constant_x_textbox->SetLabel(label);

			int len = strlen("Spring Constant X: ");
			spring_constant_x_textbox->remove_limit = len;
			spring_constant_x_textbox->length_limit = len + MAX_DIGITS; 
		}

		spring_constant_y_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = spring_constant_y_textbox->GetValue();
			r->setSize(Vector2f(190, 20));
			r->setPosition(Vector2f(330, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Spring Constant Y: ");
			}
			spring_constant_y_textbox->SetLabel(label);

			int len = strlen("Spring Constant Y: ");
			spring_constant_y_textbox->remove_limit = len;
			spring_constant_y_textbox->length_limit = len + MAX_DIGITS; 
		}

		damping_constant_x_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = damping_constant_x_textbox->GetValue();
			r->setSize(Vector2f(210, 20));
			r->setPosition(Vector2f(530, 540));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Damping Constant X: ");
			}
			damping_constant_x_textbox->SetLabel(label);

			int len = strlen("Damping Constant X: ");
			damping_constant_x_textbox->remove_limit = len;
			damping_constant_x_textbox->length_limit = len + MAX_DIGITS; 
		}

		damping_constant_y_textbox = Rendering::RENDER_CLASS->CreateTextBox();
		{
			sf::RectangleShape* r = damping_constant_y_textbox->GetValue();
			r->setSize(Vector2f(210, 20));
			r->setPosition(Vector2f(530, 570));

			Rendering::Text* label = Rendering::RENDER_CLASS->CreateText();
			{
				sf::Text* text = label->GetValue();
				text->setCharacterSize(17);
				text->setFillColor(Color::Red);
				text->setString("Damping Constant Y: ");
			}
			damping_constant_y_textbox->SetLabel(label);

			int len = strlen("Damping Constant Y: ");
			damping_constant_y_textbox->remove_limit = len;
			damping_constant_y_textbox->length_limit = len + MAX_DIGITS; 
		}


		apply_button = Rendering::RENDER_CLASS->CreateButton([&](Rendering::Button* self)
			{
				std::string system_mass_text = get_value_from_textbox(system_mass_textbox);
				std::string gravity_constant_text = get_value_from_textbox(gravity_constant_textbox);
				std::string spring_constant_x_text = get_value_from_textbox(spring_constant_x_textbox);
				std::string spring_constant_y_text = get_value_from_textbox(spring_constant_y_textbox);
				std::string damping_constant_x_text = get_value_from_textbox(damping_constant_x_textbox);
				std::string damping_constant_y_text = get_value_from_textbox(damping_constant_y_textbox);

				double pre_system_mass_value;
				if (!validate_double_input(system_mass_text, pre_system_mass_value)) {
					printf("Invalid System Mass Value\n");
					return;
				}

				double pre_gravity_constant_value;
				if (!validate_double_input(gravity_constant_text, pre_gravity_constant_value)) {
					printf("Invalid Gravity Constant Value\n");
					return;
				}

				double pre_spring_constant_x_value;
				if (!validate_double_input(spring_constant_x_text, pre_spring_constant_x_value)) {
					printf("Invalid Spring Constant X Value\n");
					return;
				}

				double pre_spring_constant_y_value;
				if (!validate_double_input(spring_constant_y_text, pre_spring_constant_y_value)) {
					printf("Invalid Spring Constant Y Value\n");
					return;
				}

				double pre_damping_constant_x_value;
				if (!validate_double_input(damping_constant_x_text, pre_damping_constant_x_value)) {
					printf("Invalid Damping Constant X Value\n");
					return;
				}

				double pre_damping_constant_y_value;
				if (!validate_double_input(damping_constant_y_text, pre_damping_constant_y_value)) {
					printf("Invalid Damping Constant Y Value\n");
					return;
				}

				// set the simulations values now after all the error checking
				damping_constant_y_value = pre_damping_constant_y_value;
				damping_constant_x_value = pre_damping_constant_x_value;
				spring_constant_y_value = pre_spring_constant_y_value;
				spring_constant_x_value = pre_spring_constant_x_value;
				gravity_constant_value = pre_gravity_constant_value;
				system_mass_value = pre_system_mass_value;

				velocityX = 0;
				velocityY = 0;
				simulate = true;
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
}