#pragma once

#include<string>
#include<vector>

#include"RENDER/core/shader.h"
#include"RENDER/core/camera.h"

#include"RENDER/loading/stb_image.h"

class Skybox
{
public:
	Skybox(const std::string& shader, const std::string& texPath, const std::string& prefix, const std::string& suffix);
	~Skybox();

	void Bind();
	void Update(const Camera& camera);
	void Render();
private:
	Shader *shader;

	GLuint texture;

	GLuint VAO, VBO;
};

