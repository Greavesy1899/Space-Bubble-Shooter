#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Camera.h"
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	class GameObject
	{
	protected:
		Model* model;

	public:
		GameObject();
		GameObject(OBJLoader loader);
		GameObject(float width, float height);
		GameObject(float radiusFactor);

		~GameObject();
		virtual void Input();
		virtual void Update();
		virtual void Render(Camera cam);
		virtual short GetObjectType() { return 0; }
		virtual Model* GetModel();

		TransformMatrix Transform;
	};
}
#endif
