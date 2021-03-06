/*
************************************
* Copyright (C) 2016 ByteForge
* MeshGL.hpp
************************************
*/

#pragma once
#include "../IMesh.hpp"
#include "flextGL.h"
#include "BufferGL.hpp"
#include <memory>

namespace anvil
{
	namespace GL
	{
		/**
		 * @class	MeshGL
		 *
		 * @brief	A mesh gl.
		 */
		class MeshGL : public IMesh
		{
		public:

			/**
			 * @fn	MeshGL::MeshGL();
			 *
			 * @brief	Default constructor.
			 */
			MeshGL();

			/**
			* @fn	MeshGL::~MeshGL();
			*
			* @brief	Default destructor.
			*/
			~MeshGL();

			/**
			 * @fn	void MeshGL::Render(IShader& shader, bool minimal);
			 *
			 * @brief	Renders the given shader.
			 *
			 * @param [in,out]	shader	The shader.
			 * @param	minimal	if it should render with minimal settings
			 */
			size_t Render(IShader& shader, bool minimal);

			/**
			* @fn	virtual void IMesh::Init() = 0;
			*
			* @brief	Initializes the Mesh for rendering.
			*/
			void Init();

		private:
			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_infbo, m_fbo;
		};
	}
}