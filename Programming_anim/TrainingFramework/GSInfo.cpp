#include"GSInfo.h"


extern int screenWidth;
extern int screenHeight;


GSInfo::GSInfo() {
	
}

GSInfo::~GSInfo(){

}

void GSInfo::Init() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 200);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

}

void GSInfo::Exit() {

}

void GSInfo::Pause() {

}

void GSInfo::Resume() {

}

void GSInfo::HandleEvents() {

}

void GSInfo::HandleKeyEvents(int key, bool bIsPressed) {

}

void GSInfo::HandleTouchEvents(int x, int y, bool bIsPressed) {
	for (auto it : m_listButton) {
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}


void GSInfo::Update(float deltaTime) {
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton) {
		it->Update(deltaTime);
	}
}

void GSInfo::Draw() {
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gamName->Draw();
}