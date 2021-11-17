#include "Actor.h"
#include "Engine.h"
#include "Math/MathUtils.h"
#include "Graphics/Renderer.h"
#include "Component/GraphicsComponent.h"
#include <algorithm>

namespace glds
{
	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;

		transform =  other.transform;
		scene = other.scene;

		/*parent = other.parent;
		for (auto& child : children)
		{
			auto clone = child->Clone();
		}*/

		for (auto& component : other.components)
		{
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			clone->owner = this;
			clone->Create();
			AddComponent(std::move(clone));
		}
	}

	void Actor::Update(float dt)
	{
		if (!active) return;

		std::for_each(components.begin(), components.end(), [](auto& component) { component->Update(); });

		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
	}

	void Actor::Draw(Renderer* renderer)
	{
		if (!active) return;
		
		std::for_each(components.begin(), components.end(), [renderer](auto& component)
		{
			if (dynamic_cast<GraphicsComponent*>(component.get()))
			{
				dynamic_cast<GraphicsComponent*>(component.get())->Draw(renderer);
			}
		});

		std::for_each(children.begin(), children.end(), [renderer](auto& child) {child->Draw(renderer); });
	}

	void Actor::BeginContact(Actor* other)
	{
		Event event;

		event.name = "collision_enter";
		event.data = other;
		event.receiver = this;

		if(!destroy) scene->engine->Get<EventSystem>()->Notify(event);
	}

	void Actor::EndContact(Actor* other)
	{
		Event event;

		event.name = "collision_exit";
		event.data = other;
		event.receiver = this;

		if(!destroy) scene->engine->Get<EventSystem>()->Notify(event);
	}

	void Actor::AddChild(std::unique_ptr<Actor> actor)
	{
		actor->parent = this;
		children.push_back(std::move(actor));
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		components.push_back(std::move(component));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, name);
		JSON_READ(value, tag);

		if (value.HasMember("transform"))
		{
			transform.Read(value["transform"]);
		}

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& componentValue : value["components"].GetArray())
			{
				std::string type;
				JSON_READ(componentValue, type);
				auto component = ObjectFactory::Instance().Create<Component>(type);

				if (component)
				{
					component->owner = this;
					component->Read(componentValue);
					component->Create();
					AddComponent(std::move(component));
				}
			}
		}

		return true;
	}	
}