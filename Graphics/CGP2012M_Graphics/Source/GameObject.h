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
		OBSTACLE = 4,
		SKYBOX = 5
	};
	enum RenderTypes
	{
		TEXTURE = 0,
		VERTEX_COLOUR,
		COLOUR,
		SPECIAL_BUBBLE,
		SPECIAL_SKYBOX
	};
	class GameObject
	{
	private:
		ObjectTypes objectType;

	protected:
		Model* model;
		RenderTypes renderType;
		int textureID;
		int isHidden;
		glm::vec3 colour;

	public:
		GameObject();
		GameObject(OBJLoader loader, ObjectTypes type);
		GameObject(float width, float height, ObjectTypes type);
		GameObject(float width, float height, float depth, ObjectTypes type);

		~GameObject();

		bool IsHidden() const;
		void HideObject(bool);

		virtual void Input();
		virtual void Update();
		virtual void Render(Camera cam);
		virtual void SetRenderType(RenderTypes type);
		virtual void SetDiffuseColour(glm::vec3 colour);
		virtual void SetTextureID(int id);
		virtual void SetObjectType(ObjectTypes type);
		virtual void SetShaderType(ShaderProgram* sp);

		virtual short GetObjectType() { return this->objectType; }
		RenderTypes GetRenderType() const;
		virtual Model* GetModel();

		static bool IsCircleBoxColliding(GameObject* rect, GameObject* circle);
		static bool IsBoxColliding(GameObject* obj1, GameObject* obj2);

		TransformMatrix Transform;
	};
}
#endif
