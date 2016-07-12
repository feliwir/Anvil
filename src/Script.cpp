/*
************************************
* Copyright (C) 2016 ByteForge
* Script.cpp
************************************
*/

#include "Script.hpp"
#include "Environment.hpp"
#include <fstream>
#include <iostream>

using namespace anvil;

Script::Script()
{
	m_state = luaL_newstate();  //crash on mac, if not linked with "-pagezero_size 10000 -image_base 100000000"
	luaL_openlibs(m_state);
}

Script::~Script()
{
	lua_close(m_state);
}

void Script::Update()
{
	
}

void Script::LoadFile(const std::string& file)
{
	if (luaL_dofile(m_state, file.c_str()))
	{
		std::cout << lua_tostring(m_state, -1) << std::endl;
	}
}
	