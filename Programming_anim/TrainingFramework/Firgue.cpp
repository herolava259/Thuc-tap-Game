#include"Firgue.h"
#include"Texture.h"
#include"Shaders.h"
#include"Models.h"
#include"ResourceManagers.h"


extern GLint screenWidth;
extern GLint screenHeight;


class Firgue;
void Firgue::Init() {
	m_Name = "Firgue";
	m_State = StateFigTypes::FIRGUE_Stand;
	m_isChangeState = false;
	m_currAttrAnimation.framTime = 0.0;
	m_currAttrAnimation.numFrames = 0;
	m_currAttrAnimation.isloop = 0;
	m_currAttrAnimation.State = FIRGUE_Invalids;
	m_currAttrAnimation.name = "";
	m_isLoop = true;
	SpriteAnimation::Init();
}
Firgue::Firgue(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, frameTime) {
	Init();
}
Firgue::~Firgue() {

}
void Firgue::AddAnimation(const std::string& str, StateFigTypes statetype, bool isloop, GLint numFrame, GLfloat frameTime) {
	AnimationAttribute attrAnimation = { str, isloop, statetype, numFrame, frameTime };
	m_listAnimation.insert(std::pair<std::string, AnimationAttribute>(str, attrAnimation));
}

void Firgue::LoadAnimation(const std::string str) {
	auto pTexture = ResourceManagers::GetInstance()->GetTexture(str);
	auto pAttrAnimation = m_listAnimation.find(str)->second;
	m_isLoop = pAttrAnimation.isloop;
	m_State = pAttrAnimation.State;
	m_numFrames = pAttrAnimation.numFrames;
	m_frameTime = pAttrAnimation.framTime;

	m_pTexture = pTexture;
	m_isChangeState = true;
}

bool Firgue::IsChangeState() {
	return m_isChangeState;
}

void Firgue::Update(GLfloat deltaTime) {
	if (!m_isChangeState) {
		if (m_isLoop || m_currentFrame < m_numFrames) {
			m_currentTime += deltaTime;
			if (m_currentTime >= m_frameTime) {
				m_currentFrame++;
				if (m_currentFrame >= m_numFrames) {
					m_currentFrame = 0;
				}
				m_currentTime -= m_frameTime;
			}
		}
	}
	else {
		m_isChangeState = 0;
		m_currentTime = 0.0f;
		m_currentFrame = 0;
	}
	m_colIndex = GLint(m_Vec2DPos.x/ 2 * 50) + 1;
	m_rowIndex = GLint(m_Vec2DPos.y/ 2 * 50) + 1;
}
void Firgue::Set2DPostion(GLfloat x, GLfloat y) {
	m_colIndex = GLint(x / 2*50) + 1;
	m_rowIndex = GLint(y / 2 * 50) + 1;
	SpriteAnimation::Set2DPosition(x, y);

}

bool Firgue::isCollision(Firgue& fig) {
	auto vecPos = fig.Get2DPosition();
	auto vecSize = fig.Get2DSize();
	GLint dis = (m_Vec2DPos.x - vecPos.x);
	GLint maxdis = (m_iWidth + vecSize.x);
	if (dis <= maxdis && dis >= maxdis) {
		return 1;
	}
	return 0;
}

Vector2 Firgue::Get2DSize() {
	return Vector2(m_iWidth, m_iHeight);
}

void Firgue::SetState(StateFigTypes state) {
	m_State = state;
	StateFigTypes tmp;
	std::string str = "";
	for (auto it : m_listAnimation) {
		tmp = it.second.State;
		if (tmp == state) {
			str = it.second.name;
			break;
		}
	}
	LoadAnimation(str);
}