#include "Engine.h"
#include "Object/Actor.h"

namespace glds
{
	void ModelComponent::Update()
	{

	}

	void ModelComponent::Draw(Renderer* renderer)
	{
		material->shader->SetUniform("model", owner->transform.matrix);
		auto actor = owner->scene->FindActor("camera");
		if (actor != nullptr)
		{
			material->shader->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			material->shader->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
		}

		material->Set();
		model->Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		JSON_READ(value, model_name);
		model = owner->scene->engine->Get<glds::ResourceSystem>()->Get<glds::Model>(model_name);

		std::string material_name;
		JSON_READ(value, material_name);
		material = owner->scene->engine->Get<glds::ResourceSystem>()->Get<glds::Material>(material_name, owner->scene->engine);

		return true;
	}
}
