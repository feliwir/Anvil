#include "IShader.hpp"
#include "../Util/Watchdog.h"
#include <iostream>
using namespace anvil;
namespace fs = boost::filesystem;

IShader::IShader() : m_tracked(false)
{

}

void IShader::Load(const std::string &vertShader, const std::string &fragShader)
{
	LoadShader(vertShader, ANVIL_VERT_SHADER);
	LoadShader(fragShader, ANVIL_FRAG_SHADER);
}

void IShader::Load(const std::string &vertShader, const std::string& geoShader, const std::string &fragShader)
{
	LoadShader(vertShader, ANVIL_VERT_SHADER);
	LoadShader(geoShader,  ANVIL_GEOM_SHADER);
	LoadShader(fragShader, ANVIL_FRAG_SHADER);
}

void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader)
{
	LoadShader(vertShader,			ANVIL_VERT_SHADER);
	LoadShader(tessControlShader,	ANVIL_TESC_SHADER);
	LoadShader(tessEvalShader,		ANVIL_TESE_SHADER);
	LoadShader(fragShader,			ANVIL_FRAG_SHADER);
}

void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader)
{
	LoadShader(vertShader,			ANVIL_VERT_SHADER);
	LoadShader(tessControlShader,	ANVIL_TESC_SHADER);
	LoadShader(tessEvalShader,		ANVIL_TESE_SHADER);
	LoadShader(geoShader,			ANVIL_GEOM_SHADER);
	LoadShader(fragShader,			ANVIL_FRAG_SHADER);
}

void IShader::LoadShader(const std::string& file, const ShaderType type)
{
	auto reload = [this](const fs::path &path) {
		if (m_tracked)
		{
			std::cout << path << "needs recompile" << std::endl;
			m_shouldReload.push_back(path.string());
		}
	};

	if (!m_tracked)
	{
		wd::watch(fs::path(file), reload);
		m_files[file] = type;
	}
}

void IShader::Ready()
{
	m_tracked = true;
}


void IShader::Update()
{
	for (const auto& file : m_shouldReload)
	{
		Reload(file);
	}
	if (m_shouldReload.size() > 0)
	{
		Compile();
		m_shouldReload.clear();
	}

	
}