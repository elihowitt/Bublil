#include"RENDER\renderManager.h"
#include"RENDER\core\camera.h"
#include"RENDER\core\display.h"
#include"RENDER\core\texture.h"
#include"RENDER\core\mesh.h"

#include"INPUT\inputDetection.h"

#include"RENDER\renderManager.h"

#define WIDTH	800//About full screen 1400
#define HEIGHT	600//					700

#undef main

int main()
{
	Display display(WIDTH, HEIGHT, "Graphical test");
	glm::vec3 skyVec(0.5, 0.2, 0.8);

	input::InputDetector inDetec;

	std::string meshs[MESHLIST::NUM_MESHES];
	std::string textures[TEXTURELIST::NUM_TEXTURES];
	std::string shaders[SHADERLIST::NUM_SHADERES];

	meshs[MESHLIST::MESH_TREE] = "./res/models/tree.obj";
	textures[TEXTURELIST::TEXTURE_TREE] = "./res/textures/tree.png";
	shaders[SHADERLIST::GENERAL_SHADER] = "./res/shaders/basicShader";
	shaders[SHADERLIST::GUI_SHADER] = "./res/shaders/GUIShader";

	render::RenderManager renderManager(meshs, textures, shaders);

	Camera camera(glm::vec3(0, 0, 0), 70.f, (float)WIDTH / (float)HEIGHT, 0.001, 1000);

	Transform treeTransform;

	RenderPack treeRenderPack;
	treeRenderPack.mesh_id = MESHLIST::MESH_TREE;
	treeRenderPack.texture_id = TEXTURELIST::TEXTURE_TREE;
	treeRenderPack.shader_id = SHADERLIST::GENERAL_SHADER;

	ShaderUpdatePack treeUpdatePack;

	treeUpdatePack.camera = &camera;
	
	glm::vec3 lightVec(glm::normalize(glm::vec3(5, 6, 7)));

	treeUpdatePack.vectors.push_back(lightVec);
	treeUpdatePack.vectors.push_back(skyVec);

	while (!display.IsClosed())
	{
		display.Clear(skyVec.x, skyVec.y, skyVec.z, 1.0);
		//display.Clear((float)inDetec.getMouseX()/WIDTH, (float)inDetec.getMouseY() / WIDTH, skyVec.z, 1.0);

		treeTransform.GetPos() = glm::vec3(0, -2, 5);
		treeTransform.GetScale() = glm::vec3(1, 1, 1);

		treeUpdatePack.transforms.clear();
		treeUpdatePack.transforms.push_back(treeTransform);

		renderManager.render(treeRenderPack, treeUpdatePack);

		inDetec.update();

		display.Update();
	}

	return 0;
}




