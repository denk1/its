#include "TPCamera.h"
#include "ITS.h"

template<> RAT::TPCamera* Ogre::Singleton<RAT::TPCamera>::msSingleton = 0;

namespace RAT
{

TPCamera::TPCamera()
	:mVelocity(60), mSencivity(0.001), mYaw(0), mPitch(0),
    mGoingBack(false),
    mGoingForward(false),
    mGoingLeft(false),
    mGoingRight(false),
    mTarget(0),
    mFollowVehicle(false),
    mIts(ITS::getSingleton()),
    mSignDirection(-1)
{
    mCamera = mIts.getSceneManager()->createCamera("PlayerCam");
    mCameraSN = mIts.getSceneManager()->getRootSceneNode()->createChildSceneNode("mCameraSceneNode");
    mCameraSN->attachObject(mCamera);
    //mCamera->setPosition(Ogre::Vector3(0, 200, 200));
    mCameraSN->setPosition(Ogre::Vector3(300, 100, 450));
    mCameraSN->lookAt(Ogre::Vector3(0,0,0), Ogre::Node::TS_WORLD );
    mCamera->setNearClipDistance(1);
    mCamera->setCastShadows(false);
	//mCamera->setAutoAspectRatio(true);
    mCamera->setAspectRatio(
        Ogre::Real(mIts.getWindow()->getWidth()) / Ogre::Real(mIts.getWindow()->getHeight()));
	
    mCameraSN->setOrientation(Ogre::Quaternion(Ogre::Radian(mPitch),Ogre::Vector3::UNIT_Y)*Ogre::Quaternion(Ogre::Radian(mYaw),Ogre::Vector3::UNIT_X));
}

TPCamera::~TPCamera()
{
}

void TPCamera::setTarget(Ogre::SceneNode* target, const Ogre::Real dist)
{
	mTarget = target;
	mFollowVehicle = false;
	mTargetDistance = dist;

	mYaw = 0;
	mPitch = 0;
}

void TPCamera::setTargetVehicle(Ogre::SceneNode* target, const Ogre::Real dist)
{
	mTarget = target;
    mFollowVehicle = true; // was true
	mTargetDistance = dist;

	mYaw = 0;
	mPitch = 0;
}

void TPCamera::update()
{
	if (mTarget)
	{
		if (mFollowVehicle)
		{
            Ogre::Vector3 testPosCam = mTarget->_getDerivedPosition();
			Ogre::Vector3 dir = mTarget->_getDerivedOrientation() * Ogre::Quaternion(Ogre::Radian(mYaw), Ogre::Vector3::UNIT_Y) *Ogre::Quaternion(Ogre::Radian(mPitch), Ogre::Vector3::UNIT_X) * Ogre::Vector3(0,0,1);
			dir.normalise();
            mCameraSN->setPosition(mTarget->_getDerivedPosition() + Ogre::Vector3(0, 3.0f, 0) + mSignDirection*dir*mTargetDistance);
            mCameraSN->lookAt(mTarget->_getDerivedPosition() + Ogre::Vector3(0, 3.0f, 0), Ogre::Node::TS_WORLD );
			
		}
		else
		{
			// TODO: trac for non vehicle
		}
	}
}

bool TPCamera::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mTarget)
	{
		update();
	}
	else
	{
		Ogre::Vector3 delta = Ogre::Vector3::ZERO;

        if (mGoingRight) delta += mCameraSN->getOrientation().xAxis();
        if (mGoingLeft) delta -= mCameraSN->getOrientation().xAxis();
        if (mGoingForward) delta += mCameraSN->getOrientation().zAxis() * -1;
        if (mGoingBack) delta -= mCameraSN->getOrientation().zAxis() * -1;

		delta.normalise();

//        if (ITS::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Modifier::Shift))
//			delta *= 4;

        mCameraSN->translate(delta * mVelocity * evt.timeSinceLastFrame);
	}
		
	return true;
}


Ogre::Camera* TPCamera::getCamera()
{
	return mCamera;
}

Ogre::Camera* TPCamera::getCameraS()
{
    return TPCamera::getSingleton().mCamera;
}

Ogre::SceneNode *TPCamera::getCameraSN()
{
     return TPCamera::getSingleton().mCameraSN;
}



void TPCamera::rotate(Ogre::Real yaw, Ogre::Real pitch)
{
    mCameraSN->yaw(Ogre::Radian(-yaw*mSencivity));
    mCameraSN->pitch(Ogre::Radian(-pitch*mSencivity));
	
	if (mTarget)
	{
		mYaw -= yaw*mSencivity;
		mPitch -= pitch*mSencivity;
	}
	
}

void TPCamera::startGoingRight()
{
	mGoingRight = true;
}

void TPCamera::startGoingLeft()
{
	mGoingLeft = true;
}

void TPCamera::startGoingForward()
{
	mGoingForward = true;
}

void TPCamera::startGoingBack()
{
	mGoingBack = true;
}

void TPCamera::stopGoingRight()
{
	mGoingRight = false;
}

void TPCamera::stopGoingLeft()
{
	mGoingLeft = false;
}

void TPCamera::stopGoingForward()
{
	mGoingForward = false;
}

void TPCamera::stopGoingBack()
{
    mGoingBack = false;
}

void TPCamera::changeSignDirection(int sign)
{
    mSignDirection = sign;
}

bool TPCamera::setTargetFollowing()
{
    mCameraSN->setPosition(Ogre::Vector3(300, 100, 550));
    mFollowVehicle = !mFollowVehicle;
    return mFollowVehicle;
}

}
