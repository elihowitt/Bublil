#pragma once

#include<string>

#include<glm\glm.hpp>

#include"ft2build.h"
#include FT_FREETYPE_H

#include"RENDER\core\shader.h"

#include"RENDER\specialties\quade.h"

namespace render
{
	class FontRendere
	{
	public:
		struct Character
		{
			GLuint TextureID;   // ID handle of the glyph texture
			glm::ivec2 Size;    // Size of glyph
			glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
			GLuint Advance;    // Horizontal offset to advance to next glyph
		};

		FontRendere(const std::string& fontFile, const unsigned int& numChars, const std::string& shaderFile);
		~FontRendere();

		void render(const std::string& message, const glm::vec2& start_position, const glm::mat2& rotation_scale);
	private:
		static FT_Library library;
		FT_Face face;
		Character* availableCharacters;
		Shader* shader;
		Quade quade;
	};
}