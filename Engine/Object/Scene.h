#pragma once
#include "Object.h"
#include "Core/Serializable.h"
#include <list>
#include <string>
#include <vector>
#include <memory>

namespace glds
{
	class Actor;
	class Engine;

	class Scene : public Object, public ISerializable
	{
	public:
		void Update(float dt);
		void Draw(class Renderer* renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveActor(Actor* actor);
		void RemoveAllActors();

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		Actor* FindActor(const std::string& name);

		template<typename T>
		T* GetActor();

		template<typename T>
		std::vector<T*> GetActors();

	public:
		Engine* engine{nullptr};
		std::string name;

	private:
		std::vector<std::unique_ptr<Actor>> newActors;
		std::vector<std::unique_ptr<Actor>> actors;
	};

	template<typename T>
	T* Scene::GetActor()
	{
		for (auto& actor : actors)
		{
			if (dynamic_cast<T*>(actor.get())) return dynamic_cast<T*>(actor.get());
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActors()
	{
		std::vector<T*> result;
		
		for (auto& actor : actors)
		{
			if (dynamic_cast<T*>(actor.get()))
			{
				result.push_back(dynamic_cast<T*>(actor.get()));
			}
		}
		
		return result;
	}
}