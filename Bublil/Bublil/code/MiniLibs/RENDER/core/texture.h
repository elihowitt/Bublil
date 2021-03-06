#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include<string>
#include<GL/glew.h>
namespace render
{
	class Texture
	{
	public:
		Texture(const std::string& filename);

		void Bind(unsigned int unit);

		virtual ~Texture();
	protected:
	private:
		Texture(const Texture& other) {}
		Texture&operator=(const Texture& other) {}

		GLuint m_texture;
	};
}
#endif 