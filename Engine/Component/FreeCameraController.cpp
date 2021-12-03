#include "FreeCameraController.h"
#include "Engine.h"

void glds::FreeCameraController::Update()
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
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == glds::InputSystem::eKeyState::Held) direction.x = -1;
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == glds::InputSystem::eKeyState::Held) direction.x = 1;
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == glds::InputSystem::eKeyState::Held) direction.z = -1;
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_S) == glds::InputSystem::eKeyState::Held) direction.z = 1;
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_E) == glds::InputSystem::eKeyState::Held) direction.y = 1;
	if (owner->scene->engine->Get<glds::InputSystem>()->GetKeyState(SDL_SCANCODE_Q) == glds::InputSystem::eKeyState::Held) direction.y = -1;

	glm::quat rotation{ owner->transform.rotation };

	owner->transform.position += rotation * direction * speed * owner->scene->engine->time.deltaTime;
}

bool glds::FreeCameraController::Write(const rapidjson::Value& value) const
{
	return false;
}

bool glds::FreeCameraController::Read(const rapidjson::Value& value)
{
	return false;
}
