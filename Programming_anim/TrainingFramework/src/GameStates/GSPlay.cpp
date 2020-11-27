#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include"Firgue.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{

}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	m_isGameOver = false;
	PlayerControls m_currentControl = PlayerControls::CONTROL_Invalids;
	m_isStaticState = true;
	m_isDead = false;
	m_isPlayMain =true; 
	m_isPlay =true;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	
	auto texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(100, 50);
	button->SetSize(100, 25);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Resume();
		});
	m_listButton.push_back(button);
	auto texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(250, 50);
	button->SetSize(100, 25);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Pause();
		});
	m_listButton.push_back(button);

	auto texture = ResourceManagers::GetInstance()->GetTexture("button_option");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 50, screenHeight - 100);
	button->SetSize(100, 25);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Pause_and_OpenWindow();
		});

	//Option Sub-Window
	
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_subwin_animation");

	m_OptionWindow = std::make_shared<OptWinObject>(model, shader, texture, 18, 0.1f);
	m_OptionWindow->SetBackGround("bg_subwin_static");

	m_OptionWindow->AddButton("button_subwin_resume", 100, 25, 350, 200, []() {
		GameStateMachine::GetInstance()->CurrentState()->Play_and_CloseWindow();
		});
	m_OptionWindow->AddButton("bg_subwin_mute", 100, 25, 450, 200, []() {
		// function mute to GSPlay
		});
	m_OptionWindow->AddButton("button_subwin_unmute", 100, 25,550, 200 ,[]() {
		// function unmute to GSPlay
		});
	m_OptionWindow->AddButton("button_subwin_close", 30, 30, 385, 15, []() {
		GameStateMachine::GetInstance()->CurrentState()->Play_and_CloseWindow();
		});
	// Game Over Sub_Widow
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_subwin_animation");
	m_GameOverWindow = std::make_shared<OptWinObject>(model, shader, texture, 18, 0.1f);
	m_GameOverWindow->SetBackGround("bg_subwin_static");

	m_GameOverWindow->AddButton("button_reset_gameplay", 100, 25, 350, 100, []() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});

	m_GameOverWindow->AddButton("button_next_gameplay", 100, 25, 450, 100, []() {
		// Next Game Play 
		});
	
	m_GameOverWindow->AddButton("button_back", 100, 25, 450, 100, []() {
		GameStateMachine::GetInstance()->BackState();
		});
	// Enemy
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Wolf_Stand");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 18, 0.1f);
	enemy->Set2DPosition(240, 400);
	enemy->SetSize(50, 50);
	enemy->SetEnemyType(EnemyTypes::ENEMY_Wolf);
	enemy->SetState(StateFigTypes::FIRGUE_Stand);
	enemy->AddAnimation("Wolf_Move", StateFigTypes::FIRGUE_Move, true, 18, 0.1f);
	enemy->AddAnimation("Wolf_Hunt", StateFigTypes::GIRGUE_Eat, false, 18, 0.1f);
	enemy->AddAnimation("Wolf_Dead", StateFigTypes::FIRGUE_Dead, false, 18, 0.1f);
	enemy->AddAnimation("Wolf_Inertia", StateFigTypes::FIRGUE_Inertia, false, 18, 0.1f);
	enemy->AddAnimation("Wolf_Stand", StateFigTypes::FIRGUE_Stand, true, 18, 0.1f);
	m_listEnemy.push_back(enemy);
	//Player
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Player_Stand");
	m_Player = std::make_shared<Player>(model, shader, texture, 18, 0.1f);
	m_Player->Set2DPosition(240, 500);
	m_Player->SetSize(50, 50);
	m_Player->SetState(StateFigTypes::FIRGUE_Stand);
	m_Player->AddAnimation("Player_Move", StateFigTypes::FIRGUE_Move, true, 18, 0.1f);
	m_Player->AddAnimation("Player_Dead", StateFigTypes::FIRGUE_Dead, false, 18, 0.1f);
	m_Player->AddAnimation("Player_Inertia", StateFigTypes::FIRGUE_Inertia,false, 18, 0.1f);
	m_Player->AddAnimation("Player_Stand", StateFigTypes::FIRGUE_Stand, true, 18, 0.1f);
	
	ResourceManagers::GetInstance()->PlaySound("bground");
}

void GSPlay::Exit()
{
	exit(0);
}

void GSPlay::CheckDead() {
	if (m_Player->GetState() == StateFigTypes::FIRGUE_Dead) {
		m_isDead = false;
	}
	for (int i = 0; i < m_listEnemy.size(); i++) {
		if (m_listEnemy[i]->GetState() == StateFigTypes::FIRGUE_Dead) {
			m_listEnemy.erase(m_listEnemy.begin() + i);
		}
	}
	for (int i = 0; i < m_listScene.size(); i++) {
		if (m_listScene[i]->GetState() == StateFigTypes::FIRGUE_Destroyed) {
			m_listEnemy.erase(m_listEnemy.begin() + i);
		}
	}
}


void GSPlay::Pause()
{
	m_isPlay = false;
}

void GSPlay::Resume()
{
	m_isPlay = true;
}


void GSPlay::HandleEvents()
{
	CheckDead();
	CheckFinal();
	ConfirmCollision();
	SetControl();
}
void GSPlay::CheckFinal() {
	if (m_isDead ) {
		// GameOver
		m_isGameOver = true;
		m_isPlayMain = false;
	}
	if (m_Player->GetState() == StateFigTypes::FIRGUE_Success) {
		//Final
		m_isGameOver = true;
		m_isPlayMain = false;
	}
}

void GSPlay::SetControl() {
	bool isAllStand = true;
	PlayerControls nextcontrol  = PlayerControls::CONTROL_Invalids;
	while (isAllStand) {
		if (m_Player->GetState() != StateFigTypes::FIRGUE_Stand) {
			isAllStand = false;
			return;
		}
		for (auto it : m_listEnemy) {
			if (it->GetState() != StateFigTypes::FIRGUE_Stand) {
				isAllStand = false;
				return;
			}
		}
		for (auto it : m_listScene) {
			if (it->GetState() != StateFigTypes::FIRGUE_Stand) {
				isAllStand = false;
				return;
			}
		}
	}
	if (!isAllStand) return;
	if (m_queueControl.empty()) return;
	nextcontrol = m_queueControl.front();
	m_queueControl.pop();
	m_Player->SetControl(nextcontrol);
	for (auto it : m_listEnemy) {
		it->SetControl(nextcontrol);
	}

}
void GSPlay::ConfirmCollision() {
	PlayervsEnemy();
	PlayervsScene();
	EnemyvsEnemy();
	EnemyvsScene();
}
void GSPlay::PlayervsEnemy() {
	for (auto it: m_listEnemy) {
		GLint disx = m_Player->Get2DPosition().x - it->Get2DPosition().x;
		GLint maxdis = m_Player->Get2DSize().x + it->Get2DSize().x;
		GLint disy = m_Player->Get2DPosition().y - it->Get2DPosition().y;
		if ((disx >= -maxdis && disx <= maxdis) || (disy >= -maxdis && disy <= maxdis)) {
			m_Player->CatchEvent(ImpactEvents::IMPACT_Eaten);
			it->CatchEvent(ImpactEvents::IMPACT_Hunt);
		}
	}
}
void GSPlay::PlayervsScene(){
	for (auto it : m_listScene) {
		GLint disx = m_Player->Get2DPosition().x - it->Get2DPosition().x;
		GLint maxdis = m_Player->Get2DSize().x + it->Get2DSize().x;
		GLint disy = m_Player->Get2DPosition().y - it->Get2DPosition().y;
		if ((disx >= -maxdis && disx <= maxdis) || (disy >= -maxdis && disy <= maxdis)) {
			switch (it->GetSceneType()) {
			case SceneTypes::SCENE_Cake:
			{
				m_Player->CatchEvent(ImpactEvents::IMPACT_Pickcake);
				it->CatchEvent(ImpactEvents::IMPACT_Damage);
				break;
			}
			case SceneTypes::SCENE_Hole:
			{
				m_Player->CatchEvent(ImpactEvents::IMPACT_Fallingdown);
				it->CatchEvent(ImpactEvents::IMPACT_Invalids);
				break;
			}
			case SceneTypes::SCENE_Stone:
			{
				m_Player->CatchEvent(ImpactEvents::IMPACT_Collision);
				it->CatchEvent(ImpactEvents::IMPACT_Collision);
				break;
			}
			case SceneTypes::SCENE_Tree:
			{
				m_Player->CatchEvent(ImpactEvents::IMPACT_Collision);
				it->CatchEvent(ImpactEvents::IMPACT_Collision);
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}
void GSPlay::EnemyvsEnemy() {

}

void GSPlay::EnemyvsScene() {
	for (auto it : m_listEnemy) {
		for (auto iter : m_listScene) {
			GLint disx = iter->Get2DPosition().x - it->Get2DPosition().x;
			GLint maxdis = iter->Get2DSize().x + it->Get2DSize().x;
			GLint disy = it->Get2DPosition().y - it->Get2DPosition().y;
			if ((disx >= -maxdis && disx <= maxdis) || (disy >= -maxdis && disy <= maxdis)) {
				switch (iter->GetSceneType()) {
				case SceneTypes::SCENE_Cake:
				{
					it->CatchEvent(ImpactEvents::IMPACT_Pickcake);
					iter->CatchEvent(ImpactEvents::IMPACT_Damage);
					break;
				}
				case SceneTypes::SCENE_Hole:
				{
					it->CatchEvent(ImpactEvents::IMPACT_Fallingdown);
					iter->CatchEvent(ImpactEvents::IMPACT_Invalids);
					break;
				}
				case SceneTypes::SCENE_Stone:
				{
					it->CatchEvent(ImpactEvents::IMPACT_Collision);
					iter->CatchEvent(ImpactEvents::IMPACT_Collision);
					break;
				}
				case SceneTypes::SCENE_Tree:
				{
					it->CatchEvent(ImpactEvents::IMPACT_Collision);
					iter->CatchEvent(ImpactEvents::IMPACT_Collision);
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (m_isPlay && m_isPlayMain) {
		if (!bIsPressed) {
			if (key == KEY_LEFT || key == KEY_MOVE_LEFT) {
				m_queueControl.push(PlayerControls::CONTROL_Left);
			}
			else if (key == KEY_RIGHT || key == KEY_MOVE_RIGHT) {
				m_queueControl.push(PlayerControls::CONTROL_Right);
			}
			else if (key == KEY_UP || key == KEY_MOVE_FORWORD) {
				m_queueControl.push(PlayerControls::CONTROL_Up);
			}
			else if (key == KEY_DOWN || key == KEY_MOVE_BACKWORD) {
				m_queueControl.push(PlayerControls::CONTROL_Down);
			}
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	bool isTouchButton = false;
	if (m_isPlayMain) {
		for (auto it : m_listButton) {
			it->HandleTouchEvents(x, y, bIsPressed);
			if(it->IsHandle()){
				isTouchButton =true;
				break;
			}
		}
	}
	if (!m_isPlayMain) {
		if (!m_isGameOver) {
			m_OptionWindow->HandleTouchEvents(x, y, bIsPressed);
		}
		else {
			m_GameOverWindow->HandleTouchEvents(x, y, bIsPressed);
		}
	}
	if (m_isPlay && m_isPlayMain&&!isTouchButton) {
		if (!bIsPressed) {
			Vector2 Vec2DPos;
			GLint dis_x = Vec2DPos.x - x;
			GLint dis_y = Vec2DPos.y - y;
			if (abs_value(x) > abs_value(y)) {
				if (dis_x < 0) {
					m_queueControl.push(PlayerControls::CONTROL_Left);
				}
				else {
					m_queueControl.push(PlayerControls::CONTROL_Right);
				}
			}
			else {
				if (dis_y < 0) {
					m_queueControl.push(PlayerControls::CONTROL_Down);
				}
				else {
					m_queueControl.push(PlayerControls::CONTROL_Up);
				}
			}

		}
	}

}

void GSPlay::Update(float deltaTime)
{
	
	if (m_isPlay && m_isPlayMain) {
		HandleEvents();
		UpdateObj(deltaTime);
	}
	if (!m_isPlayMain) {
		m_OptionWindow->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	if (!m_isPlayMain) {
		DrawSubWindow();
	}
	DrawMainWin();
}

void GSPlay::SetNewPostionForBullet()
{

}


GLint abs_value(GLint x) {
	return(x > 0 ? x : -x);
}

void GSPlay::UpdateObj(GLfloat deltaTime) {
	for (auto it : m_listEnemy) {
		it->Update(deltaTime);
	}
	for (auto it : m_listScene) {
		it->Update(deltaTime);
	}
	m_Player->Update(deltaTime);
}

void GSPlay::Pause_and_OpenWindow() {
	m_isPlayMain = false;
}
void GSPlay::Play_and_CloseWindow() {
	m_OptionWindow->TurnOff();
	m_isPlayMain = true;
}
void GSPlay::DrawMainWin() {
	m_Player->Draw();
	for (auto it : m_listEnemy) {
		it->Draw();
	}
	for (auto it : m_listScene) {
		it->Draw();
	}
	for (auto it :m_listButton) {
		it->Draw();
	}
}
void GSPlay::DrawSubWindow() {
	if (!m_isGameOver) {
		m_OptionWindow->Draw_All();
	}
	else {
		m_GameOverWindow->Draw_All();
	}
}