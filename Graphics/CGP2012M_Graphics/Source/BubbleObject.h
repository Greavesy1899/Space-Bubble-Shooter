#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H
#include "Model.h"
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	class BubbleObject
	{
		int direction;
		bool CheckBounds();
		Model* model;

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