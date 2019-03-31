#pragma once

#include<string>

#include<glm\glm.hpp>

#include"ft2build.h"
#include FT_FREETYPE_H

#include"RENDER\core\shader.h"

#include"RENDER\specialties\quade.h"

#include"RENDER\specialties\GUI.h"
#include"RENDER\core\shaders\guiShader.h"

#include"LOGGER\logger.h"

#include<map>

/*
This is the idea:
	For most cases we render sentances we know we will use in the future
	and dont need to be created many times - 
	so we'll setup all those sentances in the begining and save thier texture for further use.

	Other cases like when someone types in the chat then we'll just draw many quades of
	the used letters separetly.
*/
namespace render
{
	namespace specialties
	{
		class FontRenderer
		{
		public:
			struct Character
			{
				GLuint textureID;   // ID handle of the glyph texture

				unsigned char* buffer;	//glyph actual data.
				glm::ivec2 size;    // Size of glyph
				glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
				GLuint advance;    // Horizontal offset to advance to next glyph
			};

			enum SAVED_SENTANCE
			{
				SAVED_HELLOWORLD
			};


			FontRenderer(const std::string& fontFile, const unsigned int& numChars, const std::string& shaderFile);
			~FontRenderer();

			//Initializing a saved sentance.
			void SaveSentance(const SAVED_SENTANCE& id, const std::string& data);

			//Rendering saved sentance.
			void renderSaved(const SAVED_SENTANCE& sentance, const glm::vec2 & start_position, const glm::vec3 & rotation, const glm::vec2& scale);

			//Rendering non-saved sentance.
			void render(const std::string & message, const glm::vec2 & start_position, const glm::vec3 & rotation, const glm::vec2& scale);
		private:
			static bool libraryInitialized;
			FT_Library library;
			FT_Face face;
			Character* availableCharacters;
			Shader* shader;
			GUI frame;

			lg::fout fileOutputLog;

			ShaderUpdatePack updatePack;
			std::map<SAVED_SENTANCE, GLuint> sentance_texture_map;
			
			void renderCurrent(const bool& to_bind = true);
		};
	}
}