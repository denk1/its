#ifndef VehiclePrototype_H
#define VehiclePrototype_H

#include <memory>

#include <Ogre.h>
#include "Physics.h"

namespace RAT
{
	// �������� ����������
struct VehicleProperties
{
	float	mRestitution; // ����������� ���������
    float	mFriction; // ����������� ������
    float	mMass; // �����

	float	mMaxEngineForce; // ������������ �������� ���������

	float	mSteeringIncrement; // �������� �������� ����
	float	mSteeringClamp; // ����������� ��������
	float	mSpeedClampAffection; // ������� �������� �� ������������ ������� ����
	float	mSpeedIncrementAffection; // ������� �������� �� �������� �������� ����

	float	mWheelRadius; // ������ ������
	float	mWheelWidth; // ������ ������

	float	mWheelFriction; // ����������� ������ ������
	float	mMaxSuspensionForce;
	float	mSuspensionStiffness; // 
	float	mSuspensionDamping; // �������������
	float	mSuspensionCompression; // �������� � ������ 

	float	mRollInfluence; // ������ �������
	float	mSuspensionRestLength; // ����� ������������ � ��������� ���������
	float	mMaxSuspensionTravelCm; // ������������ ������
	float	mFrictionSlip; //

	float	mLinearDamping; // ������� ������������� �������
	float	mAngularDamping; // ������� ������������� �������

	float	mWeelOffsetW; // �������� ������ �� ������ �� ������ ����������
	float	mWeelOffsetL; // �������� ������ �� ������ �� ����� ����������
	float	mWeelOffsetH; // �������� ������ �� ������ �� ������ ����������

	VehicleProperties()
		: mRestitution(0.6f)
		, mFriction(0.6f)
		, mMass(800)
		, mMaxEngineForce(6000.f)
		, mSteeringIncrement(0.04f)
		, mSteeringClamp(0.8f)

		, mWheelRadius(1.0f)
		, mWheelWidth(0.4f)

		, mWheelFriction(10.f)
		, mMaxSuspensionForce(1000.f)
		, mSuspensionStiffness(20.f)
		, mSuspensionDamping(2.3f)
		, mSuspensionCompression(4.4f)

		, mRollInfluence(0.1f)
		, mSuspensionRestLength(0.2f)
		, mMaxSuspensionTravelCm(500.f)
		, mFrictionSlip(10.5f)
		, mWeelOffsetW(1.5f)
		, mWeelOffsetL(3.f)
		, mWeelOffsetH(0.4f)
		, mLinearDamping(0.2f)
		, mAngularDamping(0.2f)
		, mSpeedClampAffection(1000.f)
		, mSpeedIncrementAffection(1000.f)
		{
		}
};

struct VehicleWheel
{
	float	mEngineForce; // �������� ��������� �� ������ ������
    float	mEngineBackForce; // �������� ��������� �� ������ ������ ��� ������ ����
    float	mBreakForce; // ���� ��������
	float	mHandBreakForce; // ���� ������ ��������
	Ogre::String mMesh;

	VehicleWheel()
		: mEngineForce(0.f)
		, mEngineBackForce(0.f)
		, mBreakForce(0.f)
		, mHandBreakForce(0.f)
		, mMesh("")
	{
	}
};


	// �������� ����������, ���������� ��� ������� ��������������
class VehiclePrototype
{

public:

	enum WCPType
	{
		WCHeavy,
		WCMedium,
		WCLight
	};

	static WCPType wcpTypeFromString(const Ogre::String& value);

	struct WCPoint // Weapon Connection Point
	{
		WCPType mType;				// ��� ������, ����������� ��� ���������
		bool mIsStatic;
		Ogre::Vector3 mPosition;	// ����� ��������� �����
		Ogre::Quaternion mRotation;	// ������� �����, ��� ��������� �� ��� �����

                WCPoint()
			: mType(VehiclePrototype::WCLight)
			, mIsStatic(true)
			, mPosition(Ogre::Vector3::ZERO)
			, mRotation(Ogre::Quaternion::ZERO)
		{
		}
	};

	enum WheelIndices
	{
		VFLWheelIndex = 0,	// Vehicle Front Left Wheel Index
		VFRWheelIndex = 1,	// Vehicle Front Right Wheel Index
		VRLWheelIndex = 2,	// Vehicle Rear Left Wheel Index
		VRRWheelIndex = 3	// Vehicle Rear Right Wheel Index
	};

	VehiclePrototype();
	virtual ~VehiclePrototype();

	const VehicleProperties& getProperties();
	void setProperties(const VehicleProperties& value);
	void setWheel(const int index, const VehicleWheel& wheel);

	void setName(const Ogre::String& value);
	void setMesh(const Ogre::String& value);
	void setResourceGroup(const Ogre::String& value);
	void setShape(OgreBulletCollisions::CollisionShape* shape);
	void addConnectionPoint(const WCPoint& point);
	Ogre::String getName();
	
protected:

		// ��������, ������� ��������������� ����� ���������� (����� ���� ���������)
        typedef std::shared_ptr<OgreBulletCollisions::CollisionShape> TShareShape;
	TShareShape mShape;
	
	VehicleProperties mProperties;
	VehicleWheel mWheels[4]; // ������ ������. �� ����������� ����, ����, ���� �������� ��
	std::vector<WCPoint> mConnectionPoints;
	Ogre::String mName;
	Ogre::String mResourceGroup;
	Ogre::String mMesh;
};

}

#endif
