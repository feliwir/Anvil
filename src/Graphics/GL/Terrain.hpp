//
// Created by stephan on 14.12.15.
//

#pragma once
#include "../ITerrain.hpp"
#include "../ITexture.hpp"
#include "../Quadtree.hpp"
#include "../Material.hpp"
#include "Buffer.hpp"
#include "flextGL.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace hpse
{
    namespace GL
    {
        class Terrain : public ITerrain
        {
        public:
            Terrain(std::uint32_t width, std::uint32_t height);
			~Terrain();
			
            void Render(int mode);
            void Update();
        private:
			//rendering stuff
			std::vector<GLuint> m_tessLevelIDs, m_lightIDs;

			std::shared_ptr<ITexture> m_diff;
			std::shared_ptr<ITexture> m_nrm;
			std::shared_ptr<ITexture> m_spec;
			std::shared_ptr<ITexture> m_disp;
			std::shared_ptr<ITexture> m_ambi;

			std::vector<GLuint> m_diffIDs, m_nrmIDs, m_specIDs, m_dispIDs, m_ambiIDs;

			glm::mat4 m_mvp;
			glm::mat4 m_mod;
			glm::mat3 m_mv3x3;

			std::vector<GLuint> m_matrixIDs, m_modelMatrixIDs, m_viewMatrixIDs, m_modelView3x3MatrixIDs;

			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_fbo, m_mbo;
        };
    }
}




