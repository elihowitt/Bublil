#include "guiShader.h"

render::shaders::GUIShader::GUIShader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs.txt"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);//Adding each shader to the program.

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "[Error]: program failed to link!: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "[Error]: program is invalid!: ");

	m_uniforms[POS_U] = glGetUniformLocation(m_program, "pos");
	m_uniforms[SCALE_U] = glGetUniformLocation(m_program, "scale");
}

render::shaders::GUIShader::~GUIShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);

}

void render::shaders::GUIShader::update(const ShaderUpdatePack& pack)
{
	glm::vec3 pos = pack.vectors[0];
	glm::vec2 scale = pack.vectors[1];

	glUniform2fv(m_uniforms[POS_U], 1, &pos[0]);
	glUniform2fv(m_uniforms[SCALE_U], 1, &scale[0]);
}
