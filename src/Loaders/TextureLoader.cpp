#include "TextureLoader.hpp"

#include <iostream>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <gli/load.hpp>
#include "../Graphics.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Core.hpp"

using namespace std;
using namespace hpse;

void TextureLoader::Load(const std::string& name)
{
	cout << "loading texture: " << name << endl;
	std::string path = "textures/";
	std::string ext = ".ktx";

	gli::texture Texture = gli::load(path + name + ext);
	if (Texture.empty())
	{
		return;
	}

	auto tex = Core::GetGraphics()->GetTexture();
	std::shared_ptr<IResource> p(tex.get());
	Core::GetResources()->AddResource(name, p);
}
