#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class TransformMatrix
{
	glm::mat4 matrix;

public:
	TransformMatrix();
	~TransformMatrix();

	static glm::vec3 GetForward() { return glm::vec3(0, 0, 1.0f); }
	static glm::vec3 GetZero() { return glm::vec3(0.0f, 0.0f, 0); }
	static glm::vec3 GetOne() { return glm::vec3(1.0f, 1.0f, 0); }
	static glm::vec3 GetUp() { return glm::vec3(0.0f, 1.0f, 0); }
	static glm::vec3 GetDown() { return glm::vec3(1.0f, -1.0f, 0); }
	static glm::vec3 GetLeft() { return glm::vec3(-1.0f, 0.0f, 0); }
	static glm::vec3 GetRight() { return glm::vec3(1.0f, 0.0f, 0); }

	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	glm::vec3 GetEuler() const;
	glm::mat4 GetMatrix() const;

	void Translate(glm::vec3 pos);
	void Rotate(glm::vec3 rotate, float angle = 0.0f);
	void Scale(glm::vec3 scale);
	void SetPosition(glm::vec3 pos);
	void SetScale(glm::vec3 scale);
	void SetRotation(glm::vec3 rot, float angle = 0.0f);
	void SetMatrix(glm::mat4 mat);

};
#endif

