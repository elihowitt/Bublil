#include "GUI.h"
#include<cassert>
#include"RENDER/loading/stb_image.h"

static bool InitTexture(const std::string& filename, GLuint& tex);

render::specialties::GUI::GUI(const std::string& texfile, const glm::vec2& position, const glm::vec2& scale)
{
	m_position = position;
	m_scale = scale;
	if(!InitTexture(texfile, m_texture))
		std::cout<<"[Error] : image information failed to load for file: " << texfile << std::endl; 
}
static bool InitTexture(const std::string& filename, GLuint& tex)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		return false;


	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	return true;
}

render::specialties::GUI::~GUI()
{
	glDeleteTextures(1, &m_texture);
}

void render::specialties::GUI::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void render::specialties::GUI::Draw()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_quade.Draw();
	
	glDisable(GL_BLEND);

	glEnable  (GL_CULL_FACE);
	glCullFace(GL_BACK); 
	glEnable(GL_DEPTH_TEST);
}
