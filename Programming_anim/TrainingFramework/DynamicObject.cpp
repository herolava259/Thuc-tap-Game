#include"DynamicObjet.h"
#include"Firgue.h"

DynamicObject::DynamicObject(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :Firgue(model, shader, texture, numFrames, frameTime)
{
	Init();
}
DynamicObject::~DynamicObject() {

}

void DynamicObject::SetControl(PlayerControls control) {
	m_currentControl = control;
	if (control == PlayerControls::CONTROL_Invalids) return;
	if (control == PlayerControls::CONTROL_Left) {
		m_direction.x = -1.0f;
		m_direction.y = 0.0f;
	}
	else if (control == PlayerControls::CONTROL_Right) {
		m_direction.x = 1.0f;
		m_direction.y = 0.0f;
	}
	else if (control == PlayerControls::CONTROL_Up) {
		m_direction.x = 0.0f;
		m_direction.y = -1.0f;
	}
	else if (control == PlayerControls::CONTROL_Down) {
		m_direction.x = 0.0f;
		m_direction.y = 1.0f;
	}
	SetState(StateFigTypes::FIRGUE_Move);
}

void DynamicObject::Move(GLfloat deltaTime) {
	if (m_Speed != 0) {
		if (m_direction.x == 0.0f) {
			if ((m_moveLimited - m_Vec2DPos.y) * m_direction.y * m_moveLimited >= 0) {

				GLfloat y = m_Vec2DPos.y + m_Speed * m_direction.y * deltaTime;
				Set2DPosition(m_Vec2DPos.x, y);
			}
			else {
				if (m_State == StateFigTypes::FIRGUE_Inertia) {
					SetState(StateFigTypes::FIRGUE_Stand);
				}
			}
		}
		else {
			if ((m_moveLimited - m_Vec2DPos.x) * m_direction.x * m_moveLimited >= 0) {
				GLfloat x = m_Vec2DPos.x + m_Speed * m_direction.x * deltaTime;
				Set2DPosition(x, m_Vec2DPos.y);
			}
			else {
				if (m_State == StateFigTypes::FIRGUE_Inertia) {
					
					SetState(StateFigTypes::FIRGUE_Stand);
				}
			}
		}
	}
}

void DynamicObject::Update(GLfloat deltaTime) {
	Firgue::Update(deltaTime);
	Move(deltaTime);
}
void DynamicObject::SetState(StateFigTypes state) {
	switch (state) {
	case FIRGUE_Move:
	{
		m_moveLimited = 0;
		m_isLoop = true;
		m_Speed = 400;
		break;
	}
	case FIRGUE_Dead:
	{
		m_moveLimited = 0;
		m_isLoop = true;
		m_Speed = 0;
		break;
	}
	case FIRGUE_Success:
	{
		m_moveLimited = 0;
		m_isLoop = false;
		m_Speed = 0;
		break;
	}
	case FIRGUE_Stand:
	{
		m_moveLimited = 0;
		m_isLoop = true;
		m_Speed = 0;
		break;
	}
	case FIRGUE_Inertia:
	{
		m_isLoop = true;
		m_Speed = 200;
		m_direction.x = -m_direction.x;
		m_direction.y = -m_direction.y;
		SetMoveLimited();
	}

	default:
		m_isLoop = false;
	}
	Firgue::SetState(state);
}

void DynamicObject::SetMoveLimited() {
	switch (m_currentControl) {
	case  CONTROL_Down:
	{
		m_moveLimited = (m_rowIndex - 1) * 100 - 50;
		break;
	}
	case CONTROL_Up:
	{
		m_moveLimited = (m_rowIndex + 1) * 100 - 50;
		break;
	}
	case CONTROL_Left:
	{
		m_moveLimited = (m_colIndex + 1) * 100 - 50;
		break;
	}
	case CONTROL_Right:
		m_moveLimited = (m_colIndex - 1) * 100 - 50;
		break;
	}
}