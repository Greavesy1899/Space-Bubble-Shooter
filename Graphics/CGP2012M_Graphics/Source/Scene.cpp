#include "Scene.h"

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
		background->SetRenderType(RenderTypes::TEXTURE);
		background->SetTextureID(2);

		GameObject* leftObstacle = new GameObject(0.125f, 4.0f);
		leftObstacle->Transform.SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));
		leftObstacle->SetRenderType(RenderTypes::COLOUR);
		leftObstacle->SetDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));

		GameObject* rightObstacle = new GameObject(0.125f, 4.0f);
		rightObstacle->Transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
		rightObstacle->SetRenderType(RenderTypes::COLOUR);
		rightObstacle->SetDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));

		GameObject* topObstacle = new GameObject(4.0f, 0.125f);
		topObstacle->Transform.SetPosition(glm::vec3(0.04, 4.0f, 0.0f));
		topObstacle->SetRenderType(RenderTypes::COLOUR);
		topObstacle->SetDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));

		GameObject* botObstacle = new GameObject(4.0f, 0.125f);
		botObstacle->Transform.SetPosition(glm::vec3(0.0f, -4.0f, 0.0f));
		botObstacle->SetRenderType(RenderTypes::COLOUR);
		botObstacle->SetDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));

		ShipObject* ship = new ShipObject();
		ship->Transform.SetPosition(glm::vec3(0.0f));

		BubbleObject* bubObj = new BubbleObject(loader);
		bubObj->Transform.Translate(glm::vec3(-1.0f, 0.5f, 0.0f));
		BubbleObject* bubObj1 = new BubbleObject(loader);
		bubObj1->Transform.Translate(glm::vec3(0.5f, -2.5f, 0.0f));
		BubbleObject* bubObj2 = new BubbleObject(loader);
		bubObj2->Transform.Translate(glm::vec3(-0.5f, 0.5f, 0.0f));

		this->objects.push_back(background);
		this->objects.push_back(leftObstacle);
		this->objects.push_back(rightObstacle);
		this->objects.push_back(topObstacle);
		this->objects.push_back(botObstacle);
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
			bullet->Transform.SetMatrix(this->objects.at(5)->Transform.GetMatrix());
			this->objects.push_back(bullet);
		}

		for (GameObject* obj : this->objects)
			obj->Input();
	}
	void Scene::Update()
	{
		//collision checks.
		for (auto it = this->objects.begin(); it != this->objects.end();)
		{
			bool d = false;
			GameObject* obj = (*it);
			if (obj->GetObjectType() == ObjectTypes::BULLET)
			{
				glm::vec3 pos = obj->Transform.GetPosition();

				if ((pos.x < -4.0f || pos.x > 4.0f) || (pos.y < -4.0f || pos.y > 4.0f))
					d = true;
			}
			else if(obj->GetObjectType() == ObjectTypes::BUBBLE)
			{

				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::BULLET)
					{
						if (GameObject::IsColliding(object, obj))
							d = true;
					}
				}
			}

			if (d)
			{
				it = this->objects.erase(it);
				delete obj;
			}
			else
				++it;
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