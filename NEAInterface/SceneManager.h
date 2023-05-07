#pragma once
#include "Render.h"

// create SceneManager singleton
// within, create Scene class- this will be used with polymorphism for use of other scenes. 
// will have step function, setup / create function.. all virtual so can be used here

namespace Rendering {
	class SceneManager : public Singleton<SceneManager> {
	public:
		class Scene {
		public:
			virtual void step() {

			}

			// setup will be called whenever a new scene has been selected.
			// previous scenes will be stopped as the step function will no longer be ran
			// scene step functions will be called from SceneManager -> Step
			// which will simply just call selected scene step
			// when setup is called, Render->Renderables will be emptied
			// and other things such as render step funcs poss?
			virtual void setup(Render* render) {

			}
		};

	private:
		Scene selected_scene; // so can call its step func etc. 
	};
}