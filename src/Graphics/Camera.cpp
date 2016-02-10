/*
************************************
* Copyright (C) 2016 ByteForge
* Camera.cpp
************************************
*/

#include "Camera.hpp"
#include "../Core.hpp"
#include <iostream>

using namespace anvil;

Camera::Camera()
{
    m_up = glm::vec3(0.0, 1.0, 0.0);
	m_currentPos = glm::vec3(-30.0, 30.0, -30.0);
	m_lookat = glm::vec3(0.0, 0.0, 0.0);

    m_fov = 45.0;
    m_ratio = 800.0/600.0;
	m_proj = glm::perspective(m_fov, m_ratio, 0.1, 10000.0);

	m_frustum = std::make_unique<Frustum>();
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 dir)
{
	float timePassed = Core::GetCore()->GetTimer().GetElapsedTime() / 1e6;
	float speed = m_speed * timePassed;
	//add also the up direction
	glm::vec3 foreward = glm::vec3({ m_direction.x, 0.0, m_direction.z });
	glm::vec3 right = glm::vec3({ m_direction.z, 0.0, -m_direction.x });
	//glm::vec3 up = glm::vec3({  });
	glm::vec3 offset = (dir.x * right + dir.z * foreward) * speed * m_currentPos.y / 10.0f;
	m_currentPos += offset;
	m_lookat += offset;
}

void Camera::Move(Direction dir)
{
	glm::vec3 offset;
	float timePassed = Core::GetCore()->GetTimer().GetElapsedTime() / 1e6;
	float speed = m_speed * timePassed;
	switch (dir)
	{
	case FOREWARD:
		offset = glm::vec3({ m_direction.x, 0.0, m_direction.z }) * speed * m_currentPos.y / 10.0f;
		m_currentPos += offset;
		m_lookat += offset;
		break;
	case BACK:
		offset = glm::vec3({ m_direction.x, 0.0, m_direction.z }) * speed * m_currentPos.y / 10.0f;
		m_currentPos -= offset;
		m_lookat -= offset;
		break;
	case LEFT:
		offset = glm::vec3({ -m_direction.z, 0.0, m_direction.x }) * speed * m_currentPos.y / 10.0f;
		m_currentPos -= offset;
		m_lookat -= offset;
		break;
	case RIGHT:
		offset = glm::vec3({ m_direction.z, 0.0, -m_direction.x }) * speed * m_currentPos.y / 10.0f;
		m_currentPos -= offset;
		m_lookat -= offset;
		break;
	}
}

void Camera::Rotate(float angle)
{
	float timePassed = Core::GetCore()->GetTimer().GetElapsedTime() / 1e6;
	glm::vec3 delta = m_currentPos - m_lookat;
	m_currentPos = m_lookat + glm::rotateY(delta, angle * timePassed);
}

void Camera::Rotate(Direction dir)
{
	float angle = 5.0f;
	switch (dir)
	{
	case (LEFT) :
		Rotate(angle);
		break;
	case (RIGHT) :
		Rotate(-angle);
		break;
	}
}

void Camera::Zoom(Direction dir)
{
	float timePassed = Core::GetCore()->GetTimer().GetElapsedTime() / 1e6;
	switch (dir)
	{
	case ZOOM_OUT:
		m_currentPos -= m_direction * timePassed * 500.0f;
		break;
	case ZOOM_IN:
		if (m_currentPos.y > 3)
			m_currentPos += m_direction * timePassed * 500.0f;
		break;
	}
}

void Camera::Update()
{
	m_position = m_currentPos;
	m_direction = glm::normalize(m_lookat - m_position);
    m_view = glm::lookAt(m_position, m_lookat, m_up);
    m_vp = m_proj * m_view;

	m_frustum->Recalculate(m_view, m_proj);
}

//out_origin starts at the near plane NOT the camera position
void Camera::ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction)
{
	glm::vec2 resolution = Core::GetCore()->GetResolution();

	glm::vec4 ray_start((mouse_pos.x / resolution.x - 0.5f) * 2.0f, -(mouse_pos.y / resolution.y - 0.5f) * 2.0f, 0.0, 1.0);

	std::cout << ray_start.x << ", " << ray_start.y << std::endl;

	glm::vec4 temp = (glm::inverse(m_proj * m_view)) * ray_start;
	out_origin = glm::vec3(temp.x, temp.y, temp.z);
	out_direction = m_direction;
}