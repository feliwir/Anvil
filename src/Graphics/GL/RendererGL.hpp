/*
************************************
* Copyright (C) 2016 ByteForge
* RendererGL.hpp
************************************
*/

#pragma once
#include "../IRenderer.hpp"
#include "../../Types/Map.hpp"

namespace anvil
{
	/**
	 * @class	RendererGL
	 *
	 * @brief	A renderer gl.
	 */
	class RendererGL : public IRenderer
	{
	public:

		/**
		 * @fn	RendererGL::RendererGL();
		 *
		 * @brief	Default constructor.
		 */
		RendererGL();

		/**
		 * @fn	RendererGL::~RendererGL();
		 *
		 * @brief	Destructor.
		 */
		~RendererGL();

		/**
		 * @fn	void RendererGL::Clear();
		 *
		 * @brief	Clears this object to its blank/initial state.
		 */
		void Clear();

		/**
		 * @fn	void RendererGL::Render(const glm::mat4& ortho);
		 *
		 * @brief	Renders the given ortho.
		 *
		 * @param	ortho	The ortho.
		 */
		void Render(const glm::mat4& ortho);

		/**
		 * @fn	void RendererGL::Resize(int width, int height);
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void Resize(int width, int height);

		/**
		 * @fn	void RendererGL::PrintInfo();
		 *
		 * @brief	Print information.
		 */
		void PrintInfo();

		/**
		 * @fn	int RendererGL::GetTotalVRAM();
		 *
		 * @brief	Gets total VRAM.
		 *
		 * @return	The total VRAM.
		 */
		int GetTotalVRAM();

		/**
		 * @fn	int RendererGL::GetUsedVRAM();
		 *
		 * @brief	Gets used VRAM.
		 *
		 * @return	The used VRAM.
		 */
		int GetUsedVRAM();

		/**
		 * @fn	const std::string RendererGL::GetGPUName();
		 *
		 * @brief	Gets GPU name.
		 *
		 * @return	The GPU name.
		 */
		const std::string GetGPUName();

	private:
		int m_totalVRAM;
		std::string m_deviceName;
	};
}