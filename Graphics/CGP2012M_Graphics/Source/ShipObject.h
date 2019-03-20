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
		float forwardVector;
		int lives;
		bool movingForward;

	public:
		ShipObject();
		~ShipObject();
		void Input() override;
		void Update() override;
		
		int GetLives() const;
		bool HasMoved() const;
		void DeincrementLife();

		virtual short GetObjectType() override { return ObjectTypes::SHIP; }
	};
}
#endif

