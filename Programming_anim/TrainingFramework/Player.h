#pragma once
#include"DynamicObjet.h"


class Player :public DynamicObject {
private:
protected:
	ImpactEvents m_currImpact;
	GLint m_numCake;
public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~Player();

	void CatchEvent(ImpactEvents impt);

	void Update(GLfloat deltatime);
	void Init();
	void HandleEvent();
	void PickCake();
};