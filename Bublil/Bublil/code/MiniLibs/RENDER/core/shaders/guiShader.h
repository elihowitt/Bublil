#pragma once
#include "RENDER\core\shader.h"
class GUIShader :
	public Shader
{
public:
	GUIShader(const std::string& filename);
	~GUIShader();

	virtual void update(const ShaderUpdatePack& pack)override;

protected:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		POS_U,
		SCALE_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

};

