#include "skyboxShader.h"

SkyboxShader::SkyboxShader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs.txt"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".fs.txt"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);//Adding each shader to the program.

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "[Error]: program failed to link!: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "[Error]: program is invalid!: ");

	m_uniforms[MODEL_U] = glGetUniformLocation(m_program, "model");
	m_uniforms[VIEWANDPROJECTION_U] = glGetUniformLocation(m_program, "viewAndProjection");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "viewMat");
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "projectionMat");
	m_uniforms[NORMALMAT_U] = glGetUniformLocation(m_program, "normalMatrix");
	m_uniforms[LIGHTVEC_U] = glGetUniformLocation(m_program, "lightVec");
	m_uniforms[SKYCOLOUR_U] = glGetUniformLocation(m_program, "skyColour");

}

SkyboxShader::~SkyboxShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);

}

void SkyboxShader::update(const ShaderUpdatePack& pack)
{
	glm::mat4 viewMat = glm::mat4(glm::mat3(pack.camera->GetView()));
	glm::mat4 projectionMat = pack.camera->GetProjection();

	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &viewMat[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, &projectionMat[0][0]);
}


