/*
************************************
* Copyright (C) 2016 ByteForge
* Platform.cpp
************************************
*/

#include "Platform.hpp"
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#include <iostream>
#include "../Util.hpp"

using namespace anvil;

std::vector<std::string> IO::ListFiles(const std::string & dir, const std::string & ext)
{
	std::vector<std::string> files;
	fs::path path(dir);

	for (auto& dirEntry : fs::directory_iterator(path))
	{
		if ((dirEntry.path().extension() == ext||ext.size()==0)
			&&fs::is_regular_file(dirEntry.path()))
		{
			files.push_back(dirEntry.path().string());
		}
	}
	return files;
}

std::vector<std::string> IO::ListFilesRecursively(const std::string & dir, const std::string & ext)
{
	std::vector<std::string> files;
	fs::path path(dir);
	for (auto& dirEntry : fs::recursive_directory_iterator(path))
	{
		if ((dirEntry.path().extension() == ext || ext.size() == 0)
			&& fs::is_regular_file(dirEntry.path()))
		{
			files.push_back(dirEntry.path().string());
		}
	}

	return files;
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
void anvil::ShowError(const std::string & msg)
{
	#ifdef _WIN32
	MessageBox(NULL, msg.c_str(), "Error", MB_OK | MB_ICONERROR);
    #else
	std::cout << msg << std::endl;
    #endif

}