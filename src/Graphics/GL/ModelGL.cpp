/*
************************************
* Copyright (C) 2016 ByteForge
* ModelGL.cpp
************************************
*/

#include "ModelGL.hpp"
#include "MeshGL.hpp"
#include "../../Objects/Entity.hpp"
#include <iostream>
#include "../../Core.hpp"
#include "../Camera.hpp"
#include <glm/glm.hpp>
#include "../../Util.hpp"
#include <glm/gtc/type_ptr.hpp>


using namespace anvil;

GL::ModelGL::ModelGL()
{

}

GL::ModelGL::~ModelGL()
{

}

void GL::ModelGL::Render(IShader& shader)
{
	//glm::mat4 mod(1.0);
	for (Entity* e : m_entities)
	{
		if (e->GetInstances().size() > 0)
		{
			for (std::shared_ptr<Entity::Instance> i : e->GetInstances())
			{
				glUniformMatrix4fv(shader.GetUniform("mvp"), 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix()));
				glUniform4fv(shader.GetUniform("position"), 1, glm::value_ptr(glm::vec4(i->position, 1.0)));

				if (m_hierarchy != nullptr)
				{
					//glUniform1iv(shader.GetUniform("parentIDs"), sizeof(std::int16_t) *  m_hierarchy->GetParentIDs().size(), reinterpret_cast<GLint *>(m_hierarchy->GetParentIDs().data()));
					glUniformMatrix4fv(shader.GetUniform("pivots"), sizeof(glm::f32mat4x4) * m_hierarchy->GetPivots().size(), GL_FALSE, reinterpret_cast<GLfloat *>(m_hierarchy->GetPivots().data()));
					//glUniform3fv(shader.GetUniform("centerPos"), 1, glm::value_ptr(m_hierarchy->GetCenterPos()));
					//printMat(m_hierarchy->GetPivots().data()[0]);
					std::cout << sizeof(glm::f32mat4x4) << std::endl;
				}

				for (std::map<std::string, std::shared_ptr<IMesh>>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
				{					
					glActiveTexture(GL_TEXTURE0); //albedo textures
					e->GetMaterial(it->second->GetName())->GetAlbedoTexture()->Bind();
					glUniform1i(shader.GetUniform("albedoTex"), 0);

					it->second->Render(shader);
				}
			}
		}
	}
}

void GL::ModelGL::Update()
{
	for (Entity* e : m_entities)
	{
		e->Update();
	}
}
