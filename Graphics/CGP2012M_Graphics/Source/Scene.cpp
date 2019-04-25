#include "Scene.h"

namespace EngineOpenGL
{
	Scene::Scene()
	{
		this->camera = Camera(683, 384);
		this->objects = std::vector<GameObject*>();
		this->ui = std::vector<GameObject*>();
		this->light = LightObject();
	}
	Scene::~Scene()
	{
		this->Clean();
	}
	void Scene::UpdateCamera(int w, int h)
	{
		//this->camera.SetOrthographic((float)w, (float)h);
		this->camera.SetPerspective((float)w, (float)h);
	}
	void Scene::Init()
	{
		OBJLoader loader = OBJLoader();

		loader = OBJLoader();
		loader.ParseOBJ("Models/skybox.obj");

		GameObject* background = new GameObject(loader, ObjectTypes::SKYBOX);
		background->Transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		background->SetRenderType(RenderTypes::SPECIAL_SKYBOX);
		background->SetDiffuseColour(glm::vec3(0.0f));
		background->SetShaderType(Singleton::getInstance()->GetSM()->GetShader(1));
		background->SetTextureID(2);

		loader = OBJLoader();
		loader.ParseOBJ("Models/boundaryV.obj");

		GameObject* leftObstacle = new GameObject(loader, ObjectTypes::OBSTACLE);
		leftObstacle->Transform.SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));
		leftObstacle->SetRenderType(RenderTypes::TEXTURE);
		leftObstacle->SetTextureID(5);

		GameObject* rightObstacle = new GameObject(loader, ObjectTypes::OBSTACLE);
		rightObstacle->Transform.SetPosition(glm::vec3(4.0f, 0.0f, 0.0f));
		rightObstacle->SetRenderType(RenderTypes::TEXTURE);
		rightObstacle->SetTextureID(5);

		loader = OBJLoader();
		loader.ParseOBJ("Models/boundaryH.obj");

		GameObject* topObstacle = new GameObject(loader, ObjectTypes::OBSTACLE);
		topObstacle->Transform.SetPosition(glm::vec3(0.04, 4.0f, 0.0f));
		topObstacle->SetRenderType(RenderTypes::TEXTURE);
		topObstacle->SetTextureID(5);

		GameObject* botObstacle = new GameObject(loader, ObjectTypes::OBSTACLE);
		botObstacle->Transform.SetPosition(glm::vec3(0.0f, -4.0f, 0.0f));
		botObstacle->SetRenderType(RenderTypes::TEXTURE);
		botObstacle->SetTextureID(5);

		ShipObject* ship = new ShipObject();
		ship->Transform.SetPosition(glm::vec3(0.0f, -3.5f, 0.0f));

		loader = OBJLoader();
		loader.ParseOBJ("Models/circle.obj");

		BubbleObject* bubObj = new BubbleObject(loader);
		BubbleObject* bubObj1 = new BubbleObject(loader);
		BubbleObject* bubObj2 = new BubbleObject(loader);
		BubbleObject* bubObj3 = new BubbleObject(loader);
		BubbleObject* bubObj4 = new BubbleObject(loader);
		BubbleObject* bubObj5 = new BubbleObject(loader);

		this->objects.push_back(background);
		this->objects.push_back(leftObstacle);
		this->objects.push_back(rightObstacle);
		this->objects.push_back(topObstacle);
		this->objects.push_back(botObstacle);
		this->objects.push_back(ship);
		this->objects.push_back(bubObj);
		this->objects.push_back(bubObj1);
		this->objects.push_back(bubObj2);
		this->objects.push_back(bubObj3);
		this->objects.push_back(bubObj4);
		this->objects.push_back(bubObj5);

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
		if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_SPACE) && bulletTimer > bulletRefreshTimer) {
			BulletObject* bullet = new BulletObject();
			bullet->Transform.SetMatrix(this->objects.at(5)->Transform.GetMatrix());
			this->objects.push_back(bullet);
			bulletTimer = 0;
		}
		else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_O)) {
			if (this->objects[0]->GetRenderType() == RenderTypes::TEXTURE)
				this->objects[0]->SetRenderType(RenderTypes::COLOUR);
			else
				this->objects[0]->SetRenderType(RenderTypes::TEXTURE);
		}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_T)) {
		//	this->camera.ViewMatrix.Translate(glm::vec3(0.0f, 0.0f, 0.1f));
		//}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_G)) {
		//	this->camera.ViewMatrix.Translate(glm::vec3(0.0f, 0.0f, -0.1f));
		//}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_F)) {
		//	this->camera.ViewMatrix.Translate(glm::vec3(0.0f, 0.1f, 0.0f));
		//}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_H)) {
		//	this->camera.ViewMatrix.Translate(glm::vec3(0.0f, -0.1f, 0.0f));
		//}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_R)) {
		//	this->camera.ViewMatrix.Rotate(glm::vec3(0.1f, 0.0f, 0.0f), 0.1f);
		//}
		//else if (Singleton::getInstance()->GetIM()->CheckForKey(SDL_SCANCODE_Y)) {
		//	this->camera.ViewMatrix.Rotate(glm::vec3(0.0f, 0.1f, 0.0f), 0.1f);
		//}

		for (GameObject* obj : this->objects)
			obj->Input();

		for (GameObject* obj : this->ui)
			obj->Input();

		bulletTimer++;
	}
	void Scene::Update()
	{
		//this->light.SetColour(glm::vec3(0.33f, 0.33f, 0.33f));
		//this->light.SetPosition(glm::vec3(0.0f));
		//this->light.SetIntensity(1.0f);

		//collision checks.
		int lightIDX = 0;
		for (auto it = this->objects.begin(); it != this->objects.end();)
		{
			bool d = false;

			GameObject* obj = (*it);
			if (obj->GetObjectType() == ObjectTypes::BULLET)
			{
				obj->Update();

				if (lightIDX != 3)
				{
					this->light.pointLight[lightIDX].position = obj->Transform.GetPosition();
					lightIDX++;
				}
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
				obj->Update();
				auto* bubble = dynamic_cast<BubbleObject*>(obj);

				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::OBSTACLE)
					{
						if (GameObject::IsBoxColliding(object, obj))
						{
							bubble->InvertDirection();
						}
					}
					else if (object->GetObjectType() == ObjectTypes::BULLET)
					{
						if (GameObject::IsBoxColliding(object, obj))
						{
							bubble->Respawn();
							object->Transform.SetPosition(glm::vec3(4.0f, 4.0f, 0.0f)); //im outta time!
						}
					}
				}
			}
			else if (obj->GetObjectType() == ObjectTypes::SHIP)
			{
				auto* ship = dynamic_cast<ShipObject*>(obj);

				for (auto object : this->objects)
				{
					if (object->GetObjectType() == ObjectTypes::BUBBLE || object->GetObjectType() == ObjectTypes::OBSTACLE)
					{
						if (GameObject::IsCircleBoxColliding(obj, object))
						{
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
					ship->Update();

					if (ship->GetLives() == 0)
					{
						this->Clean();
						this->Init();
						return;
					}
				}
			}
			else if (obj->GetObjectType() == ObjectTypes::BASIC || obj->GetObjectType() == ObjectTypes::OBSTACLE)
			{
				obj->Update();
			}

			if (d)
			{
				it = this->objects.erase(it);
				delete obj;
			}
			else
				++it;
		}

		for (int i = lightIDX; i < 3; i++)
		{
			if (i <= lightIDX)
				this->light.pointLight[i].position = glm::vec3(99.0f);
		}

		for (GameObject* obj : this->ui)
			obj->Update();
	}
	void Scene::Render()
	{
		for (GameObject* obj : this->objects)
			obj->Render(this->camera, this->light);

		for (GameObject* obj : this->ui)
			obj->Render(this->camera, this->light);
	}
}