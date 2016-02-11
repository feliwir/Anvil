/*
************************************
* Copyright (C) 2016 ByteForge
* Texture.hpp
************************************
*/

#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include "../ITexture.hpp"
#include <GL/gl.h>

namespace anvil
{
    namespace GL
    {
        class Texture : public ITexture
        {
        public:
            ~Texture();
			Texture & operator=(const Texture&) = delete;

			void CreateArray(int size, int levels,int width, int height, const gli::format format);
			bool SetLevel(int level, const gli::texture& tex);
			bool Load(const gli::texture& tex);
            void Bind();
        private:
			GLuint CreateHandle(const gli::texture& tex);
            GLuint m_handle;
			GLenum m_target;

			static gli::gl GL;
        };
    }
}

