#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Model.h";
#include "Camera.h"
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	class GameObject
	{

		Model* model;

	public:
		GameObject();
		GameObject(OBJLoader loader);
		GameObject(float width, float height);
		GameObject(float radiusFactor);

		~GameObject();
		void Input();
		void Update();
		void Render(Camera cam);

		Model* GetModel();
		TransformMatrix Transform;
	};
}
#endif
