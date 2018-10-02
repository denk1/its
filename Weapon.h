#ifndef Weapon_H
#define Weapon_H

#include <Ogre.h>

namespace RAT
{

	// �������� ������.
struct WeaponDescription
{
	Ogre::String	mMeshFile;	// ������
	Ogre::String	mType;		// ��� ������
	Ogre::Real		mMinAngle;	// ������������ ���� �������� ������ ������� �������
	Ogre::Real		mMaxAngle;	// ������������ ���� �������� ��� ������� �������
	Ogre::Real		mRotateSpeed;	// �������� ��������
	Ogre::Vector3	mPosition;		// �������� ������������ ���������
	Ogre::Real		mBaseDamage;	// ������� ����
	Ogre::Real		mReloadTime;	// ����� �����������
	
	WeaponDescription()
		: mMeshFile("")
		, mType("")
		, mMinAngle(0.f)
		, mMaxAngle(0.f)
		, mRotateSpeed(0.f)
		, mPosition()
		, mBaseDamage(0.f)
		, mReloadTime(0.f)
	{
	}
};

	// ����� ������. ������������ ��� ������ �����, ��� � �����.
class Weapon
{
public:

	Weapon(const WeaponDescription& desc);
	virtual ~Weapon(){}

	const WeaponDescription& getDescription();

	//const Ogre::Vector3& getDirection();
	// ������ ������������ ����� � �������� ����������� �� �����, �������� ������� "�������� ��������"  
	//virtual void rotateTo(const Ogre::Vector3& direction);

	// ���������� �������� ���� ������
	virtual Ogre::SceneNode* getSceneNode();

	virtual void setOrientation(const Ogre::Radian angle);

	// ������� ������ � �������� �� �����.
	virtual void create(Ogre::SceneNode* parentNode) = 0;

	// ������ ��������
	virtual void startShoot(const Ogre::Real dTime) = 0;
	// ��������� ��������
	virtual void stopShoot(const Ogre::Real dTime) = 0;
	// ���������� ������ ����
	virtual void update(const Ogre::Real dTime) = 0;

	
protected:

	WeaponDescription mDescription;

	Ogre::SceneNode* mSceneNode;
};

}

#endif