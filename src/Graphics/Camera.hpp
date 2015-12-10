//
// Created by stephan on 08.12.15.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace hpse
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void Update();

        inline const glm::mat4& GetViewProjectionMatrix()
        {
            return m_vp;
        }

        inline void SetFOV(double fov)
        {
            m_fov = fov;
        }

        inline void SetRatio(double ratio)
        {
            m_ratio = ratio;
        }

        inline void SetPosition(glm::vec3 pos)
        {
            m_pos = pos;
        }

		inline void Move(glm::vec3 direction)
		{
			m_pos += direction * speed; //* delta_time
		}

    private:
        glm::vec3 m_pos;
        glm::vec3 m_lookat;
        glm::vec3 m_up;
        glm::quat m_rotation;
        double m_fov;
        double m_ratio;

		float speed = 3.0f; // 3 units / second

        glm::mat4 m_proj;
        glm::mat4 m_view;
        glm::mat4 m_vp;
    };
}


