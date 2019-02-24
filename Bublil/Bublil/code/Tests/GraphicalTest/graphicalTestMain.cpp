#include"RENDER\renderManager.h"
#include"RENDER\core\camera.h"
#include"RENDER\core\display.h"
#include"RENDER\core\texture.h"
#include"RENDER\core\mesh.h"

#include"INPUT\inputDetection.h"

#include"RENDER\renderManager.h"

#include"RENDER\specialties\GUI.h"

#include"RENDER\core\shaders\guiShader.h"

#include"LOGGER\logger.h"

#define WIDTH	800//About full screen 1400
#define HEIGHT	600//					700

#undef main

#include<ctime>

#include"../res/directories/resourceDirectories.h"

int main()
{
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

	GUI londonGUI(directories::resources::textures::DIR_LONDON, glm::vec2(0, 0), glm::vec2(1, 1));
	render::Shader* guiShader = new render::shaders::GUIShader(directories::resources::shaders::DIR_GUI);
	render::ShaderUpdatePack guiUpdatePack;

	render::Drawable treeDrawable;
	render::Transform treeTransform;
		
	{
		render::ShaderUpdatePack treeUpdatePack;
		treeTransform.GetPos() = glm::vec3(0, -2, 5);
		treeTransform.GetScale() = glm::vec3(1, 1, 1);
		treeUpdatePack.transforms.push_back(treeTransform);
		treeUpdatePack.camera = &camera;
		treeUpdatePack.vectors.push_back(lightVec);
		treeUpdatePack.vectors.push_back(skyVec);

		render::RenderPack treeRenderPack;
		treeRenderPack.mesh_id = render::MESHLIST::MESH_TREE;
		treeRenderPack.texture_id = render::TEXTURELIST::TEXTURE_TREE;
		treeRenderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;

		treeDrawable.renderPack = treeRenderPack;
		treeDrawable.updatePack = treeUpdatePack;
	}

	render::Drawable foxDrawable;
	render::Transform foxTransform;

	{
		render::ShaderUpdatePack foxUpdatePack;
		foxTransform.GetPos() = glm::vec3(0, 0, 0);
		foxTransform.GetScale() = glm::vec3(1, 1, 1);
		foxUpdatePack.transforms.push_back(foxTransform);
		foxUpdatePack.camera = &camera;
		foxUpdatePack.vectors.push_back(lightVec);
		foxUpdatePack.vectors.push_back(skyVec);

		render::RenderPack foxRenderPack;
		foxRenderPack.mesh_id = render::MESHLIST::MESH_POKEBALL;
		foxRenderPack.texture_id = render::TEXTURELIST::TEXTURE_POKEBALL;
		foxRenderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;

		foxDrawable.renderPack = foxRenderPack;
		foxDrawable.updatePack = foxUpdatePack;
	}


	int TC = 50;


	float turnFactor = 0.5f;
	float movementSpeed = 5.f;
	float counter = 0.f;

	while (!display.IsClosed())
	{
		if (inDetec.ButtonClicked(input::MSB_RIGHT))
			lg::cwout::generalLog("FRAPS", std::to_string(1.f / inDetec.getTimeDelta()));
		//lg::cwout::generalLog("TREE_COUNT", std::to_string(TC));

		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);
		
		inDetec.update();

		counter += 0.005f;
		lightVec.x = cosf(counter);
		lightVec.y = sinf(counter);
		lightVec.z = -1;

		renderManager.beginRoutine();

		for (int i = 0; i < TC; ++i)
		{
			float angle = i * glm::two_pi<float>() / (float)TC;
			float R = 10;

			if (i % 2)
				treeDrawable.renderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;
			else
				treeDrawable.renderPack.shader_id = render::SHADERLIST::RELATIVEPOSITION_SHADER;

			treeDrawable.updatePack.clearAll();
			treeDrawable.updatePack.camera = &camera;
			treeTransform.GetPos() = glm::vec3(R * cosf(angle), 0, R * sinf(angle));
			treeTransform.GetRot() = glm::vec3(0, 0, glm::radians(90.f));
			treeDrawable.updatePack.transforms.push_back(treeTransform);
			treeDrawable.updatePack.vectors.push_back(lightVec);
			treeDrawable.updatePack.vectors.push_back(skyVec);
			renderManager.render(treeDrawable);
		}

		foxDrawable.updatePack.clearAll();
		foxDrawable.updatePack.camera = &camera;
		foxDrawable.updatePack.transforms.push_back(foxTransform);
		foxDrawable.updatePack.vectors.push_back(lightVec);
		foxDrawable.updatePack.vectors.push_back(skyVec);
		renderManager.render(foxDrawable);

		renderManager.endRoutine();

		guiUpdatePack.transforms.clear();
		guiUpdatePack.transforms.push_back(render::Transform(
			glm::vec3(-0.5, 0.5, 0), glm::vec3(0, 0, glm::radians(180.f)), glm::vec3(1/2.f, 1/2.f, 1)));
		guiShader->bind();
		((render::shaders::GUIShader*)guiShader)->update(guiUpdatePack);
		londonGUI.Bind(0);
		londonGUI.Draw();


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




