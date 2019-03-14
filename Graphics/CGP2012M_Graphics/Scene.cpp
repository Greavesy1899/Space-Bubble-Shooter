#include "Source\Scene.h"

namespace EngineOpenGL
{
	Scene::Scene()
	{
		this->objects = std::vector<GameObject*>();
	}
	Scene::~Scene()
	{
		this->Clean();
	}
	void Scene::UpdateCamera(int w, int h)
	{
		this->camera.SetOrthographic(w, h);
	}
	void Scene::Init()
	{
		OBJLoader loader = OBJLoader();
		loader.ParseOBJ("Models/circle.obj");

		GameObject* background = new GameObject(4.0f, 4.0f);
		background->Transform.SetPosition(glm::vec3(0.0f));

		ShipObject* ship = new ShipObject();
		ship->Transform.SetPosition(glm::vec3(0.0f));

		BubbleObject* bubObj = new BubbleObject(loader);
		bubObj->Transform.Translate(glm::vec3(-1.0f, 0.5f, 0.0f));
		BubbleObject* bubObj1 = new BubbleObject(loader);
		bubObj1->Transform.Translate(glm::vec3(0.5f, -2.5f, 0.0f));
		BubbleObject* bubObj2 = new BubbleObject(loader);
		bubObj2->Transform.Translate(glm::vec3(-0.5f, 0.5f, 0.0f));

		this->objects.push_back(background);
		this->objects.push_back(ship);
		this->objects.push_back(bubObj);
		this->objects.push_back(bubObj1);
		this->objects.push_back(bubObj2);


		this->camera = Camera();
		this->camera.SetOrthographic(800, 600);
	}
	void Scene::Clean()
	{
		for (int i = 0; i != this->objects.size(); i++)
			delete this->objects[i];
		this->objects.clear();
	}
	void Scene::Input()
	{
		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_SPACE)) {
			BulletObject* bullet = new BulletObject();
			bullet->Transform.SetMatrix(this->objects.at(1)->Transform.GetMatrix());
			this->objects.push_back(bullet);
		}

		for (GameObject* obj : this->objects)
			obj->Input();
	}
	void Scene::Update()
	{
		for (GameObject* obj : this->objects)
		{
			obj->GetModel()->GetBBox();
		}
		for (GameObject* obj : this->objects)
			obj->Update();
	}
	void Scene::Render()
	{
		for (GameObject* obj : this->objects)
			obj->Render(this->camera);
	}
}