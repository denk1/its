#ifndef GSStart_H
#define GSStart_H

#include "GameState.h"

namespace RAT
{

	// ��������� ���� - �������������
class GSStart : public GameState
{
public:
	GSStart();

		// �������������� ��� ���������, ��� ��������� ��������� ����
	void startGame();

protected:

	~GSStart();

		// �� ����������, �.�. ��� ������ ���������
	virtual void enteredState(){}



};

}

#endif
