/*
************************************
* Copyright (C) 2016 ByteForge
* Functions.cpp
************************************
*/

#include <string>
#include <iostream>
#include "../Core.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Graphics.hpp"
#include "../GUI.hpp"
#include "../Graphics/IRenderer.hpp"

using namespace anvil;

#ifdef _MSC_VER 
#define SCRIPT_FUNC __declspec(dllexport)
#else
#define SCRIPT_FUNC
#endif

extern "C"
{
	SCRIPT_FUNC void LoadGUIByFile(const char* name)
	{
		auto& gui = Core::GetCore()->GetGUI();
		gui->LoadFile(name);
	}

	SCRIPT_FUNC void PrintRenderer()
	{
		auto renderer = Core::GetCore()->GetGraphics()->GetRenderer();
		renderer->PrintInfo();
	}

	SCRIPT_FUNC void AddModDir(const char* dir)
	{
		Core::GetCore()->GetResources()->AddModDir(dir);
	}
}
