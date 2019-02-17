#include"RENDER\renderManager.h"
#include"RENDER\core\camera.h"
#include"RENDER\core\display.h"
#include"RENDER\core\texture.h"
#include"RENDER\core\mesh.h"

#include"INPUT\inputDetection.h"

#include"RENDER\renderManager.h"

#include"RENDER\specialties\GUI.h"

#include"RENDER\core\shaders\guiShader.h"

#define WIDTH	800//About full screen 1400
#define HEIGHT	600//					700

#undef main

int main()
{
	render::Display display(WIDTH, HEIGHT, "Graphical test");
	glm::vec3 skyVec(0.5, 0.2, 0.8);

	input::InputDetector inDetec;

	std::string meshs[render::MESHLIST::NUM_MESHES];
	std::string textures[render::TEXTURELIST::NUM_TEXTURES];
	std::string shaders[render::SHADERLIST::NUM_SHADERES];

	meshs[render::MESHLIST::MESH_TREE] = "../Bublil/res/models/tree.obj";
	textures[render::TEXTURELIST::TEXTURE_TREE] = "../Bublil/res/textures/tree.png";
	shaders[render::SHADERLIST::GENERAL_SHADER] = "../Bublil/res/shaders/basicShader";

	render::RenderManager renderManager(meshs, textures, shaders);

	render::Camera camera(glm::vec3(0, 0, 0), 70.f, (float)WIDTH / (float)HEIGHT, 0.001, 1000);

	//render::specialties::GUI londonGUI(
	//	"../Bublil/res/textures/LondonPhoto.png",
	//	glm::vec2(0, 0), glm::vec2(1, 1),
	//	"../Bublil/res/shaders/GUIShader");
	render::shaders::GUIShader guiShader("../Bublil/res/shaders/GUIShader");
	render::specialties::Quade guiQuade;
	render::Texture guiTexture("../Bublil/res/textures/LondonPhoto.png");
	render::ShaderUpdatePack guiUpdatePack;
	guiUpdatePack.vectors.push_back(glm::vec3(0, 0, 0));
	guiUpdatePack.vectors.push_back(glm::vec3(1, 1, 1));

	render::Drawable treeDrawable;

	render::ShaderUpdatePack treeUpdatePack;
	render::Transform treeTransform;
	treeTransform.GetPos() = glm::vec3(0, -2, 5);
	treeTransform.GetScale() = glm::vec3(1, 1, 1);
	treeUpdatePack.transforms.push_back(treeTransform);
	treeUpdatePack.camera = &camera;
	glm::vec3 lightVec(glm::normalize(glm::vec3(5, 6, 7)));
	treeUpdatePack.vectors.push_back(lightVec);
	treeUpdatePack.vectors.push_back(skyVec);

	render::RenderPack treeRenderPack;
	treeRenderPack.mesh_id = render::MESHLIST::MESH_TREE;
	treeRenderPack.texture_id = render::TEXTURELIST::TEXTURE_TREE;
	treeRenderPack.shader_id = render::SHADERLIST::GENERAL_SHADER;

	treeDrawable.renderPack = treeRenderPack;
	treeDrawable.updatePack = treeUpdatePack;
	
	float turnFactor = 0.5f;
	float movementSpeed = 5.f;
	float counter = 0.f;

	while (!display.IsClosed())
	{
		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);
		//display.Clear((float)inDetec.getMouseX()/WIDTH, (float)inDetec.getMouseY() / WIDTH, skyVec.z, 1.0);
		inDetec.update();

		counter += 0.005;
		lightVec.x = cosf(counter);

		treeDrawable.updatePack.clearAll();
		treeDrawable.updatePack.camera = &camera;
		treeDrawable.updatePack.transforms.push_back(treeTransform);
		treeDrawable.updatePack.vectors.push_back(lightVec);
		treeDrawable.updatePack.vectors.push_back(skyVec);

		//renderManager.render(treeDrawable);
		
		guiShader.bind();
		guiTexture.Bind(0);
		guiShader.update(guiUpdatePack);
		guiQuade.Draw();


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




