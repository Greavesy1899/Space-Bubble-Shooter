#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Camera.h"
#include "TransformMatrix.h"

namespace EngineOpenGL
{
	enum ObjectTypes
	{
		BASIC = 0,
		BUBBLE = 1,
		SHIP = 2,
		BULLET = 3,
	};
	enum RenderTypes
	{
		TEXTURE = 0,
		VERTEX_COLOUR,
		COLOUR,
		SPECIAL_BUBBLE
	};
	class GameObject
	{
	protected:
		Model* model;
		RenderTypes renderType;
		int textureID;
		int isHidden;
		glm::vec3 colour;

	public:
		GameObject();
		GameObject(OBJLoader loader);
		GameObject(float width, float height);
		GameObject(float radiusFactor);

		~GameObject();

		bool IsHidden() const;
		void HideObject(bool);

		virtual void Input();
		virtual void Update();
		virtual void Render(Camera cam);
		virtual void SetRenderType(RenderTypes type);
		virtual void SetDiffuseColour(glm::vec3 colour);
		virtual void SetTextureID(int id);

		virtual short GetObjectType() { return ObjectTypes::BASIC; }
		RenderTypes GetRenderType() const;
		virtual Model* GetModel();

		static bool IsColliding(GameObject* obj1, GameObject* obj2);

		TransformMatrix Transform;
	};
}
#endif
