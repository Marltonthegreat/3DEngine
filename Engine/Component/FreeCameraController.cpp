#include "FreeCameraController.h"
#include "Engine.h"

namespace glds
{

	void FreeCameraController::Update()
	{
		glm::vec3 rotate{ 0 };
		if (owner->scene->engine->Get<InputSystem>()->GetButtonState((int)InputSystem::eMouseButton::Right) == InputSystem::eKeyState::Held)
		{
			glm::vec2 axis = owner->scene->engine->Get<InputSystem>()->GetMouseRel() * sensitivity;
			rotate.x -= glm::radians(axis.y);
			rotate.y -= glm::radians(axis.x);
		}

		owner->transform.rotation += rotate;

		glm::vec3 direction{ 0 };
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held) direction.x = -1;
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held) direction.x = 1;
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_W) == InputSystem::eKeyState::Held) direction.z = -1;
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_S) == InputSystem::eKeyState::Held) direction.z = 1;
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_E) == InputSystem::eKeyState::Held) direction.y = 1;
		if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_Q) == InputSystem::eKeyState::Held) direction.y = -1;

		glm::quat rotation{ owner->transform.rotation };

		owner->transform.position += rotation * direction * speed * owner->scene->engine->time.deltaTime;
	}

	bool FreeCameraController::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool FreeCameraController::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, speed);
		JSON_READ(value, sensitivity);

		return false;
	}
}
