#pragma once
#include "Object/Object.h"
#include "Core/Serializable.h"

namespace glds
{
	class Component : public Object, public ISerializable
	{
	public:
		virtual void Update() = 0;

	public:
		class Actor* owner{ nullptr };
	};
}