#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H
#include "GameObject.h"
#include "Camera.h"
#include "BulletObject.h"

namespace EngineOpenGL
{
	class ShipObject : public GameObject
	{
		bool CheckBounds();
		BulletObject* bulletObject;
		float forwardVector;

	public:
		ShipObject();
		~ShipObject();
		void Input() override;
		void Update() override;
		void Render(Camera cam) override;
	};
}
#endif

