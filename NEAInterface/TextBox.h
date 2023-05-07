#pragma once
#include "Text.h"

namespace Rendering {
	class TextBox : public Button {
	public:
		TextBox() {}


		int length_limit = 10;
	};
}