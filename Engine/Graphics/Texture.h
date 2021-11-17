#pragma once
#include "Resource/ResourceSystem.h"
#include "Math/MathTypes.h"
#include <SDL.h>
#include <iostream>

namespace glds
{
	class Texture : public Resource
	{
	public:
		Texture() {}
		Texture(class Renderer* renderer);

		bool Create(SDL_Surface* surface);
		bool Load(const std::string& name, void* data) override;

		glm::vec2 GetSize() const;

		friend class Renderer;

	private:
		SDL_Texture* texture{ nullptr };
		SDL_Renderer* renderer{ nullptr };
	};
}