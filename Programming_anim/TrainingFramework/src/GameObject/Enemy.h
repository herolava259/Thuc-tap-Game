#pragma once
#include"DynamicObjet.h"

class Enemy :public DynamicObject {
private:
	GLint m_Id;
protected:
	ImpactEvents m_currImpact;
	GLint m_numCake;
	EnemyTypes m_EnemyType;
	
public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~Enemy();
	void CatchEvent(ImpactEvents impt);

	void Update(GLfloat deltatime);
	void Init();
	void HandleEvent();
	void PickCake();
	void SetEnemyType(EnemyTypes type);
	EnemyTypes GetEnemyType() {
		return m_EnemyType;
	}
};
