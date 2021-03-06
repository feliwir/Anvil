/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.hpp
************************************
*/

#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "Entity.hpp"
#include <vector>
#include <memory>

namespace anvil
{
	class Material;

	/**
	* @class	Instance
	*
	* @brief	An instance of an entity object
	*/
	class Instance : public std::enable_shared_from_this<Instance>
	{
	public:
		/**
		* @fn	Instance::Instance(std::shared_ptr<Entity> entity, glm::vec3 &position);
		*
		* @brief	Default constructor.
		* @param	entity	the entity this instance is for
		* @param	position	the position of this instance
		*/
		Instance(std::shared_ptr<Entity> entity, const glm::vec3 &position,
			const glm::vec3 &euler = glm::vec3(0.0, 0.0, 0.0), const float scale = 0.0f);

		/**
		* @fn	Instance::~Instance();
		*
		* @brief	Default destructor.
		*/
		~Instance();

		/**
		* @fn	void Instance::Init();
		*
		* @brief	initialize the instance with states and set start values
		*/
		void Init();

		/**
		* @fn	void Instance::Unlink();
		*
		* @brief	unlinks this instance from its model
		*/
		void Unlink();

		/**
		* @fn	bool Instance::Update();
		*
		* @brief	Updates this instance.
		*
		* @return	returns false if the instance is invalid (should be deleted).
		*/
		bool Update();

		/**
		* @fn	std::shared_ptr<Material> Instance::GetMaterial();
		*
		* @brief	returns the material for the given mesh name
		* @param	meshName	the name of the mesh we want the material for
		* @return	returns a pointer to the material
		*/
		std::shared_ptr<Material> GetMaterial(const std::string& meshName);

		/**
		* @fn	void Instance::SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state);
		*
		* @brief	sets the current ModelConditionState of this instance
		* @param	state	the new state
		*/
		void SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state);

		/**
		* @fn	void Instance::SetAnimationState(std::shared_ptr<Entity::AnimationState> state);
		*
		* @brief	sets the current AnimationState of this instance
		* @param	state	the new state
		*/
		void SetAnimationState(std::shared_ptr<Entity::AnimationState> state);

		inline void SetHealth(int health) { m_health = health; }
		inline void Move() { m_m = glm::translate(m_direction * m_entity->GetSpeed() * (m_deltaTime / 1000.0f)) * m_m; }
		inline void SetPosition(glm::vec3 position) { m_m[3][0] = position.x; m_m[3][1] = position.y; m_m[3][2] = position.z; }
		inline glm::vec3 GetPosition() { return glm::vec3(m_m[3][0], m_m[3][1], m_m[3][2]); }
		inline void SetDirection(glm::vec3 direction) { m_direction = direction; }
		inline void SetHeight(float height) { m_m[3][1] = height; }
		inline void Rotate(glm::vec3 euler) { 
			Rotate(euler.x, glm::vec3(1.0, 0.0, 0.0)); 
			Rotate(euler.y, glm::vec3(0.0, 1.0, 0.0));
			Rotate(euler.z, glm::vec3(0.0, 0.0, 1.0));
		}
		inline void Rotate(float angle, glm::vec3 axis) { m_m = glm::rotate(m_m, glm::radians(angle), axis); }
		inline void Scale(float scale) { m_m = m_m * glm::scale(glm::vec3(scale, scale, scale)); }
		inline void Scale(glm::vec3 scale) { m_m = m_m * glm::scale(scale); }
		inline glm::mat4 GetMatrix() { return m_m; }
		inline std::shared_ptr<Entity::ModelConditionState> GetModelConditionState() { return m_modelConditionState; }
		inline std::shared_ptr<Animation> GetAnimation() { return m_animationState->animations[m_animationIndex].animation; }
		inline const long long GetAnimationTime() { return m_animationTime; }
		inline bool IsAnimated() { return m_animationState != nullptr; }
		inline bool IsUnit() { return m_entity->GetKindOfs().UNIT; }
		inline bool IsVisible() { return m_visible; }
		inline glm::vec2 GetTexOffset(float u, float v) { m_texOffset += glm::vec2(m_deltaTime/1000.f * u, m_deltaTime/1000.f * v); return m_texOffset; }
		inline void SetInvalid() { m_valid = false; Unlink(); }
		inline bool IsValid() { return m_valid; }

	private:
		bool m_valid = true;
		bool m_visible = false;
		bool m_firstUpdate = true;
		glm::vec3 m_direction;
		glm::vec2 m_texOffset = glm::vec2(0.0f, 0.0f);
		long long m_deltaTime;
		std::chrono::high_resolution_clock::time_point m_lastUpdated;
		long long m_animationTime = 0;
		std::shared_ptr<Entity> m_entity;
		int m_health;
		glm::mat4 m_m;
		std::shared_ptr<Entity::ModelConditionState> m_modelConditionState;
		std::shared_ptr<Entity::AnimationState> m_animationState;
		int m_animationIndex = 0;
	};
}
