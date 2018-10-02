#ifndef GameObject_H
#define GameObject_H

#include <Ogre.h>

namespace RAT
{

class GameObject
{
public:

	enum GameObjectType
	{
		Tower, BonusBuilding, Bonus
	};

	GameObject(GameObjectType type)
		:mType(type)
	{

	}

	virtual ~GameObject()
	{
	}

		// ��������� ������� �� �����
	virtual void create(Ogre::SceneNode*) = 0;

		// ���������� ������ ����, �� ������� FrameRenderingQueued.
		// �������� ����������� FrameListner, ������� ���������� �������� �������
	virtual void update(const Ogre::Real dTime){}

	GameObjectType getType()
	{
		return mType;
	}

protected:

	GameObjectType mType;

};

}

#endif