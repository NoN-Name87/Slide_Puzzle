#pragma warning(disable:4996)

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <algorithm> 
#include <iomanip>
#include <Windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct Res_Table
{
	int keystroke=0;
	int Saved_time = 0;
};


void Save_Game(Res_Table Tab, vector<vector<int>>& sliding_board, int num_rows, int num_colums, int start);
void Download(Res_Table Tab, int num_rows, int num_colums);
bool Flag_val(int Right_arr, vector<vector<int>>& sliding_board, int num_rows, int num_colums);
void Initialize_Board(vector<vector<int>>& Right_arr, vector<vector<int>>& sliding_board, int num_rows, int num_colums);
void Print_Board(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums);
int slide_title(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums, Res_Table Tab);
void Init_arr(vector<vector<int>>& Right_arr, int num_rows, int num_colums);
bool board_solved(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums, Res_Table Tab, int start);
void Right_solve(vector<vector<int>>& Right_arr, vector<vector<int>>& sliding_board, int num_rows, int num_colums);
int Menu(Res_Table Tab);

int main()
{
	srand(time(NULL));
	Res_Table tab;
	Menu(tab);
	return 0;
}

int Menu(Res_Table Tab)
{
	Tab.keystroke = 0;
	Tab.Saved_time = 0;
	int option = 0;
	int num_rows = 0, num_colums = 0;
	cout << "Choose one of the option:1-3x3 board,2-4x4,3-exit,4-load save" << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		num_rows = num_colums = 3;
		break;
	case 2:
		num_rows = num_colums = 4;
		break;
	case 3:
		return 0;
		break;
	case 4:
		Download(Tab, num_rows, num_colums);
		return Menu(Tab);
		break;
	default:
		cout << "Error" << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}
		return Menu(Tab);
	}
	vector<vector<int>> sliding_board(num_colums, vector<int>(num_colums));
	vector<vector<int>> Right_arr(num_colums, vector<int>(num_colums));

	Init_arr(Right_arr, num_rows, num_colums);
	Right_solve(Right_arr, sliding_board, num_rows, num_colums);
	Initialize_Board(Right_arr, sliding_board, num_rows, num_colums);
	Print_Board(sliding_board, Right_arr, num_rows, num_colums);
	slide_title(sliding_board, Right_arr, num_rows, num_colums,Tab);
	return 0;
}


void Init_arr(vector<vector<int>>& Right_arr, int num_rows, int num_colums)
{
	for (int i = 0; i < (num_rows*num_colums)-1; i++)
	{
			Right_arr[i/num_rows][i%num_colums] = i + 1;
	}
	Right_arr[num_rows - 1][num_colums - 1] = 42;
}

void Right_solve(vector<vector<int>>& Right_arr, vector<vector<int>>& sliding_board, int num_rows, int num_colums)
{
	cout << "It's right solve.Press any key and enter to continue" << endl;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_colums; j++)
		{
			if (Right_arr[i][j] != 42)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << setw(2.3) << Right_arr[i][j] << " ";
			}
			if (Right_arr[i][j] == '*')
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				cout << setw(2.3) << static_cast<char>(Right_arr[i][j]) << " ";
			}
		}
		cout << endl;
	}
	getch();
}

void Initialize_Board(vector<vector<int>>& Right_arr, vector<vector<int>>& sliding_board, int num_rows, int num_colums)
{
	int i = 0;
	int random_value;
	for (i; i < num_rows*num_colums; i++)
	{
		do
		{
			random_value = 0 + rand() % (num_rows * num_colums);
		} while (Flag_val(Right_arr[random_value / num_rows][random_value % num_colums], sliding_board, num_rows, num_colums) == false);
		sliding_board[i / num_rows][i % num_colums]= Right_arr[random_value / num_rows][random_value % num_colums];
	}
}

bool Flag_val(int Right_val, vector<vector<int>>& sliding_board, int num_rows, int num_colums)
{
	for (int i = 0; i < num_rows * num_colums; i++)
	{
		if (sliding_board[i / num_rows][i % num_colums] == Right_val)
		{
			return false;
		}
	}
	return true;
}

void Print_Board(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums)
{
	system("cls");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_colums; j++)
		{
			if (sliding_board[i][j] == '*')
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				cout << setw(2.3) << static_cast<char>(sliding_board[i][j]) << " ";
			}
			if (sliding_board[i][j] != Right_arr[i][j] && sliding_board[i][j] != '*')
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				cout << setw(2.3) << sliding_board[i][j] << " ";
			}
			else if (sliding_board[i][j] == Right_arr[i][j] && sliding_board[i][j] != '*')
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << setw(2.3) << sliding_board[i][j] << " ";
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Please,enter follow buttons:w-->UP a-->LEFT s-->DOWN d-->RIGHT" << " " << endl;
	cout << "Press 1 if you want to save and exit the Menu" << endl;
}

int slide_title(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums, Res_Table Tab)
{
	int start = clock();
	while (board_solved(sliding_board, Right_arr, num_rows, num_colums,Tab,start) == false)
	{
		if (kbhit())
		{
			system("cls");
			int button;
			button = getch();//key interception
		   if (button == 119)
			{
			   Tab.keystroke++;
				for (int i = 1; i < num_rows; i++)
				{
					for (int j = 0; j < num_colums; j++)
					{
						if (sliding_board[i][j] == '*')
						{
							system("cls");
							swap(sliding_board[i - 1][j], sliding_board[i][j]);
							break;
						}
					}
				}
			}

			else if (button == 97)
			{
			   Tab.keystroke++;
				for (int i = 0; i < num_rows; i++)
				{
					for (int j = 1; j < num_colums; j++)
					{
						if (sliding_board[i][j] == '*')
						{
							system("cls");
							swap(sliding_board[i][j-1], sliding_board[i][j]);
							break;
						}
					}
				}
			}

			else if (button == 115)
			{
			   Tab.keystroke++;
			   int count = 0;
				for (int i = 0; i < num_rows-1; i++)
				{
					for (int j = 0; j < num_colums; j++)
					{
						if (sliding_board[i][j] == '*'&&count!=1)
						{
							system("cls");
							swap(sliding_board[i][j], sliding_board[i + 1][j]);
							count++;
							break;
						}
					}
				}
			}

			else if (button == 100)
			{
			   Tab.keystroke++;
				for (int i = 0; i < num_rows; i++)
				{
					for (int j = 0; j < num_colums-1; j++)
					{
						if (sliding_board[i][j] == '*')
						{
							system("cls");
							swap(sliding_board[i][j+1], sliding_board[i][j]);
							break;
						}
					}
				}
			}
		   else if (button == 49)
		   {
			   Save_Game(Tab, sliding_board, num_rows, num_colums, start);
			   break;
		   }
			Print_Board(sliding_board, Right_arr, num_rows, num_colums);
			cout << "Keystroke:" << Tab.keystroke << endl;
		}
	}
    return Menu(Tab);
}

void Save_Game(Res_Table Tab, vector<vector<int>>& sliding_board, int num_rows, int num_colums, int start)
{
	int stop = clock();
	string name_file;
	cout << "Name the save file:";
	cin >> name_file;
	ofstream file(name_file);
	file << "Size: " << num_colums << endl;
	file << "Keystroke: " << Tab.keystroke << endl;
	file << "Time: " << (stop - start) / CLK_TCK << endl;
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_colums; j++)
		{
			file << sliding_board[i][j] << " ";
		}
	}
	sliding_board.clear();
	file.close();
}

void Download(Res_Table Tab, int num_rows, int num_colums)
{
	string name_file;
	cout << "Enter file name:";
	cin >> name_file;
	ifstream file;
	file.open(name_file);
	if (file.is_open())
	{
		file >> name_file >> num_rows;
		file >> name_file >> Tab.keystroke;
		file >> name_file >> Tab.Saved_time;
		num_colums = num_rows;
		vector<vector<int>> sliding_board(num_colums, vector<int>(num_colums));
		vector<vector<int>> Right_arr(num_colums, vector<int>(num_colums));
		for (int i = 0; i < num_rows; i++)
		{
			for (int j = 0; j < num_colums; j++)
			{
				file >> sliding_board[i][j];
			}
		}
		file.close();
		Init_arr(Right_arr, num_rows, num_colums);
		Print_Board(sliding_board, Right_arr, num_rows, num_colums);
		slide_title(sliding_board, Right_arr, num_rows, num_colums, Tab);
	}
	else
	{
		cout << "File not found" << endl;
		Download(Tab, num_rows, num_colums);
	}
}

bool board_solved(vector<vector<int>>& sliding_board, vector<vector<int>>& Right_arr, int num_rows, int num_colums, Res_Table Tab, int start)
{
	bool flag;
	int stop = 0;
	int counter = 0;
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_colums; j++)
		{
			counter++;
			if (sliding_board[i][j] == Right_arr[i][j] && counter == num_colums*num_colums)
			{
				flag = true;
				stop = clock();
				cout << "True!" << endl;
				cout << "Total keystroke:" << Tab.keystroke << endl;
				cout << "Total seconds:" << Tab.Saved_time + (stop - start) / CLK_TCK << endl;
				break;
			}
			else if (sliding_board[i][j] != Right_arr[i][j])
			{
				flag = false;
				break;
			}
		}
	}
	return flag;
}

