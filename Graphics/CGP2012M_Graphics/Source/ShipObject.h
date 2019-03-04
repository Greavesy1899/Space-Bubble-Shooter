#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H
#include "Model.h"
#include "TransformMatrix.h"
#include "Camera.h"

namespace EngineOpenGL
{
	class ShipObject
	{
		bool CheckBounds();
		Model* model;

	public:
		ShipObject();
		~ShipObject();
		void Update();
		void Render(Camera cam);

		Model* GetModel();
		TransformMatrix Transform;
	};
}
#endif SHIPOBJECT_H

