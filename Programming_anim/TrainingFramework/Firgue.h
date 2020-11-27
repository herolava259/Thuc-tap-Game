#pragma once
#include"SpriteAnimation.h"
#include"ResourceManagers.h"

enum ImpactEvents {
	IMPACT_Invalids = 0,
	IMPACT_Collision,
	IMPACT_Fallingdown,
	IMPACT_Final,
	IMPACT_Pickcake,
	IMPACT_Eaten,
	IMPACT_Frozen,
	IMPACT_Stop,
	IMPACT_Inertia,
	IMPACT_Hunt,
	IMPACT_Damage


};
enum StateFigTypes {
	FIRGUE_Invalids = 0,
	FIRGUE_Move,
	FIRGUE_Stand,
	FIRGUE_Success,
	FIRGUE_Dead,
	FIRGUE_Destroyed,
	FIRGUE_Inertia,
	FIRGUE_Silent,
	FIRGUE_Vibrate,
	FIRGUE_Eat,

};
enum  RoleFigTypes {
	ROLE_Invalids = 0,
	ROLE_DynamicObj,
	ROLE_StaticObj,
	ROLE_Player,
	ROLE_Enemy,
	ROLE_Scene,
	ROLE_Effect
};

enum EnemyTypes {
	ENEMY_Invalids = 0,
	ENEMY_Wolf,
	ENEMY_Golbin,
	ENEMY_Bear,
	ENEMY_Ghost,
};
enum SceneTypes {
	SCENE_Invalids = 0,
	SCENE_Stone,
	SCENE_Tree,
	SCENE_Pond,
	SCENE_Cake,
	SCENE_Hole,
	SCENE_Mine,
};
enum PlayerControls {
	CONTROL_Invalids,
	CONTROL_Right,
	CONTROL_Left,
	CONTROL_Up,
	CONTROL_Down
};
typedef struct AnimationAttribute {

	std::string name;
	bool isloop;
	StateFigTypes State;
	GLint numFrames;
	GLfloat framTime;


	/*AnimationAttribute(std::string _name, bool _isloop, StateFigTypes _State, GLint _numFrames, GLfloat _frameTime) {
		name = _name;
		isloop = _isloop;
		State = _State;
		numFrames = _numFrames;
		framTime = _frameTime;
	}*/

};


class Firgue : public SpriteAnimation {
private:
	GLint m_id;
protected:
	std::string m_Name;
	StateFigTypes m_State;
	RoleFigTypes m_RoleType;
	std::map<const std::string, AnimationAttribute> m_listAnimation;
	AnimationAttribute m_currAttrAnimation;
	bool m_isLoop;
	bool m_isChangeState;
	GLint m_rowIndex;
	GLint m_colIndex;
public:
	Firgue(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
	~Firgue();
	//StateAttribute GetStateAnimation() {
		//return m_currStateAnimation;
	//}
	void  AddAnimation(const std::string& str, StateFigTypes statetype, bool isloop, GLint numFrame, GLfloat frameTime);
	void LoadAnimation(const std::string str);

	bool IsChangeState();

	void SetState(StateFigTypes state);
	StateFigTypes GetState();

	void SetRoleType(RoleFigTypes role) {
		m_RoleType = role;
	}

	RoleFigTypes GetRoleState(){
		return m_RoleType;
	}

	void Update(GLfloat deltaTime);
	void Init();
	void Set2DPostion(GLfloat x, GLfloat y);
	Vector2 Get2DSize();
	bool isCollision(Firgue& fig);
};