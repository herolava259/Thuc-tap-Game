#pragma once

#include"StaticObject.h"
#include"ResourceManagers.h"
#include"Texture.h"
#include"Firgue.h"

class StaticObject : public Firgue {
private:
	GLint m_id;
protected:
	SceneTypes m_SceneType;
	ImpactEvents m_currImpact;

public:
	StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~StaticObject();
	void Init();
	void CatchEvent(ImpactEvents impt);
	void HandleEvent();
	void Update(GLfloat deltaTime);

};