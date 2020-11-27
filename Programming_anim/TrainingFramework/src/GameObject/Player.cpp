#include"Player.h"

#include"ResourceManagers.h"

class Player;
Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :DynamicObject(model, shader, texture, numFrames, frameTime) {
	Init();
}

Player::~Player() {

}

void Player::CatchEvent(ImpactEvents impt) {
	m_currImpact = impt;
	HandleEvent();
}
void Player::HandleEvent() {
	switch (m_currImpact) {
	case ImpactEvents::IMPACT_Invalids:
	{
		return;
	}
	case ImpactEvents::IMPACT_Collision:
	{
		SetState(StateFigTypes::FIRGUE_Inertia);
	}
	case ImpactEvents::IMPACT_Eaten:
	{
		SetState(StateFigTypes::FIRGUE_Dead);
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
void Player::PickCake() {
	m_numCake++;
}
void Player::Init() {
	m_currImpact = ImpactEvents::IMPACT_Invalids;
	m_numCake = 0;
	DynamicObject::Init();
}

void Player::Update(GLfloat deltaTime) {
	DynamicObject::Update(deltaTime);
}