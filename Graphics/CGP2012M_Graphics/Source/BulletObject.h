#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "Model.h"
#include "Camera.h"

namespace EngineOpenGL
{
	class BulletObject
	{
		Model* model;

	public:
		BulletObject();
		~BulletObject();

		void Update();
		void Render(Camera cam);

		Model* GetModel();
		TransformMatrix Transform;
	};
}
#endif BULLETOBJECT_H

