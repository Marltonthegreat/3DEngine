#pragma once
#include "Framework/System.h"
#include "Math/MathTypes.h"
#include <SDL.h>
#include <vector>
#include <array>

namespace glds
{
	class InputSystem : public System {
	public:
		enum class eKeyState
		{
			Idle, Pressed, Held, Released
		};

		enum class eMouseButton
		{
			Left, Middle, Right
		};

	public:
		void Startup() override;
		void Shutdown() override;
		void Update(float dt) override;

		eKeyState GetKeyState(int id);
		bool IsKeyDown(int id);
		bool IsPreviousKeyDown(int id);

		const glm::vec2& GetMousePos() const { return mousePos; }

		bool IsButtonDown(int id) { return mouseButtonState[id]; };
		bool IsPrevButtonDown(int id) { return prevMouseButtonState[id]; };
		eKeyState GetButtonState(int id);

	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState;
		int numKeys;

		glm::vec2 mousePos;
		std::array<Uint8, 3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;

	};
}