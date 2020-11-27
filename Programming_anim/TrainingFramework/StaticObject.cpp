#include"StaticObject.h"
#include"Texture.h"
#include"Shaders.h"
#include"Models.h"

StaticObject::StaticObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :Firgue(model, shader, texture, numFrames, frameTime) {
	Init();
}

StaticObject::~StaticObject() {

}
void StaticObject::Init() {
	m_SceneType = SceneTypes::SCENE_Invalids;
	m_id = 1;
	Firgue::Init();
}
void StaticObject::CatchEvent(ImpactEvents impt) {
	m_currImpact = impt;
	HandleEvent();
}

void StaticObject::HandleEvent() {
	switch (m_currImpact) {
	case ImpactEvents::IMPACT_Invalids:
	{
		return;
	}
	case ImpactEvents::IMPACT_Collision:
	{
		SetState(StateFigTypes::FIRGUE_Vibrate);
		break;
	}
	
	case ImpactEvents::IMPACT_Damage:
		SetState(StateFigTypes::FIRGUE_Destroyed);
		break;
	}
	m_currImpact = ImpactEvents::IMPACT_Invalids;
}

void StaticObject::Update(GLfloat deltaTime) {
	if (m_State == StateFigTypes::FIRGUE_Vibrate && m_currentFrame >= m_numFrames) {
		SetState(StateFigTypes::FIRGUE_Silent);
	}
	Firgue::Update(deltaTime);
}