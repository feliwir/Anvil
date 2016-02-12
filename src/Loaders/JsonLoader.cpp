/*
************************************
* Copyright (C) 2016 ByteForge
* JsonLoader.cpp
************************************
*/

#include "JsonLoader.hpp"
#include "../Graphics/Material.hpp"
#include "../Core.hpp"
#include "../Loaders/Util.hpp"
#include "../Exception.hpp"
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace anvil;
using namespace rapidjson;

void JsonLoader::LoadMaterial(const std::string &name, const std::string &path)
{
	std::shared_ptr<Material> mat;

	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		throw AnvilException("Failed to open material file: " + name, __FILE__, __LINE__);
	IStreamWrapper isw(fin);
	Document d;
	d.ParseStream(isw);
	
	if (d.HasMember("material"))
	{
		mat = std::make_shared<Material>();
		if (d["material"].HasMember("displacement_factor"))
			mat->m_displacementFactor = d["material"]["displacement_factor"].GetDouble();
		if (d["material"].HasMember("diffuse"))
			mat->m_diffuseTexture = d["material"]["diffuse"].GetString();
		if (d["material"].HasMember("normal"))
			mat->m_normalTexture = d["material"]["normal"].GetString();
		if (d["material"].HasMember("specular"))
			mat->m_specularTexture = d["material"]["specular"].GetString();
		if (d["material"].HasMember("displacement"))
			mat->m_displacementTexture = d["material"]["displacement"].GetString();
		if (d["material"].HasMember("ambient_occ"))
			mat->m_ambientOccTexture = d["material"]["ambient_occ"].GetString();
	}
	else
		throw AnvilException("Material file has no material object", __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(toUpper(name), mat);
}

void JsonLoader::LoadEntity(const std::string &name, const std::string &path)
{
	std::shared_ptr<Entity> ent;

	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		throw AnvilException("Failed to open entity file: " + name, __FILE__, __LINE__);
	IStreamWrapper isw(fin);
	Document d;
	d.ParseStream(isw);

	if (d.HasMember("entity"))
	{
		if (d["entity"].IsObject())
		{
			if (d["entity"].HasMember("parent"))
				ent = std::make_shared<Entity>(Core::GetCore()->GetResources()->GetEntity(d["entity"]["parent"].GetString()));
			else
				ent = std::make_shared<Entity>();

			if (d["entity"].HasMember("model"))
				ent->m_model = Core::GetCore()->GetResources()->GetModel(d["entity"]["model"].GetString());

			if (d["entity"].HasMember("materials") && d["entity"]["materials"].IsArray())
			{
				for (int i = 0; i < d["entity"]["materials"].Size(); i++)
				{
					ent->m_materials.push_back(Core::GetCore()->GetResources()->GetMaterial(d["entity"]["materials"][i].GetString()));
				}
			}
		}
	}
	else
		throw AnvilException("Entity file has no entity object: " + path, __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(toUpper(name), ent);
}