#include"RENDER\renderManager.h"
#include"RENDER\core\camera.h"
#include"RENDER\core\display.h"
#include"RENDER\core\texture.h"
#include"RENDER\core\mesh.h"

#include"INPUT\inputDetection.h"

#include"RENDER\specialties\GUI.h"

#include"RENDER\core\shaders\guiShader.h"

#include"LOGGER\logger.h"

#define WIDTH	800//About full screen 1400
#define HEIGHT	600//					700

#undef main

#include<ctime>

#include"../res/directories/resourceDirectories.h"

#include<ft2build.h>

//#include<freeType\freetype.h>
#include FT_FREETYPE_H

int main_graphicalTest()
{

	/*
		FreeType is a bit wierd but good for recieving the proper stuff
	to build a glyph map of the text you wish to render.
	We need to find a way to build this thing and then a way to render it 
	[maybe using GUI or a new specialty to the system]. Shaders and stuff
	should be simple. Hopefully soon we could include any font file
	from the internet (maybe create/edit them in future) and render it
	to the screen something like :
	
		void renderText(string text, vec2 position, mat2 rotation, vec2 scale
			, colour, shader, fontFile ....).
	*/



	srand((unsigned)time(0));

	render::Display display(WIDTH, HEIGHT, "Graphical test");
	glm::vec3 skyVec(rand()%46/45.f, rand()%45/44.f, rand()%105/104.f);//glm::normalize(glm::vec3((rand()%25, rand()%65, rand()%95))));

	input::InputDetector inDetec;

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

	render::Camera camera(glm::vec3(0, 0, 0), 70.f, (float)WIDTH / (float)HEIGHT, 0.001f, 1000);

	glm::vec3 lightVec(glm::normalize(glm::vec3(5, 6, -7)));

	render::specialties::GUI londonGUI(directories::resources::textures::DIR_LONDON, glm::vec2(0, 0), glm::vec3(0,0,0), glm::vec2(1, 1));
	render::Shader* guiShader = new render::shaders::GUIShader(directories::resources::shaders::DIR_GUI);
	render::ShaderUpdatePack guiUpdatePack;


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

	render::Drawable foxDrawable;
	{
		foxDrawable.updatePack.transforms.push_back(render::Transform());
		foxDrawable.updatePack.transforms[0].GetPos() = glm::vec3(0, 0, 0);
		foxDrawable.updatePack.transforms[0].GetScale() = glm::vec3(1, 1, 1);
		foxDrawable.updatePack.camera = &camera;
		foxDrawable.updatePack.vectors.push_back(lightVec);
		foxDrawable.updatePack.vectors.push_back(skyVec);

		foxDrawable.renderPack.mesh_id = render::MESHLIST::MESH_POKEBALL;
		foxDrawable.renderPack.texture_id = render::TEXTURELIST::TEXTURE_POKEBALL;
		foxDrawable.renderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;
	}

	int TC = 50;

	float turnFactor = 0.5f;
	float movementSpeed = 5.f;
	float counter = 0.f;

	while (!display.IsClosed())
	{
		//
		///
		//Init beg:
			display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);
		
			inDetec.update();

			counter += 0.005f;
			lightVec.x = cosf(counter);
			lightVec.y = sinf(counter);
			lightVec.z = -1;

		//Init end.
		///
		//Render beg:

			if (inDetec.ButtonClicked(input::MSB_RIGHT))
				lg::cwout::generalLog("FRAPS", std::to_string(1.f / inDetec.getTimeDelta()));
			
			renderManager.beginRoutine();
			
			for (int i = 0; i < TC; ++i)
			{
				float angle = i * glm::two_pi<float>() / (float)TC;
				float R = 10;
			
				if (i % 2)
					treeDrawable.renderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;
				else
					treeDrawable.renderPack.shader_id = render::SHADERLIST::RELATIVEPOSITION_SHADER;
			
			
				treeDrawable.updatePack.transforms[0].GetPos() = glm::vec3(R * cosf(angle), 0, R * sinf(angle));
				treeDrawable.updatePack.transforms[0].GetRot() = glm::vec3(0, 0, 0);
				renderManager.render(treeDrawable);
			}
			
			
			foxDrawable.updatePack.transforms[0].GetRot().y += inDetec.getTimeDelta()/2.f;
			renderManager.render(foxDrawable);
			
			renderManager.endRoutine();
			
			guiUpdatePack.transforms.clear();
			guiUpdatePack.transforms.push_back(render::Transform(
				glm::vec3(-0.5, 0.5, 0), glm::vec3(0, 0, glm::radians(180.f)), glm::vec3(1/2.f, 1/2.f, 1)));
			guiShader->bind();
			((render::shaders::GUIShader*)guiShader)->update(guiUpdatePack);
			londonGUI.Bind(0);
			londonGUI.Draw();
			
		//Render end.
		///
		//Update beg:

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

		//Update end.
		///
		//
	}

	return 0;
}




