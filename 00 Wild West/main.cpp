#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;


struct GAMEINFO {
	COORD PlayerOnePosition;
	COORD PlayerTwoPosition;
	COORD PlayerOneBullet;
	COORD PlayerTwoBullet;
	COORD PlayerOneBullet2;
	COORD PlayerTwoBullet2;
	COORD ZeroZero;
};

HANDLE hInput, hOutput;
GAMEINFO GameInfo;

void Movement(GAMEINFO &GameInfo)
{	
	INPUT_RECORD InputRecord;
	DWORD Events = 0;

	ReadConsoleInput(hInput, &InputRecord, 14, &Events);
	
	if(InputRecord.EventType == KEY_EVENT){
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_Q && InputRecord.Event.KeyEvent.bKeyDown == 1){
			Erase(GameInfo);
			GameInfo.PlayerOnePosition.Y--;
			if(GameInfo.PlayerOnePosition.Y < 03)
				GameInfo.PlayerOnePosition.Y++;
			Draw(GameInfo);
		}
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_A && InputRecord.Event.KeyEvent.bKeyDown == 1){
			Erase(GameInfo);
			GameInfo.PlayerOnePosition.Y++;
			if(GameInfo.PlayerOnePosition.Y > 242)
				GameInfo.PlayerOnePosition.Y--;
			Draw(GameInfo);
		}

		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_S && InputRecord.Event.KeyEvent.bKeyDown == 1){
			LaunchBullet(GameInfo, 1);
		}
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_O && InputRecord.Event.KeyEvent.bKeyDown == 1){
			Erase(GameInfo);
			GameInfo.PlayerTwoPosition.Y--;
			if(GameInfo.PlayerTwoPosition.Y < 0)
				GameInfo.PlayerTwoPosition.Y++;
			Draw(GameInfo);
		}

		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_L && InputRecord.Event.KeyEvent.bKeyDown == 1){
			Erase(GameInfo);
			GameInfo.PlayerTwoPosition.Y++;
			if(GameInfo.PlayerTwoPosition.Y > 24)
				GameInfo.PlayerTwoPosition.Y--;
			Draw(GameInfo);
		}

		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_K && InputRecord.Event.KeyEvent.bKeyDown == 1){
			LaunchBullet(GameInfo, 2);
		}

		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
			exit(0);

	}
	FlushConsoleInputBuffer(hInput);
}

void Draw(GAMEINFO GameInfo)
{
	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
	cout << "|";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
	cout << "|";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet);
	cout << ".";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet);
	cout << ".";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet2);
	cout << ".";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet2);
	cout << ".";
	
	GameInfo.ZeroZero.X = 0;
	GameInfo.ZeroZero.Y = 0;

	int i;
	for(i = 0; i < 79; i++){
		SetConsoleCursorPosition(hOutput, GameInfo.ZeroZero);
		cout << ".";
		GameInfo.ZeroZero.X++;
	}

}

void Erase(GAMEINFO GameInfo)
{
	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOnePosition);
	cout << " ";
	
	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoPosition);
	cout << " ";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet);
	cout << " ";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet);
	cout << " ";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerOneBullet2);
	cout << " ";

	SetConsoleCursorPosition(hOutput, GameInfo.PlayerTwoBullet2);
	cout << " ";
}

int LaunchBullet(GAMEINFO &GameInfo, int PlayerNumber)
{	
	int i;
	if(PlayerNumber == 1){
		GameInfo.PlayerOneBullet.Y = GameInfo.PlayerOnePosition.Y;
		GameInfo.PlayerOneBullet.X = GameInfo.PlayerOnePosition.X + 1;
		Draw(GameInfo);
		Erase(GameInfo);
		for(i = 0; i < 77; i++){
			GameInfo.PlayerOneBullet.X += 1;
			Draw(GameInfo);
	
			int move;
			move =	Wait();
			switch(move){
			case 1:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y--;
				if(GameInfo.PlayerOnePosition.Y < 0)
					GameInfo.PlayerOnePosition.Y++;
				break;
			case 2:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y++;
				if(GameInfo.PlayerOnePosition.Y > 24)
					GameInfo.PlayerOnePosition.Y--;
				break;
			case 3:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y--;
				if(GameInfo.PlayerTwoPosition.Y < 0)
					GameInfo.PlayerTwoPosition.Y++;
				break;
			case 4:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y++;
				if(GameInfo.PlayerTwoPosition.Y > 24)
					GameInfo.PlayerTwoPosition.Y--;
				break;
			case 5:
				LaunchBullet2(GameInfo, 1);
				return 0;
				break;
			default:
				LaunchBullet2(GameInfo, 2);
				return 0;
				break;
			}

			Draw(GameInfo);
			Erase(GameInfo);
			if(GameInfo.PlayerOneBullet.X == GameInfo.PlayerTwoPosition.X)
				if(GameInfo.PlayerOneBullet.Y == GameInfo.PlayerTwoPosition.Y){
					system("cls");
					cout << "\aPlayer 1 Wins" << endl;
					system("pause");
					exit(0);
				}
		}
		GameInfo.PlayerOneBullet.Y = 0;
		GameInfo.PlayerOneBullet.X = 0;
		Draw(GameInfo);
	}
	if(PlayerNumber == 2){
		GameInfo.PlayerTwoBullet.Y = GameInfo.PlayerTwoPosition.Y;
		GameInfo.PlayerTwoBullet.X = GameInfo.PlayerTwoPosition.X - 1;
		Draw(GameInfo);
		Erase(GameInfo);
		for(i = 0; i < 77; i++){
			GameInfo.PlayerTwoBullet.X -= 1;
			Draw(GameInfo);
		
			int move;
			move =	Wait();
			switch(move){
			case 1:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y--;
				if(GameInfo.PlayerOnePosition.Y < 0)
					GameInfo.PlayerOnePosition.Y++;
				break;
			case 2:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y++;
				if(GameInfo.PlayerOnePosition.Y > 24)
					GameInfo.PlayerOnePosition.Y--;
				break;
			case 3:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y--;
				if(GameInfo.PlayerTwoPosition.Y < 0)
					GameInfo.PlayerTwoPosition.Y++;
				break;
			case 4:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y++;
				if(GameInfo.PlayerTwoPosition.Y > 24)
					GameInfo.PlayerTwoPosition.Y--;
				break;
			case 5:
				LaunchBullet2(GameInfo, 1);
				return 0;
				break;
			case 6:
				LaunchBullet2(GameInfo, 2);
				return 0;
				break;
			}
			
			Draw(GameInfo);
			Erase(GameInfo);
			if(GameInfo.PlayerTwoBullet.X == GameInfo.PlayerOnePosition.X)
				if(GameInfo.PlayerTwoBullet.Y == GameInfo.PlayerOnePosition.Y){
					system("cls");
					cout << "\aPlayer 2 Wins" << endl;
					system("pause");
					exit(0);
			}
		}
		GameInfo.PlayerTwoBullet.Y = 20;
		GameInfo.PlayerTwoBullet.X = 791;
		Draw(GameInfo);
	}
	return 0;
}

int Wait()
{	
	INPUT_RECORD InputRecord;
	DWORD Events = 0;
	
	if(WAIT_TIMEOUT == WaitForSingleObject(hInput,1))
				return 0;
	ReadConsoleInput(hInput, &InputRecord, 11, &Events);

	if(InputRecord.EventType == KEY_EVENT){
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_Q && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 1;
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_A && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 2;
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_O && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 3;
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_L && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 4;
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_S && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 5;
		
		if(InputRecord.Event.KeyEvent.wVirtualKeyCode == VK_K && InputRecord.Event.KeyEvent.bKeyDown == 1)
			return 6;
	}
	FlushConsoleInputBuffer(hInput);
	return 0;
}

void LaunchBullet2(GAMEINFO &GameInfo, int PlayerNumber)
{
	if(PlayerNumber == 1){
		GameInfo.PlayerOneBullet2.X = GameInfo.PlayerOnePosition.X + 1;
		GameInfo.PlayerOneBullet2.Y = GameInfo.PlayerOnePosition.Y;

		Draw(GameInfo);
		Erase(GameInfo);
		int i;
		for(i = 0; i < 77; i++){
			GameInfo.PlayerOneBullet.X += 1;
			GameInfo.PlayerOneBullet2.X += 1;
			GameInfo.PlayerTwoBullet.X -= 1;
			GameInfo.PlayerTwoBullet2.X -= 1;
			Draw(GameInfo);
	
			int move;
			move =	Wait();
			switch(move){
			case 1:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y--;
				if(GameInfo.PlayerOnePosition.Y < 0)
					GameInfo.PlayerOnePosition.Y++;
				break;
			case 2:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y++;
				if(GameInfo.PlayerOnePosition.Y > 24)
					GameInfo.PlayerOnePosition.Y--;
				break;
			case 3:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y--;
				if(GameInfo.PlayerTwoPosition.Y < 0)
					GameInfo.PlayerTwoPosition.Y++;
				break;
			case 4:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y++;
				if(GameInfo.PlayerTwoPosition.Y > 24)
					GameInfo.PlayerTwoPosition.Y--;
				break;
			}

			Draw(GameInfo);
			Erase(GameInfo);
			if(GameInfo.PlayerOneBullet.X == GameInfo.PlayerTwoPosition.X)
				if(GameInfo.PlayerOneBullet.Y == GameInfo.PlayerTwoPosition.Y){
					system("cls");
					cout << "\aPlayer 1 Wins" << endl;
					system("pause");
					exit(0);
				}
			if(GameInfo.PlayerOneBullet2.X == GameInfo.PlayerTwoPosition.X)
				if(GameInfo.PlayerOneBullet2.Y == GameInfo.PlayerTwoPosition.Y){
					system("cls");
					cout << "\aPlayer 1 Wins" << endl;
					system("pause");
					exit(0);
				}
		}
		GameInfo.PlayerOneBullet.Y = 0;
		GameInfo.PlayerOneBullet.X = 0;
		GameInfo.PlayerOneBullet2.Y = 0;
		GameInfo.PlayerOneBullet2.X = 1;
		Draw(GameInfo);
	}

	if(PlayerNumber == 2){
		GameInfo.PlayerTwoBullet2.Y = GameInfo.PlayerTwoPosition.Y;
		GameInfo.PlayerTwoBullet2.X = GameInfo.PlayerTwoPosition.X - 1;
		Draw(GameInfo);
		Erase(GameInfo);
		int i;
		for(i = 0; i < 77; i++){
			GameInfo.PlayerTwoBullet.X -= 1;
			GameInfo.PlayerTwoBullet2.X -= 1;
			GameInfo.PlayerOneBullet.X += 1;
			GameInfo.PlayerOneBullet2.X += 1;
			Draw(GameInfo);
		
			int move;
			move =	Wait();
			switch(move){
			case 1:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y--;
				if(GameInfo.PlayerOnePosition.Y < 0)
					GameInfo.PlayerOnePosition.Y++;
				break;
			case 2:
				Erase(GameInfo);
				GameInfo.PlayerOnePosition.Y++;
				if(GameInfo.PlayerOnePosition.Y > 24)
					GameInfo.PlayerOnePosition.Y--;
				break;
			case 3:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y--;
				if(GameInfo.PlayerTwoPosition.Y < 0)
					GameInfo.PlayerTwoPosition.Y++;
				break;
			case 4:
				Erase(GameInfo);
				GameInfo.PlayerTwoPosition.Y++;
				if(GameInfo.PlayerTwoPosition.Y > 24)
					GameInfo.PlayerTwoPosition.Y--;
				break;
			}

			Draw(GameInfo);
			Erase(GameInfo);
			if(GameInfo.PlayerTwoBullet.X == GameInfo.PlayerOnePosition.X)
				if(GameInfo.PlayerTwoBullet.Y == GameInfo.PlayerOnePosition.Y){
					system("cls");
					cout << "\aPlayer 2 Wins" << endl;
					system("pause");
					exit(0);
			}
			if(GameInfo.PlayerTwoBullet2.X == GameInfo.PlayerOnePosition.X)
				if(GameInfo.PlayerTwoBullet2.Y == GameInfo.PlayerOnePosition.Y){
					system("cls");
					cout << "\aPlayer 2 Wins" << endl;
					system("pause");
					exit(0);
			}
		}
		GameInfo.PlayerOneBullet.Y = 10;
		GameInfo.PlayerOneBullet.X = 20;
		GameInfo.PlayerOneBullet2.Y = 10;
		GameInfo.PlayerOneBullet2.X = 11;
		Draw(GameInfo);
	}
}


int main()
{
	GAMEINFO GameInfo;
	
	

	hInput = GetStdHandle(STD_INPUT_HANDLE);
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	
	SetConsoleMode(hOutput, ENABLE_PROCESSED_INPUT);
	
	GameInfo.PlayerOnePosition.X = 192;
	GameInfo.PlayerOnePosition.Y = 142;
	GameInfo.PlayerTwoPosition.X = 261;
	GameInfo.PlayerTwoPosition.Y = 112;
	GameInfo.PlayerOneBullet.X = 02;
	GameInfo.PlayerOneBullet.Y = 10;
	GameInfo.PlayerTwoBullet.X = 729;
	GameInfo.PlayerTwoBullet.Y = 10;
	GameInfo.PlayerOneBullet2.X = 13;
	GameInfo.PlayerOneBullet2.Y = 0;
	GameInfo.PlayerTwoBullet2.X = 78;
	GameInfo.PlayerTwoBullet2.Y = 40;
	GameInfo.ZeroZero.X = 0;
	GameInfo.ZeroZero.Y = 10;

	int i;
	GameInfo.ZeroZero.Y = 24;
	for(i = 0; i < 79; i++){
		SetConsoleCursorPosition(hOutput, GameInfo.ZeroZero);
		cout << ".";
		GameInfo.ZeroZero.X++;
	}

	Draw(GameInfo);

	while(1){
		Movement(GameInfo);;
	}
	
	return 0;
}





