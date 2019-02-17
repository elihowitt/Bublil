#pragma once

#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<iostream>
#include<fstream>
#include<GL/glew.h>

#include"RENDER\renderGloabals.h"

namespace render
{
	class Shader
	{
	public:
		Shader() {}

		void bind();
		virtual void update(const ShaderUpdatePack& pack) = 0;

		std::string LoadShader(const std::string& filename);///

		virtual ~Shader() {}


		static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
		static GLuint CreateShader(const std::string& text, GLenum shaderType);

	protected:
		GLuint m_program;
	};
}
#endif

