#ifndef WGun_H
#define WGun_H

#include <Ogre.h>
#include "Weapon.h"

namespace RAT
{

class WGun: public Weapon
{
public:

	WGun(const WeaponDescription& desc);
	virtual ~WGun();

	// ������� ������ � �������� �� �����.
	virtual void create(Ogre::SceneNode* parentNode);

	// ������ ��������
	virtual void startShoot(const Ogre::Real dTime);
	// ��������� ��������
	virtual void stopShoot(const Ogre::Real dTime);
	// ���������� ������ ����
	virtual void update(const Ogre::Real dTime);

};

}

#endif