#pragma once
#include "Component.h"
#include "Math/MathTypes.h"

namespace glds
{
	class PhysicsComponent : public Component
	{
	public:
		std::unique_ptr<Object> Clone() const override { return std::make_unique<PhysicsComponent>(*this); }

		void Update() override;
		virtual void ApplyForce(const glm::vec3& force) { acceleration += force; };

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 velocity;
		glm::vec3 acceleration;
		float damping{ 1 };
	};
}