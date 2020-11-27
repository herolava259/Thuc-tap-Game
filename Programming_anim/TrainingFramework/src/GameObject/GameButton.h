#pragma once 
#include "Sprite2D.h"
#include "GameStates/GSPlay.h"
class GameButton : public Sprite2D
{
public:
	GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameButton();
	void	SetOnClick(void	(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	//void    SetOnClick(void(GSPlay* pBtClick)());

private:
	void	(*m_pBtClick)();
	bool	m_isHandle;

};
