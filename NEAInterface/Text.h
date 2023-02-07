#pragma once
#include "Renderable.h"

class Textt : public Renderable
{
public:
	render_type GetType() override { return render_type::Text; }
};

