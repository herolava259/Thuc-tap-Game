#pragma once
#include"GameManager/Singleton.h"
#include"GameConfig.h"
#include"Firgue.h"
#include"Enemy.h"

class ObjectManagers : public CSingleton<ObjectManagers>
{
private:
	std::vector<std::shared_ptr<Enemy>> m_listEnemy;

public:

};