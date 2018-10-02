#ifndef WRocketLauncher_H
#define WRocketLauncher_H

#include <Ogre.h>
#include "Weapon.h"

namespace RAT
{

class WRocketLauncher: public Weapon
{
public:

	WRocketLauncher(const WeaponDescription& desc);
	virtual ~WRocketLauncher();

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