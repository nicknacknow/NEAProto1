#pragma once
#include "Renderable.h"

namespace Rendering {
	class Text : public Renderable
	{
	public:
		/*Text(const char* string, int size)
		{
			text.setString(string);
		}*/

		render_type GetType() override { return render_type::Text; }

	private:
		sf::Text text;
	};
}