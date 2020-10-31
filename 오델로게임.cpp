#include<bangtal.h>
#include<iostream>

using namespace std;
using namespace bangtal;

ObjectPtr board[8][8];

enum class State {
	BLANK,
	POSSIBLE,
	BLACK,
	WHITE
};
State board_state[8][8];

enum class Turn {
	BLACK,
	WHITE
};
Turn turn = Turn::BLACK;

void setState(int x, int y, State state)
{
	switch (state){
	case State::BLANK:board[y][x]->setImage("images/blank.png");break;
	case State::POSSIBLE:board[y][x]->setImage(turn==Turn::BLACK ? "images/black possible.png" : "images/white possible.png");break;
	case State::BLACK:board[y][x]->setImage("images/black.png");break;
	case State::WHITE:board[y][x]->setImage("images/white.png");break;
	}
	board_state[y][x] = state;
}

int board_score[8][8] = { 0, };

bool checkPossible(int x, int y, int dx, int dy)
{
	State self = turn == Turn::BLACK ? State::BLACK : State::WHITE;
	State other = turn == Turn::BLACK ? State::WHITE : State::BLACK;

	int a = 0;
	int xx = x, yy = y;

	bool possible = false;
	for (x += dx, y += dy; x >= 0 && x < 8 && y >= 0 && y < 8; x += dx, y += dy) {
		if (board_state[y][x] == other) {
			possible = true;
			a++;
		}
		else if (board_state[y][x] == self) {
			board_score[xx][yy] += a; //어디를 누르면 몇 점을 먹을 수 있는지 쌓인다
			return possible;
		}
		else {
			return false;
		}
	}

	return false;
}

bool checkPossible(int x, int y)
{
	if (board_state[y][x] == State::BLACK) return false;
	if (board_state[y][x] == State::WHITE) return false;


	setState(x, y, State::BLANK);

	int delta[8][2] = {
		{0,1},
		{1,1},
		{1,0},
		{1,-1},
		{0,-1},
		{-1,-1},
		{-1,0},
		{-1,1},
	};

	bool possible = false;
	for (auto d:delta)
	{
		if(checkPossible(x, y, d[0], d[1])) possible=true;
	}

	return possible;
}

void reverse(int x, int y, int dx, int dy)
{
	State self = turn == Turn::BLACK ? State::BLACK : State::WHITE;
	State other = turn == Turn::BLACK ? State::WHITE : State::BLACK;

	bool possible = false;
	for (x += dx, y += dy; x >= 0 && x < 8 && y >= 0 && y < 8; x += dx, y += dy) {
		if (board_state[y][x] == other) {
			possible = true;
		}
		else if (board_state[y][x] == self) {
			if (possible) {
				for (x -= dx, y -= dy; x >= 0 && x < 8 && y >= 0 && y < 8; x -= dx, y -= dy) {
					if (board_state[y][x] == other) {
						setState(x, y, self);
					}
					else {
						return;
					}
				}
			}
		}
		else {
			return;
		}
	}

}

void reverse(int x, int y)
{
	int delta[8][2] = {
		{0,1},
		{1,1},
		{1,0},
		{1,-1},
		{0,-1},
		{-1,-1},
		{-1,0},
		{-1,1},
	};

	bool possible = false;
	for (auto d : delta)
	{
		reverse(x, y, d[0], d[1]);
	}
}

bool setPossible()
{
	bool possible = false;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board_score[j][i] = 0;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (checkPossible(x, y))
			{
				setState(x, y, State::POSSIBLE);
				possible = true;
			}
		}
	}
	return possible;
}

int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	auto scene = Scene::create("Othello", "images/background.png");

	int mm = 827, nn = 220;
	ObjectPtr num[10];
	ObjectPtr num2[7];
	num[0] = Object::create("images/L0.png", scene, mm, nn, true);
	num[1] = Object::create("images/L1.png", scene, mm, nn, true);
	num[2] = Object::create("images/L2.png", scene, mm, nn, true);
	num[3] = Object::create("images/L3.png", scene, mm, nn, true);
	num[4] = Object::create("images/L4.png", scene, mm, nn, true);
	num[5] = Object::create("images/L5.png", scene, mm, nn, true);
	num[6] = Object::create("images/L6.png", scene, mm, nn, true);
	num[7] = Object::create("images/L7.png", scene, mm, nn, true);
	num[8] = Object::create("images/L8.png", scene, mm, nn, true);
	num[9] = Object::create("images/L9.png", scene, mm, nn, true);
	mm = 752;
	num2[0] = Object::create("images/L0.png", scene, mm, nn, true);
	num2[1] = Object::create("images/L1.png", scene, mm, nn, true);
	num2[2] = Object::create("images/L2.png", scene, mm, nn, true);
	num2[3] = Object::create("images/L3.png", scene, mm, nn, true);
	num2[4] = Object::create("images/L4.png", scene, mm, nn, true);
	num2[5] = Object::create("images/L5.png", scene, mm, nn, true);
	num2[6] = Object::create("images/L6.png", scene, mm, nn, true);

	for (int i = 0; i < 10; i++)
		num[i]->hide();
	for (int i = 0; i < 7; i++)
		num2[i]->hide();

	mm = 1147;
	ObjectPtr num3[10];
	ObjectPtr num4[7];
	num3[0] = Object::create("images/L0.png", scene, mm, nn, true);
	num3[1] = Object::create("images/L1.png", scene, mm, nn, true);
	num3[2] = Object::create("images/L2.png", scene, mm, nn, true);
	num3[3] = Object::create("images/L3.png", scene, mm, nn, true);
	num3[4] = Object::create("images/L4.png", scene, mm, nn, true);
	num3[5] = Object::create("images/L5.png", scene, mm, nn, true);
	num3[6] = Object::create("images/L6.png", scene, mm, nn, true);
	num3[7] = Object::create("images/L7.png", scene, mm, nn, true);
	num3[8] = Object::create("images/L8.png", scene, mm, nn, true);
	num3[9] = Object::create("images/L9.png", scene, mm, nn, true);
	mm=1072;
	num4[0] = Object::create("images/L0.png", scene, mm, nn, true);
	num4[1] = Object::create("images/L1.png", scene, mm, nn, true);
	num4[2] = Object::create("images/L2.png", scene, mm, nn, true);
	num4[3] = Object::create("images/L3.png", scene, mm, nn, true);
	num4[4] = Object::create("images/L4.png", scene, mm, nn, true);
	num4[5] = Object::create("images/L5.png", scene, mm, nn, true);
	num4[6] = Object::create("images/L6.png", scene, mm, nn, true);

	for (int i = 0; i < 10; i++)
		num3[i]->hide();
	for (int i = 0; i < 7; i++)
		num4[i]->hide();

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = Object::create("images/blank.png", scene, 40 + x * 80, 40 + y * 80);


			board[y][x]->setOnMouseCallback([&, x, y](ObjectPtr object, int, int, MouseAction)->bool {
				if(board_state[y][x]==State::POSSIBLE)
				{
					if (turn == Turn::BLACK)
					{
						setState(x, y, State::BLACK);
						reverse(x, y);
						turn = Turn::WHITE;
					}

					if (!setPossible())
					{
						turn = turn == Turn::BLACK ? Turn::WHITE : Turn::BLACK;

						if (!setPossible())
						{
							showMessage("END GAME!!");
						}
					}
				}

				if (turn == Turn::WHITE)
				{
					int maxx = 0, maxy = 0, max = 0;

					for (int i = 0; i < 8; i++) //어디가 제일 많은 점수를 먹을 수 있는가
						for (int j = 0; j < 8; j++)
						{
							if (board_score[j][i] != 0 && board_score[j][i] >= max)
							{
								max = board_score[j][i];
								maxy = i;
								maxx = j;
							}
						}

					setState(maxx, maxy, State::WHITE);
					reverse(maxx, maxy);

					for (int i = 0; i < 8; i++)
						for (int j = 0; j < 8; j++)
							board_score[j][i] = 0;

					turn = Turn::BLACK;
				}

				if (!setPossible())
				{
					turn = turn == Turn::BLACK ? Turn::WHITE : Turn::BLACK;

					if (!setPossible())
					{
						showMessage("END GAME!!");
					}
				}

				int b = 0, w = 0;

				for(int i=0;i<8;i++)
					for (int j = 0; j < 8; j++)
					{
						if (board_state[j][i] == State::BLACK)
							b++;
						else if (board_state[j][i] == State::WHITE)
							w++;
				}

				for (int i = 0; i < 10; i++)
				{
					num[i]->hide();
					num3[i]->hide();
				}
				for (int i = 0; i < 7; i++)
				{
					num2[i]->hide();
					num4[i]->hide();
				}

				num[b % 10]->show();
				num2[b / 10]->show();
				num3[w % 10]->show();
				num4[w / 10]->show();

				return true;
				});
			board_state[y][x] = State::BLANK;
		}
	}

	setState(3, 3, State::BLACK);
	setState(4, 4, State::BLACK);
	setState(3, 4, State::WHITE);
	setState(4, 3, State::WHITE);
	num[2 % 10]->show();
	num2[2 / 10]->show();
	num3[2 % 10]->show();
	num4[2 / 10]->show();

	setPossible();

	startGame(scene);
}