#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "GameObject.h"
#include "Model.h"
#include "Camera.h"

namespace EngineOpenGL
{
	class BulletObject : public GameObject
	{

	public:
		BulletObject();
		~BulletObject();

		void Update() override;
		virtual short GetObjectType() override { return ObjectTypes::BULLET; }
	};
}
#endif 

