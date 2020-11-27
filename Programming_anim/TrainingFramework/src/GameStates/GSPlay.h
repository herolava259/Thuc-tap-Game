#pragma once
#include "gamestatebase.h"
#include "Firgue.h"
#include"OptWinObject.h"
#include<queue>
#include"Enemy.h"
#include"Player.h"
#include"StaticObject.h"


class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);

	void DrawMainWin();
	void DrawSubWindow();
	void Draw();

	void Pause_and_OpenWindow();
	void Play_and_CloseWindow();

	void SetControl();
	void SetNewPostionForBullet();
	void ConfirmCollision();
	void PlayervsEnemy();
	void EnemyvsScene();
	void PlayervsScene();
	void EnemyvsEnemy();
	void SetNextControl();
	void CheckDead();
	void CheckFinal();
	

	void UpdateObj(GLfloat deltaTime);
private:
	
	//std::vector<std::shared_ptr<Firgue>> m_listFirgue;
	
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<OptWinObject> m_GameOverWindow;
	std::shared_ptr<Text>  m_score;
	//std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::queue<PlayerControls> m_queueControl;
	std::vector<std::shared_ptr<Enemy>> m_listEnemy;
	std::vector<std::shared_ptr<StaticObject>> m_listScene;
	std::shared_ptr<OptWinObject> m_OptionWindow;
	std::vector<std::shared_ptr<GameButton>> m_listButton;
	std::shared_ptr<Player> m_Player;
	bool m_isGameOver;
	PlayerControls m_currentControl;
	bool m_isStaticState;
	bool m_isDead;
	bool m_isPlayMain;
	bool m_isPlay;
	
	// 
	//std::vector<std::vector<std::shared_ptr<Firgue>>> m_listLine;
	//std::vector<std::vector<std::shared_ptr<Firgue>>> m_listCol;
};

