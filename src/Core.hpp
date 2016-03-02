/*
************************************
* Copyright (C) 2016 ByteForge
* Core.hpp
************************************
*/

#pragma once
#ifdef ANVIL_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Graphics.hpp"
#include "Script.hpp"
#include "GUI.hpp"
#include "Audio.hpp"
#include "Types/Map.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Frustum.hpp"
#include "Util/Timer.hpp"
#include "Util/FPS.hpp"
#include "Input.hpp"

namespace anvil
{
	class Core
	{
	public: 

		/**
		 * @fn	Core::Core();
		 *
		 * @brief	Initialize all subsystems of the engine
		 */
		Core();

		/**
		 * @fn	Core::~Core();
		 *
		 * @brief	Delete all subsystems
		 */
		~Core();

		/**
		 * @fn	void Core::Run();
		 *
		 * @brief	Runs the engine
		 */
		void Run();

		inline std::unique_ptr<GUI>& GetGUI()
		{
			return m_gui;
		}

		inline std::unique_ptr<Script>& GetScript()
		{
			return m_script;
		}

		inline std::unique_ptr<Graphics>& GetGraphics()
		{
			return m_graphics;
		}

		inline std::unique_ptr<ResourceHandler>& GetResources()
		{
			return m_resources;
		}

		inline std::unique_ptr<Map>& GetMap()
		{
			return m_map;
		}

		inline std::unique_ptr<Camera>& GetCamera()
		{
			return m_camera;
		} 

		inline std::unique_ptr<Input>& GetInput()
		{
			return m_input;
		}

		inline glm::vec2 GetResolution()
		{
			
			return m_resolution;
		}

		inline GLFWwindow* GetWindow()
		{
			return m_window;
		}

		inline void Quit()
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		static inline Core* GetCore()
		{
			return m_instance;
		}

		Util::Timer& GetTimer()
		{
			return m_timer;
		}

		Util::FPS& GetFPS()
		{
			return m_fps;
		}

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, int key, int action, int mods);
		static void MousePosCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double x, double y);
		static void ErrorCallback(int error, const char* description);
		static void ResizeCallback(GLFWwindow* window, int width, int height);
	private:
		static Core* m_instance;

		GLFWwindow* m_window;
		std::unique_ptr<ResourceHandler> m_resources;
		std::unique_ptr<Graphics> m_graphics;
		std::unique_ptr<GUI> m_gui;
		std::unique_ptr<Script> m_script;
		std::unique_ptr<Audio> m_audio;
		std::unique_ptr<Map> m_map;
		std::unique_ptr<Camera> m_camera;
		std::unique_ptr<Frustum> m_frustum;
		std::unique_ptr<Input> m_input;
		Util::Timer m_timer;
		Util::FPS m_fps;
		glm::vec2 m_resolution;
	};
}