#include <iostream>
#include <ctime>
using namespace std;

void PlanB(int nextOperationNum);

class BadConnectionException : public exception
{
public:
	BadConnectionException(string message) : exception(message.c_str()) {}
};

class Robot
{
public:
	virtual void WalkStraightForward(int steps) = 0;
	virtual void TurnRight() = 0;
	virtual void TurnLeft() = 0;
	virtual void DefuseBomb() = 0;
};

class RobotBombDefuser : public Robot
{
private:
	int robotConfiguredWavelength = 41;
	bool isConnected = false;

public:
	void ConnectWireless(int communicationWaveLength)
	{
		if (communicationWaveLength == robotConfiguredWavelength)
		{
			isConnected = IsConnectedImmitatingConnectivitiyIssues();
		}
	}
	bool IsConnectedImmitatingConnectivitiyIssues()
	{
		return (rand() % 10) < 6; // immitates 60% good connection, aka. very bad
	}
public:
	bool IsConnected()
	{
		isConnected = IsConnectedImmitatingConnectivitiyIssues();
		return isConnected;
	}
	virtual void WalkStraightForward(int steps)
	{
		cout << "Did " << steps << " steps forward...\n";
	}

	virtual void TurnRight()
	{
		cout << "Turned right...\n";
	}

	virtual void TurnLeft()
	{
		cout << "Turned left...\n";
	}

	virtual void DefuseBomb()
	{
		cout << "Cut red or green or blue wire...\n";
	}
};

class RobotBombDefuserProxy : public Robot
{
private:
	RobotBombDefuser* _robotBombDefuser = new RobotBombDefuser();
	int _communicationWaveLength;
	int _connectionAttempts = 3;

	void EnsureConnectedWithRobot()
	{
		if (_robotBombDefuser == nullptr)
		{
			_robotBombDefuser = new RobotBombDefuser();
			_robotBombDefuser->ConnectWireless(_communicationWaveLength);
		}

		for (int i = 0; i < _connectionAttempts; i++)
		{
			if (_robotBombDefuser->IsConnected() == false)
			{
				_robotBombDefuser->ConnectWireless(_communicationWaveLength);
			}
			else
			{
				break;
			}
		}
		if (!_robotBombDefuser->IsConnected())
		{
			throw BadConnectionException("No connection with remote bomb diffuser robot could be made after few attempts.");
		}
	}

public:
	RobotBombDefuserProxy(int communicationWaveLength)
	{
		_communicationWaveLength = communicationWaveLength;
	}

	void WalkStraightForward(int steps)
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->WalkStraightForward(steps);
	}

	void TurnRight()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->TurnRight();
	}

	void TurnLeft()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->TurnLeft();
	}

	void DefuseBomb()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->DefuseBomb();
	}

};

void main()
{
	srand(time(0));

	int opNum = 0;
	try
	{
		RobotBombDefuserProxy* proxy = new RobotBombDefuserProxy(41);
		proxy->WalkStraightForward(100);
		opNum++;
		proxy->TurnRight();
		opNum++;
		proxy->WalkStraightForward(5);
		opNum++;
		proxy->DefuseBomb();
		opNum++;

		cout << endl;
	}
	catch (BadConnectionException& e)
	{
		cout << "Exception has been caught with message: (" << e.what() << "). Decided to have human operate robot there.\n";
		PlanB(opNum);
	}

	system("pause");
}

void PlanB(int nextOperationNum)
{
	RobotBombDefuser humanOperatingRobotDirectly = RobotBombDefuser();

	if (nextOperationNum == 0)
	{
		humanOperatingRobotDirectly.WalkStraightForward(100);
		nextOperationNum++;
	}
	if (nextOperationNum == 1)
	{
		humanOperatingRobotDirectly.TurnRight();
		nextOperationNum++;
	}
	if (nextOperationNum == 2)
	{
		humanOperatingRobotDirectly.WalkStraightForward(5);
		nextOperationNum++;
	}
	if (nextOperationNum == 3)
	{
		humanOperatingRobotDirectly.DefuseBomb();
	}
}