#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H
#include "Model.h"
#include "TransformMatrix.h"
#include "Camera.h"
#include "BulletObject.h"

namespace EngineOpenGL
{
	class ShipObject
	{
		bool CheckBounds();
		Model* model;
		BulletObject* bulletObject;
		float forwardVector;

	public:
		ShipObject();
		~ShipObject();
		void Input();
		void Update();
		void Render(Camera cam);

		Model* GetModel();
		TransformMatrix Transform;
	};
}
#endif SHIPOBJECT_H

