#ifndef Tower_H
#define Tower_H

#include <Ogre.h>
#include "TowerBase.h"
#include "GameObject.h"
#include "Physics.h"

namespace RAT
{

class Tower : public TowerBase, public GameObject
{
public:
	Tower(const TowerBase& base);
	~Tower();

		// �������� ����� �� �����, node - ������������ ����
	void create(Ogre::SceneNode* node);

		// ������������� ��������� ��������� (��� ��������� ��������, ������������ SceneNode)
	void setPosition(const Ogre::Vector3& value);
	void setDirection(const Ogre::Vector3& value);

	virtual void update(const Ogre::Real dTime);

protected:

	Ogre::Vector3 mPosition;
	Ogre::Vector3 mDirection;
	
		// ������������ ������ ����� ������ ������ create()
	Ogre::SceneNode* mTowerSceneNode;
	Ogre::SceneNode* mTowerTopSceneNode;
	
	//std::vector<Weapon*> mWeapons;

	OgreBulletDynamics::RigidBody* mBody;
};

}

#endif