#include"RENDER\core\display.h"
#include"RENDER\core\camera.h"
#include"RENDER\renderManager.h"

#include"INPUT\inputDetection.h"

#include"LOGGER\logger.h"

#include"SDL2\SDL.h"

#include"RENDER\specialties\fontRendere.h"

#include"freetype\ft2build.h"
#include FT_FREETYPE_H

#include"../res/directories/resourceDirectories.h"

#define HEIGHT	600
#define WIDTH	800

#undef main

int main()
{
	render::Display display(WIDTH, HEIGHT, "Font test");

	std::string meshs[render::MESHLIST::NUM_MESHES];
	std::string textures[render::TEXTURELIST::NUM_TEXTURES];
	std::string shaders[render::SHADERLIST::NUM_SHADERES];

	meshs[render::MESHLIST::MESH_TREE] = directories::resources::models::DIR_TREE;
	meshs[render::MESHLIST::MESH_POKEBALL] = directories::resources::models::DIR_FOX;
	textures[render::TEXTURELIST::TEXTURE_TREE] = directories::resources::textures::DIR_TREE;
	textures[render::TEXTURELIST::TEXTURE_POKEBALL] = directories::resources::textures::DIR_FOX;
	shaders[render::SHADERLIST::GENERAL_SHADER] = directories::resources::shaders::DIR_GENERAL;
	shaders[render::SHADERLIST::RELATIVEPOSITION_SHADER] = directories::resources::shaders::DIR_RELATIVEPOSITION;

	render::RenderManager renderManager(meshs, textures, shaders);

	glm::vec3 skyVec(0.5, 0.25, 0.75);

	input::InputDetector inDetec;

	render::Camera camera(glm::vec3(0, 0, 0), 70.f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000);

	glm::vec3 lightVec(glm::normalize(glm::vec3(2, 1, 7)));

	render::Drawable treeDrawable;
	{
		treeDrawable.updatePack.transforms.push_back(render::Transform());
		treeDrawable.updatePack.transforms[0].GetPos() = glm::vec3(0, -2, 5);
		treeDrawable.updatePack.transforms[0].GetScale() = glm::vec3(1, 1, 1);
		treeDrawable.updatePack.camera = &camera;
		treeDrawable.updatePack.vectors.push_back(lightVec);
		treeDrawable.updatePack.vectors.push_back(skyVec);

		treeDrawable.renderPack.mesh_id = render::MESHLIST::MESH_TREE;
		treeDrawable.renderPack.texture_id = render::TEXTURELIST::TEXTURE_TREE;
		treeDrawable.renderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;
	}

	float turnFactor = 0.5f;
	float movementSpeed = 5.f;


	render::specialties::FontRenderer fontRender(directories::resources::fonts::DIR_AGEO, 128, directories::resources::shaders::DIR_GUI);
	//fontRender.SaveSentance(render::specialties::FontRenderer::SAVED_SENTANCE::SAVED_HELLOWORLD, "hello world sentance");


	//
	///
	//
	/*{
		FT_Library ft_library;
		FT_Error ft_error = FT_Init_FreeType(&ft_library);
		if (ft_error != FT_Err_Ok)
		{
			lg::dbout::basicLog(L"[FT_ERROR]: Initializing library");
			return 1;
		}

		FT_Face ft_face;
		ft_error = FT_New_Face(ft_library, directories::resources::fonts::DIR_OPENSANS_BOLD, 0, &ft_face);
		if (ft_error != FT_Err_Ok)
		{
			lg::dbout::basicLog(L"[FT_ERROR]: Initializing face");
			return 1;
		}

		FT_GlyphSlot  ft_slot;
		FT_Matrix     ft_matrix;
		{ft_matrix.xx = 1, ft_matrix.xy = 0;
		ft_matrix.xx = 0, ft_matrix.xy = 1; }
		FT_Vector     ft_pen;

		ft_error = FT_Set_Char_Size(ft_face, 1 * 64, 0,
			100, 0);

		ft_slot = ft_face->glyph;

		ft_pen.x = 0;
		ft_pen.y = 0;

		std::string ft_text("ABC");

		unsigned char ft_image[FT_H][FT_W];

		auto ft_draw_bitmap = [&ft_image](FT_Bitmap* bitmap, FT_Int x, FT_Int y) {
			FT_Int  i, j, p, q;
			FT_Int  x_max = x + bitmap->width;
			FT_Int  y_max = y + bitmap->rows;


			/* for simplicity, we assume that `bitmap->pixel_mode' 
			// is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)  

			for (i = x, p = 0; i < x_max; i++, p++)
			{
				for (j = y, q = 0; j < y_max; j++, q++)
				{
					if (i < 0 || j < 0 ||
						i >= FT_W || j >= FT_H)
						continue;

					ft_image[j][i] |= bitmap->buffer[q * bitmap->width + p];
				}
			}
		};

		for (int n = 0; n < ft_text.length(); n++)
		{
			// set transformation 
			FT_Set_Transform(ft_face, &ft_matrix, &ft_pen);

			// load glyph image into the slot (erase previous one) 
			ft_error = FT_Load_Char(ft_face, ft_text[n], FT_LOAD_RENDER);
			if (ft_error != FT_Err_Ok)
			{
				lg::dbout::basicLog(L"[FT_ERROR]: Loading character");
				return 1;
			}

			// now, draw to our target surface (convert position) 
			ft_draw_bitmap(&ft_slot->bitmap,
				ft_slot->bitmap_left,
				FT_H - ft_slot->bitmap_top);

			// increment pen position 
			ft_pen.x += ft_slot->advance.x;
			ft_pen.y += ft_slot->advance.y;
		}
	}*/
	//
	///
	//
	
	

	while (!display.IsClosed())
	{
		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);

		inDetec.update();

		if (inDetec.ButtonClicked(input::MSB_RIGHT))
			lg::cwout::generalLog("FRAPS", std::to_string(1.f / inDetec.getTimeDelta()));

		renderManager.beginRoutine();
		renderManager.render(treeDrawable);
		renderManager.endRoutine();

		//
		///
		//
		//			
		fontRender.render("Regular render", glm::vec2(0.5, -0.5), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.2, 0.2));
		//fontRender.renderSaved(render::specialties::FontRenderer::SAVED_SENTANCE::SAVED_HELLOWORLD, glm::vec2(0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
		//
		///
		//

		camera.Yaw(inDetec.getDeltaMouseX()   *turnFactor);
		camera.Pitch(-inDetec.getDeltaMouseY()*turnFactor);

		if (inDetec.KeyDown(SDL_SCANCODE_A))
			camera.GetPosition() -= glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * (movementSpeed * inDetec.getTimeDelta());
		if (inDetec.KeyDown(SDL_SCANCODE_D))
			camera.GetPosition() += glm::normalize(glm::cross(camera.GetForward(), camera.GetUp())) * (movementSpeed * inDetec.getTimeDelta());

		if (inDetec.KeyDown(SDL_SCANCODE_W))
			camera.GetPosition() += camera.GetForward()*(movementSpeed * inDetec.getTimeDelta());
		if (inDetec.KeyDown(SDL_SCANCODE_S))
			camera.GetPosition() -= camera.GetForward()*(movementSpeed * inDetec.getTimeDelta());

		display.Update();
	}




	return 0;
}