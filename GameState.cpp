#include "GameState.h"
#include "ITS.h"

namespace RAT
{

GameState::GameState(const State state)
		: mState(state), mNextState(0), mIsActive(false)
{
	
}

GameState::~GameState()
{
    ITS::GetRootS()->removeFrameListener(this);
}

GameState::State GameState::getState() const
{
	return mState;
}

void GameState::switchState(GameState* nextState)
{
	mNextState = nextState;
}

void GameState::applyState()
{
		// �������������
    ITS::GetRootS()->addFrameListener(this);

		// callback �� �������� ����� � ���������
	enteredState();

	mIsActive = true;
}

bool  GameState::frameEnded(const Ogre::FrameEvent& evt)
{
		// ������������ ���������. ������� FrameListner ����� ������ � ����� �����, ����� ������ frameEnded
	if (mNextState)
	{
		GameState* nextState = mNextState;
		delete this;

			// ������ � ����� ���������
		nextState->applyState();
		
	}

	return true;
}

}	
