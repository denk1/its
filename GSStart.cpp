#include "GSStart.h"
#include "GSMainMenu.h"
#include "MyTestApp.h"

namespace RAT
{

GSStart::GSStart()
	: GameState(GameState::StStart)
{
	// � ���� ��������� �������� ����� ������������� ������. 
	// ���� ����� ������� � ������� ����
	mIsActive = true;
    MyTestApp::GetRootS()->addFrameListener(this);
}

void GSStart::startGame()
{
    MyTestApp::getSingleton().switchState(new GSMainMenu());
	
}

GSStart::~GSStart()
{

}

}
