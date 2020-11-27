#include"Enemy.h"
Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :DynamicObject(model, shader, texture, numFrames, frameTime) {
	Init();
}

Enemy::~Enemy() {

}

void Enemy::CatchEvent(ImpactEvents impt) {
	m_currImpact = impt;
	HandleEvent();
}
void Enemy::HandleEvent() {
	switch (m_currImpact) {
	case ImpactEvents::IMPACT_Invalids:
	{
		return;
	}
	case ImpactEvents::IMPACT_Collision:
	{
		SetState(StateFigTypes::FIRGUE_Inertia);
	}
	case ImpactEvents::IMPACT_Hunt:
	{
		SetState(StateFigTypes::FIRGUE_Eat);
	}
	case ImpactEvents::IMPACT_Fallingdown:
	{
		SetState(StateFigTypes::FIRGUE_Dead);
	}
	case ImpactEvents::IMPACT_Final:
	{
		SetState(StateFigTypes::FIRGUE_Success);
	}
	case ImpactEvents::IMPACT_Pickcake:
		SetState(StateFigTypes::FIRGUE_Invalids);
		PickCake();
	}
	m_currImpact = ImpactEvents::IMPACT_Invalids;
}
void Enemy::PickCake() {
	m_numCake++;
}
void Enemy::Init() {
	m_currImpact = ImpactEvents::IMPACT_Invalids;
	m_numCake = 0;
	m_EnemyType = EnemyTypes::ENEMY_Invalids;
	DynamicObject::Init();
}

void Enemy::Update(GLfloat deltaTime) {
	DynamicObject::Update(deltaTime);
}
void Enemy::SetEnemyType(EnemyTypes type) {
	m_EnemyType = type;
}