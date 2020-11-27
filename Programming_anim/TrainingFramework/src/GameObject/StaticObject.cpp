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