#include "Scene.h"

namespace EngineOpenGL
{
	Scene::Scene()
	{
		this->camera = Camera(1024, 720);
		this->objects = std::vector<GameObject*>();
		this->ui = std::vector<GameObject*>();
	}
	Scene::~Scene()
	{
		this->Clean();
	}
	void Scene::UpdateCamera(int w, int h)
	{
		this->camera.SetOrthographic((float)w, (float)h);
	}
	void Scene::Init()
	{
		OBJLoader loader = OBJLoader();
		loader.ParseOBJ("Models/circle.obj");

		GameObject* background = new GameObject(4.0f, 4.0f, ObjectTypes::BASIC);
		background->Transform.SetPosition(glm::vec3(0.0f));
		background->SetRenderType(RenderTypes::TEXTURE);
		background->SetDiffuseColour(glm::vec3(0.0f));
		background->SetTextureID(2);

		GameObject* leftObstacle = new GameObject(0.125f, 4.0f, ObjectTypes::OBSTACLE);
		leftObstacle->Transform.SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));
		leftObstacle->SetRenderType(RenderTypes::COLOUR);
		leftObstacle->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

		GameObject* rightObstacle = new GameObject(0.125f, 4.0f, ObjectTypes::OBSTACLE);
		rightObstacle->Transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
		rightObstacle->SetRenderType(RenderTypes::COLOUR);
		rightObstacle->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

		GameObject* topObstacle = new GameObject(4.0f, 0.125f, ObjectTypes::OBSTACLE);
		topObstacle->Transform.SetPosition(glm::vec3(0.04, 4.0f, 0.0f));
		topObstacle->SetRenderType(RenderTypes::COLOUR);
		topObstacle->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

		GameObject* botObstacle = new GameObject(4.0f, 0.125f, ObjectTypes::OBSTACLE);
		botObstacle->Transform.SetPosition(glm::vec3(0.0f, -4.0f, 0.0f));
		botObstacle->SetRenderType(RenderTypes::COLOUR);
		botObstacle->SetDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));

		ShipObject* ship = new ShipObject();
		ship->Transform.SetPosition(glm::vec3(0.0f, -3.5f, 0.0f));

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

		glm::vec3 heartOffset(-3.5f, -3.5f, 0.0f);
		for (int i = 0; i != ship->GetLives(); i++)
		{
			GameObject* heart = new GameObject(0.2f, 0.2f, ObjectTypes::BASIC);
			heart->Transform.Translate(heartOffset);
			heart->SetRenderType(RenderTypes::TEXTURE);
			heart->SetTextureID(3);
			this->ui.push_back(heart);
			heartOffset.y += 0.5f;
		}
	}
	void Scene::Clean()
	{
		for (int i = 0; i != this->objects.size(); i++)
			delete this->objects[i];
		for (int i = 0; i != this->ui.size(); i++)
			delete this->ui[i];
		this->ui.clear();
		this->objects.clear();
	}
	void Scene::Input()
	{
		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_SPACE)) {
			BulletObject* bullet = new BulletObject();
			bullet->Transform.SetMatrix(this->objects.at(5)->Transform.GetMatrix());
			this->objects.push_back(bullet);
		}
		else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_O)) {
			if (this->objects[0]->GetRenderType() == RenderTypes::TEXTURE)
				this->objects[0]->SetRenderType(RenderTypes::COLOUR);
			else
				this->objects[0]->SetRenderType(RenderTypes::TEXTURE);
		}

		for (GameObject* obj : this->objects)
			obj->Input();

		for (GameObject* obj : this->ui)
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
				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::OBSTACLE)
					{
						if (GameObject::IsBoxColliding(object, obj))
							d = true;
					}
				}
			}
			else if(obj->GetObjectType() == ObjectTypes::BUBBLE)
			{
				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::OBSTACLE)
					{
						if (GameObject::IsBoxColliding(object, obj))
						{
							auto* bubble = dynamic_cast<BubbleObject*>(obj);
							bubble->InvertDirection();
						}
					}
				}
			}
			else if (obj->GetObjectType() == ObjectTypes::SHIP)
			{
				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::BUBBLE)
					{
						if (GameObject::IsCircleBoxColliding(obj, object))
						{
							auto* ship = dynamic_cast<ShipObject*>(obj);
							ship->DeincrementLife();
							ship->Transform.SetPosition(glm::vec3(0.0f, -3.5f, 0.0f));

							for (int i = 0; i != ui.size(); i++)
							{
								ui[i]->HideObject(false);
								if (i >= ship->GetLives() )
									ui[i]->HideObject(true);
							}
						}
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

		for (GameObject* obj : this->ui)
			obj->Update();
	}
	void Scene::Render()
	{
		for (GameObject* obj : this->objects)
			obj->Render(this->camera);

		for (GameObject* obj : this->ui)
			obj->Render(this->camera);
	}
}