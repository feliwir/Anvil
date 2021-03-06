/*
************************************
* Copyright (C) 2016 ByteForge
* ITerrain.hpp
************************************
*/

#pragma once
#include "IRenderable.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace anvil
{
	class ITexture;
	class Quadtree;

	/**
	 * @class	ITerrain
	 *
	 * @brief	A terrain.
	 */
	class ITerrain : public IRenderable
	{
	public:

		/**
		 * @fn	ITerrain::ITerrain(std::uint32_t width, std::uint32_t height);
		 *
		 * @brief	Constructor.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		ITerrain(std::uint32_t width, std::uint32_t height);

		/**
		 * @fn	int ITerrain::GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);
		 *
		 * @brief	Gets mouse position in world space.
		 * 			
		 * @param	mousePos   	The mouse position.
		 * @param [in,out]	pos	The position.
		 *
		 * @return	The mouse position in world space.
		 */
		int GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);

		/**
		 * @fn	void ITerrain::SetMaterial(glm::vec3 &pos, float radius, int material);
		 *
		 * @brief	Sets a material.
		 *
		 * @param [in,out]	pos	The position.
		 * @param	radius	   	The radius.
		 * @param	material   	The material.
		 */
		void SetMaterial(glm::vec3 &pos, float radius, int material);

		/**
		 * @fn	void ITerrain::SetHeight(glm::vec3 &pos, float radius, float height);
		 *
		 * @brief	Sets a height.
		 *
		 * @param [in,out]	pos	The position.
		 * @param	radius	   	The radius.
		 * @param	height	   	The height.
		 */
		void SetHeight(glm::vec3 &pos, float radius, float height);


		/**
		* @fn	float ITerrain::GetHeight(float x, float y);
		*
		* @brief	Returns the terrain height at the position defined by x, y
		*
		* @param	x	   	the x position
		* @param	y	   	the y position
		*
		* @return   returns the height at the given point
		*/
		float GetHeight(float x, float y);
		
	protected:

		/**
		 * @fn	void ITerrain::Generate();
		 *
		 * @brief	Generates this object.
		 */
		void Generate();

		/**
		 * @fn	void ITerrain::ComputeNormals(std::vector<std::vector<glm::vec3>> &normals);
		 *
		 * @brief	Calculates the normals.
		 *
		 * @param [in,out]	normals	The normals.
		 */
		void ComputeNormals(std::vector<std::vector<glm::vec3>> &normals);

		/**
		 * @fn	void ITerrain::CreateHeightmap();
		 *
		 * @brief	Creates the heightmap.
		 */
		void CreateHeightmap();

		/**
		 * @fn	void ITerrain::UpdateBufferData();
		 *
		 * @brief	Updates the buffer data.
		 */
		void UpdateBufferData();

		/**
		 * @fn	void ITerrain::UpdateTextures();
		 *
		 * @brief	Updates the textures.
		 */
		void UpdateTextures();

	protected:
		glm::mat4 m_mod;

		std::shared_ptr<ITexture> m_diff;
		std::shared_ptr<ITexture> m_nrm;
		std::shared_ptr<ITexture> m_spec;
		std::shared_ptr<ITexture> m_disp;
		std::shared_ptr<ITexture> m_ambi;

		std::uint32_t m_width, m_height;
		std::vector<std::vector<float>> m_heightmap;
		std::vector<std::string> m_terrainMaterials;
		std::vector<std::vector<glm::vec3>> m_materialmap;
		std::shared_ptr<Quadtree> m_quadtree;

		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
		std::vector<std::uint32_t> m_faces;
		std::vector<glm::vec3> m_materials;
		bool heightmap_changed = true;
		bool uvs_changed = true;
		bool faces_changed = true;
		bool materials_changed = true;
	};
}