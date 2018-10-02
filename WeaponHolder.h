#ifndef WeaponHolder_H
#define WeaponHolder_H

#include <Ogre.h>
#include "Weapon.h"

namespace RAT
{

struct HolderDescription
{
	Ogre::String	mMeshFile;
	float			mMaxAngle;
	float			mRotateSpeed;
	Ogre::Vector3	mPosition;

	HolderDescription()
		: mMeshFile("")
		, mMaxAngle(0)
		, mRotateSpeed(0)
		, mPosition(0,0,0)
	{
	}
};

	// ��������� � �������
class WeaponHolder
{
public:

	WeaponHolder();
	WeaponHolder(const WeaponHolder&);

	virtual ~WeaponHolder();

	void setDesctiption(const HolderDescription& desc);
	const HolderDescription& getDescription();

	void addWeapon(Weapon* weapon);

	void create(Ogre::SceneNode* parentNode);

	virtual Ogre::SceneNode* getSceneNode();

	virtual void setOrientation(const Ogre::Radian yaw, const Ogre::Radian pitch);

	// ������ ��������
	virtual void startShoot(const Ogre::Real dTime);
	// ��������� ��������
	virtual void stopShoot(const Ogre::Real dTime);
	// ���������� ������ ����
	virtual void update(const Ogre::Real dTime);

protected:
	HolderDescription mDescription;
	std::vector<Weapon*> mWeapons;

	Ogre::SceneNode* mSceneNode;
};

}

#endif

