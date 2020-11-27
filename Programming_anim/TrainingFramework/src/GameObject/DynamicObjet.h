#pragma once
#include"Firgue.h"
#include"ResourceManagers.h"

class DynamicObject : public Firgue {
private:
	GLint m_id;
protected:
	PlayerControls m_currentControl;
	Vector2 m_direction;
	GLint m_moveLimited;
	GLfloat m_Speed;
public:
	DynamicObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~DynamicObject();

	void SetControl(PlayerControls control);

	void Move(GLfloat deltaTime);

	void Update(GLfloat deltaTime);

	void SetState(StateFigTypes state);
	void SetMoveLimited();
};