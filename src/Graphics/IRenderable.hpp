/*
************************************
* Copyright (C) 2016 ByteForge
* IRenderable.hpp
************************************
*/

#pragma once
#include "IShader.hpp"

namespace anvil
{
	class IRenderable
	{
	public:
		virtual void Render(int mode) = 0;
		virtual void Update() = 0;
	};
}