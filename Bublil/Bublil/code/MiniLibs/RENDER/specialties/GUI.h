#pragma once

#include<GL/glew.h>
#include<string>
#include<glm/glm.hpp>
#include<iostream>
#include"quade.h"

class GUI
{
public:
	GUI(const std::string& texturefilename, const glm::vec2& position, const glm::vec2& scale);
	~GUI();		

	void Bind(unsigned int unit = 0);

	void Draw();
protected:
private:
	GLuint m_texture;

	Quade m_quade;

	glm::vec2 m_position;
	glm::vec2 m_scale   ;
public:
	glm::vec2& GetPos() { return m_position; }
	glm::vec2& GetScale() { return m_scale; }
};

