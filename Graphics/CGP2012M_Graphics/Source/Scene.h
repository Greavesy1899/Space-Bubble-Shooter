#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "BubbleObject.h"
#include "ShipObject.h"
#include "LightObject.h"

namespace EngineOpenGL
{
	class Scene
	{
		std::string name;
		Camera camera;
		std::vector<GameObject*> objects;
		std::vector<GameObject*> ui;
		int bulletTimer = 25;
		int bulletRefreshTimer = 25;
		LightObject light;

	public:
		Scene();
		~Scene();
		void UpdateCamera(int w, int h);
		void Init();
		void Clean();
		void Input();
		void Update();
		void Render();
	};
}
#endif
