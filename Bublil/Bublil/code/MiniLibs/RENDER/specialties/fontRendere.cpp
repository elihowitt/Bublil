#include "fontRendere.h"

/*
Right now loading glyphs gives no errors but it doent work -
 they are given null values for everything.
 It does show up on the screen sometimes (why not everytime?!)
 as a black rectangle, strange but good.
Needs looking into...
*/



bool render::specialties::FontRenderer::libraryInitialized = false;

//Assumes buffer&size are initialized.
static void InitTexture(render::specialties::FontRenderer::Character& c);

render::specialties::FontRenderer::FontRenderer(const std::string& fontFile, const unsigned int& numChars, const std::string& shaderFile)
{
	if (!libraryInitialized)
	{
		if (FT_Init_FreeType(&library) != FT_Err_Ok)
		{
			lg::cwout::generalLog("FT_ERROR", "Failed to initialize library");
			lg::dbout::basicLog(L"Failed to initialize library");
			fileOutputLog.logRuntimeEvent("FT_ERROR", "Failed to initialize library");
		}
		else
			libraryInitialized = true;
	}
	if (FT_New_Face(library, fontFile.c_str(), 0, &face) != FT_Err_Ok)
	{
		lg::cwout::generalLog("FT_ERROR", "Failed to load face - " + '"' + fontFile + '"');
		lg::dbout::basicLog(L"Failed to initialize face");
		fileOutputLog.logRuntimeEvent("FT_ERROR", "Failed to initialize face");
	}
	//Set pixel size to load Glyphs as.
	FT_Set_Pixel_Sizes(face, 0, 12);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	//Init array and load all characters:
	availableCharacters = new Character[numChars];
	for (unsigned int i = 0; i < numChars; ++i)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER) != FT_Err_Ok)
		{
			lg::cwout::generalLog("FT_ERROR", "Failed to load Glyph - " + (char)('a' + i));
			lg::dbout::basicLog(L"Failed to load Glyph - " + (char)('a' + i));
			fileOutputLog.logRuntimeEvent("FT_ERROR", "Failed to load Glyph - " + (char)('a' + i));
			continue;
		}

		Character c;
		
		c.buffer = face->glyph->bitmap.buffer;
		c.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		c.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		c.advance = face->glyph->advance.x;
		
		//Figure texture part:
		glGenTextures(1, &c.textureID);
		glBindTexture(GL_TEXTURE_2D, c.textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, c.size.x, c.size.y, 0, GL_RED, GL_UNSIGNED_BYTE, c.buffer);

		//Add to list.
		availableCharacters[i] = c;
	}

	shader = new render::shaders::GUIShader(shaderFile);
}


render::specialties::FontRenderer::~FontRenderer()
{
	delete[] availableCharacters;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void render::specialties::FontRenderer::SaveSentance(const SAVED_SENTANCE & id, const std::string & data)
{
}

void render::specialties::FontRenderer::renderSaved(const SAVED_SENTANCE & sentance, const glm::vec2 & start_position, const glm::vec3 & rotation, const glm::vec2 & scale)
{
	frame.GetPos() = start_position;
	frame.GetRot() = rotation;
	frame.GetScale() = scale;

	frame.setTextureID(sentance_texture_map[sentance]);

	renderCurrent(true);
}

void render::specialties::FontRenderer::render(const std::string & message, const glm::vec2 & start_position, const glm::vec3 & rotation, const glm::vec2& scale)
{
	frame.GetPos() = start_position;
	frame.GetRot() = rotation;
	frame.GetScale() = scale;
	
	frame.Bind();
	shader->bind();

	//Where on the line are we.
	glm::vec2 pen = start_position;
	//Current character.
	Character c;
	//Loop through all letters and render each quade separetly.
	for (int i = 0; i < message.size(); ++i)
	{
		//Next character.
		c = availableCharacters[message[i] - 'a'];

		//Set frame position and texture.
		frame.GetPos().x = pen.x + c.bearing.x*scale.x;
		frame.GetPos().y = pen.y + c.bearing.y*scale.y;
		frame.setTextureID(c.textureID);

		//Draw.
		renderCurrent(false);

		//Progress pen.
		pen.x += (c.advance >> 6)*scale.x; // Bitshift by 6 to get value in pixels (FT is weird).
	}
}

void render::specialties::FontRenderer::renderCurrent(const bool& to_bind)
{
	if (to_bind)
	{
		shader->bind();
		frame.Bind();
	}
	
	updatePack.transforms.clear();
	updatePack.transforms.push_back(Transform(glm::vec3(frame.GetPos(), 1), frame.GetRot(), glm::vec3(frame.GetScale(), 1)));
	shader->update(updatePack);
	frame.Draw();
}

void InitTexture(render::specialties::FontRenderer::Character & c)
{
	glGenTextures(1, &c.textureID);
}
