#include "Vehicle.h"
#include "ITS.h"
#include "WeaponFactory.h"

namespace RAT
{

Vehicle::Vehicle(const VehiclePrototype& prototype)
	: VehicleBase(prototype)
	, mControlledWeapon(0)
	, mWeapons(mConnectionPoints.size(), 0)
{
}

Vehicle::~Vehicle()
{
	for(WeaponsVec::iterator it = mWeapons.begin(); it != mWeapons.end(); ++it)
		if (*it)
			delete *it;
}

void Vehicle::create(Ogre::SceneNode* parentSN)
{
	VehicleBase::create(parentSN);
}

void Vehicle::connectWeapon(const int connectionPoint, WeaponHolder* weaponHolder)
{
	if (connectionPoint >= mWeapons.size())
		return;

		// ������� ������ ������
	if (mWeapons[connectionPoint])
		delete mWeapons[connectionPoint];

	mWeapons[connectionPoint] = weaponHolder;
	if (!mConnectionPoints[connectionPoint].mIsStatic)
		mControlledWeapon = weaponHolder;

	weaponHolder->create(mCPNodes[connectionPoint]);
}

bool Vehicle::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	for(WeaponsVec::iterator it = mWeapons.begin(); it != mWeapons.end(); ++it)
		if (*it)
			(*it)->update(evt.timeSinceLastFrame);

	
	if (mControlledWeapon)
	{
        const Ogre::Quaternion& camRot = TPCamera::getCameraSN()->getOrientation();
		Ogre::Degree yaw = camRot.getYaw() - mControlledWeapon->getSceneNode()->getParentSceneNode()->_getDerivedOrientation().getYaw();
			// ��������� ���� ������� ������
        Ogre::Vector3 direction = TPCamera::getCameraSN()->getOrientation().zAxis() * -1;
		Ogre::Real len = direction.length();
		Ogre::Degree pitch(Ogre::Radian(Ogre::Math::ASin(direction.y / len)));

		mControlledWeapon->setOrientation(yaw, pitch);

	}

	return VehicleBase::frameRenderingQueued(evt);
}

}
