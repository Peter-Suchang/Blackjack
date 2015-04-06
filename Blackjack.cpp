#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std; 

int poker[52];
float sum_player, sum_com;
int cards_player, cards_com;

void shuffle();
float deal();
float player_phase();
float com_phase();
char input();

char input()
{	string input;
	cin >> input;
	while (input != "Y" && input != "y" && input != "N" && input != "n"){
		cout << "  Your input is not correct. Please check and try again.(Y/N)" << endl << "  ";
		cin >> input;
	}
	cin.sync();
	return input[0];
}

void shuffle()
{	for (int i = 0; i <= 51; ++i)
		poker[i] = i + 1;
	sum_player = 0; sum_com = 0;
	cards_player = 0; cards_com = 0;
}

float deal()
{	int card_num = 0;
	float value;

	do card_num = rand() % 52;
	while (poker[card_num] == -1);
	switch (card_num / 13){
		case 0: cout << "Spade "; break;
		case 1: cout << "Heart "; break;
		case 2: cout << "Club "; break;
		case 3: cout << "Diamond ";
	}
	switch (card_num % 13){
		case 0: cout << 'A'; value = 1; break;
		case 10: cout << 'J'; value = 0.5; break;
		case 11: cout << 'Q'; value = 0.5; break;
		case 12: cout << 'K'; value = 0.5; break;
		default: cout << poker[card_num] % 13; value = poker[card_num] % 13; 
	}
	poker[card_num] = -1;
	cout << "  ";
	return value;
}

float player_phase()
{	char choice;

	cout << "Player phase:" << endl;
	cout << "  You've got the cards: ";
	sum_player += deal();
	sum_player += deal();
	cards_player = 2;
	cout << endl;
	cout << "  The total value of your cards is: " << sum_player << endl; 
	
	cout << "  One more card?(Y/N)" << endl << "  ";
	choice = input();
	while (choice == 'Y' || choice == 'y'){
		cout << "  You've got another card: ";
		sum_player += deal();
		++cards_player;
		cout << endl;
		cout << "  The total value of your cards is: " << sum_player << endl;
		if (sum_player > 21){
			cout << "You lose..." << endl;
			return -1;
		}
		cout << "  One more card?(Y/N)" << endl << "  ";
		choice = input();
	}
	return sum_player;
}

float com_phase()
{	cout << "Computer phase:" << endl;
	cout << "  The computer has got two cards: ";
	sum_com += deal();
	sum_com += deal();
	cards_com = 2;
	cout << endl;
	cout << "  The total value of the cards of the computer is: " << sum_com << endl;
	
	while (sum_com < 21 && (sum_com <= sum_player || (sum_com == sum_player && cards_com <= cards_player))){
			cout << "  The computer has asked for one more card: ";
			sum_com += deal();
			cout << endl;
			cout << "  The total value of the cards of the computer is: " << sum_com << endl;
		}
	if (sum_com > 21){
		cout << "Congratulations! You win!" << endl;
		return -1;
	}
	return sum_player; 
}

void compare()
{	if (sum_player == sum_com && cards_player == cards_com)
		cout << "Draw." << endl;
	else{
		if (sum_player > sum_com || (sum_player == sum_com && cards_player < cards_player) )
			cout << "Congratulations! You win!" << endl;
		else
			cout << "You lose..." << endl;
	}
}

int main()
{	char judge;
	srand(time(NULL));
	cout << "Start the game?(Y/N)" << endl;
	judge = input();
	while (judge == 'Y' || judge == 'y'){
		shuffle();		
		if (player_phase() != -1){
			if (com_phase() != -1)
				void compare();
		}
		cout << "Play again?(Y/N)" << endl;
		judge = input();
	}
	return 0;
}
