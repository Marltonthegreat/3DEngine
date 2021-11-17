#pragma once
#include "Component/Component.h"

namespace glds
{
	class GraphicsComponent : public Component
	{
	public:
		virtual void Draw(class Renderer* renderer) = 0;
	};
}