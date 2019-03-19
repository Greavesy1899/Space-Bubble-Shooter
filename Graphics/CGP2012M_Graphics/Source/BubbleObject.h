#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H
#include "GameObject.h"
#include "Camera.h"

namespace EngineOpenGL
{
	class BubbleObject : public GameObject
	{
		bool CheckBounds();
		int xDirection;
		int yDirection;
		glm::vec3 shapeColour;

	public:
		BubbleObject();
		BubbleObject(OBJLoader loader);
		~BubbleObject();

		void Update() override;
		virtual short GetObjectType() override { return ObjectTypes::BUBBLE; }
	};
}

#endif