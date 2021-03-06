/* [BOJ] 6634
 * Complete!
 *
 */


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>
using namespace std;


void printNum(char* input) {
	char one[7][5] = {
		{' ', ' ', ' ', ' ', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '+'}
	};
	char two[7][5] = {
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', ' '},
		{'|', ' ', ' ', ' ', ' '},
		{'+', '-', '-', '-', '+'}
	};
	char three[7][5] = {
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char four[7][5] = {
		{'+', ' ', ' ', ' ', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '+'}
	};
	char five[7][5] = {
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', ' '},
		{'|', ' ', ' ', ' ', ' '},
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char six[7][5] = {
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', ' '},
		{'|', ' ', ' ', ' ', ' '},
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char seven[7][5] = {
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '+'}
	};
	char eight[7][5] = {
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char nine[7][5] = {
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'},
		{' ', ' ', ' ', ' ', '|'},
		{' ', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char zero[7][5] = {
		{'+', '-', '-', '-', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', ' ', ' ', ' ', '+'},
		{'|', ' ', ' ', ' ', '|'},
		{'|', ' ', ' ', ' ', '|'},
		{'+', '-', '-', '-', '+'}
	};
	char eq[7] = { ' ',' ','o',' ','o',' ',' ' };
	queue<int> q;
	char *token = strtok(input, ":");
	int hour = atoi(token);
	token = strtok(NULL, ":");
	int min = atoi(token);
	q.push(hour / 10);
	q.push(hour % 10);
	q.push(min / 10);
	q.push(min % 10);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			int num = q.front();
			q.pop();
			for (int k = 0; k < 5; k++) {
				switch (num)
				{
				case 1:
					cout << one[i][k];
					break;
				case 2:
					cout << two[i][k];
					break;
				case 3:
					cout << three[i][k];
					break;
				case 4:
					cout << four[i][k];
					break;
				case 5:
					cout << five[i][k];
					break;
				case 6:
					cout << six[i][k];
					break;
				case 7:
					cout << seven[i][k];
					break;
				case 8:
					cout << eight[i][k];
					break;
				case 9:
					cout << nine[i][k];
					break;
				case 0:
					cout << zero[i][k];
					break;
				}
			}
			cout << "  ";
			q.push(num);
			if (j == 1)
				cout << eq[i] << "  ";
		}
		cout << endl;
	}
}

int main() {
	queue<char*> answer;
	char *input;
	while (1) {
		input = (char*)malloc(sizeof(char));
		cin >> input;
		if (!strcmp(input, "end")) break;
		answer.push(input);
	}
	while (!answer.empty()) {
		printNum(answer.front());
		answer.pop();
		cout << endl << endl;
	}
	
	cout << "end";// << endl;
	return 0;
}