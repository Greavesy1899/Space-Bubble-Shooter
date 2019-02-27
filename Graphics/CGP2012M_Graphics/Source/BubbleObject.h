#ifndef BUBBLEOBJECT_H
#define BUBBLEOBJECT_H
#include "Model.h"
namespace EngineOpenGL
{
	class BubbleObject
	{
		Model* model;

	public:
		BubbleObject();
		~BubbleObject();
		void Update();
		void Render();

		Model* GetModel();
	};
}

#endif