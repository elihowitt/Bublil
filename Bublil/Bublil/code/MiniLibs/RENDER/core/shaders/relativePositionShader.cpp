#include "relativePositionShader.h"

render::shaders::RelativePositionShader::RelativePositionShader(const std::string& filename)
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

	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[VIEWANDPROJECTION_U] = glGetUniformLocation(m_program, "viewAndProjection");
	m_uniforms[SKYCOLOUR_U] = glGetUniformLocation(m_program, "skyColour");
}

render::shaders::RelativePositionShader::~RelativePositionShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

void render::shaders::RelativePositionShader::update(const ShaderUpdatePack& pack)
{
	glm::mat4 model = pack.transforms[0].GetModel();
	glm::mat4 viewAndProjection = pack.camera->GetViewProjection();
	glm::vec3 skyColour = pack.vectors[1];

	glUniformMatrix4fv(m_uniforms[MODEL_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEWANDPROJECTION_U], 1, GL_FALSE, &viewAndProjection[0][0]);
	glUniform3fv(m_uniforms[SKYCOLOUR_U], 1, &skyColour[0]);
}
