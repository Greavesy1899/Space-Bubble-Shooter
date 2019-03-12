#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "BubbleObject.h"
#include "ShipObject.h"

namespace EngineOpenGL
{
	class Scene
	{
		std::string name;
		glm::vec2 boundaries;
		Camera camera;
		std::vector<GameObject*> objects;

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
