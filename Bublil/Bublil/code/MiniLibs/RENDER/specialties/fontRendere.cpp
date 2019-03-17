#include "fontRendere.h"



render::specialties::FontRendere::FontRendere(const std::string& fontFile, const unsigned int& numChars, const std::string& shaderFile)
{
	if (FT_Init_FreeType(&library) != FT_Err_Ok)
		lg::cwout::generalLog("FT_ERROR", "Failed to initialize library");

	if (FT_New_Face(library, fontFile.c_str(), 0, &face) != FT_Err_Ok)
		lg::cwout::generalLog("FT_ERROR", "Failed to load face - " + '"' + fontFile + '"');
	
	//Init array and load all characters:
	availableCharacters = new Character[numChars];
	for (unsigned int i = 0; i < numChars; ++i)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER) != FT_Err_Ok)
		{
			lg::cwout::generalLog("FT_ERROR", "Failed to load Glyph - " + (char)('a' + i));
			continue;
		}

		Character c;
		
		c.buffer = face->glyph->bitmap.buffer;
		c.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		c.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		c.advance = face->glyph->advance.x;
		
		availableCharacters[i] = c;
	}

	shader = new render::shaders::GUIShader(shaderFile);
}


render::specialties::FontRendere::~FontRendere()
{
	delete[] availableCharacters;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void render::specialties::FontRendere::render(const std::string & message, const glm::vec2 & start_position, const glm::vec3 & rotation, const glm::vec3& scale)
{
	render::ShaderUpdatePack up;
	up.transforms.push_back(render::Transform(glm::vec3(start_position, 1), rotation, scale));

	shader->bind();
	shader->update(up);
	
	//Create bitmap texture contating string.

}
