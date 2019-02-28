#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H
#include "Model.h"
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	class BubbleObject
	{
		bool CheckBounds();
		Model* model;
		int xDirection;
		int yDirection;
		glm::vec3 shapeColour;

	public:
		BubbleObject();
		~BubbleObject();
		void Update();
		void Render();

		Model* GetModel();
		TransformMatrix Transform;
	};
}

#endif