#ifndef GameState_H
#define GameState_H

#include <Ogre.h>

namespace RAT
{

	// ����������� �����, ������������ ����� ��������� ����
class GameState :  public Ogre::FrameListener
{
public:
		// ������������ ��������� ���������, ������������� ���������������� ��������.
	enum State
	{
		StStart,
		StMainMenu,
		StLoading,
		StMap,
		StServerList,
		StEnd
	};
		// � ������������ �������� ������ ���� ������ ������� ������������� ���������, ��������� � enteredState()
	GameState(const State state);

	State getState() const;

		// ������ �� ����� ���������. ����� ������ ������� ��������� ����� �������. 
		// �������� ��������� �������� ������ ���� �������, �������: FrameListner.
	virtual void switchState(GameState* nextState);

protected:

	virtual ~GameState();

		// ���� ����� ���������� ����� ���� ��� ���������� ��������� �����������, 
		// ���� ������� � ����� ��������� � ������������ �������� Ogre::FrameListener
	virtual void enteredState() = 0;

		// Ogre::FrameListener
	virtual bool frameEnded(const Ogre::FrameEvent& evt);

	State mState;
	GameState* mNextState;
	bool		mIsActive; // �������� �� ��������� ��������

private:

		// ������� � ����� ���������. �� ����������������.
	void applyState();

};

}

#endif
