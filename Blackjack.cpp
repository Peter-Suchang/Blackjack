#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std; 

int poker[52];	//Use an array to represent a pack of cards.
float sum_player, sum_com;		//the total value of all cards owned by the player and the computer
int cards_player, cards_com;	//the number of cards owned by the player and the computer

char input();			//examination on the input
void shuffle();			//initialization
float deal();			//Randomly give a card to the player or the computer.
float player_phase();
float com_phase();

char input()
{	string input;
	cin >> input;
	while (input != "Y" && input != "y" && input != "N" && input != "n"){
		cout << "  Your input is not correct. Please check and try again.(Y/N)" << endl << "  ";
		cin >> input;
	}										//Keep asking for an input until it is legal.
	cin.sync();								//Clear the buffer space of "cin" in case that more than one string is entered, which will affect the program later.
	return input[0];
}

void shuffle()
{	for (int i = 0; i <= 51; ++i)
		poker[i] = i + 1;				//Number the cards from 1 to 52.
	sum_player = 0; sum_com = 0;
	cards_player = 0; cards_com = 0;	//initialization
}

float deal()
{	int card_num = 0;
	float value;
	
	do card_num = rand() % 52;
	while (poker[card_num] == -1);		//Randomly choose a card which hasn't been given away.
	
	switch (card_num / 13){
		case 0: cout << "Spade "; break;
		case 1: cout << "Heart "; break;
		case 2: cout << "Club "; break;
		case 3: cout << "Diamond ";
	}									//Show the color of the card.
	switch (card_num % 13){
		case 0: cout << 'A'; value = 1; break;
		case 10: cout << 'J'; value = 0.5; break;
		case 11: cout << 'Q'; value = 0.5; break;
		case 12: cout << 'K'; value = 0.5; break;
		default: cout << poker[card_num] % 13; value = poker[card_num] % 13; 
	}									//Calculate the value of the card.
	poker[card_num] = -1;				//When a card is given away, change the number in the corresponding position of the array to -1, so it can be recognized.
	cout << "  ";
	return value;
}

float player_phase()
{	char choice;						//whether to ask for another card
	
	cout << "Player phase:" << endl;	
	Sleep(1500);
	cout << "  You've got the cards: ";
	sum_player += deal();
	sum_player += deal();
	cards_player = 2;
	cout << endl;
	Sleep(1000);			//Let the program pause for one second.
	cout << "  The total value of your cards is: " << sum_player << endl; 		//Give the player the first two cards.
	Sleep(1000);
	
	cout << "  One more card?(Y/N)" << endl << "  ";
	choice = input();
	while (choice == 'Y' || choice == 'y'){
		cout << "  You've got another card: ";
		sum_player += deal();
		++cards_player;
		cout << endl;
		Sleep(1000);
		cout << "  The total value of your cards is: " << sum_player << endl;	/*Show the total value of the cards each time a new card is taken,
		                                                                          so that the player can decide whether to ask for more.*/
		Sleep(1000);
		if (sum_player > 21){
			cout << "You lose..." << endl;
			return -1;							//When the total value is over 21, the player loses.
		}
		cout << "  One more card?(Y/N)" << endl << "  ";
		choice = input();
	}
	return sum_player;
}

float com_phase()
{	cout << "Computer phase:" << endl;
	Sleep(1500);
	cout << "  The computer has got two cards: ";
	sum_com += deal();
	sum_com += deal();
	cards_com = 2;
	cout << endl;
	Sleep(1000);
	cout << "  The total value of the cards of the computer is: " << sum_com << endl;	//Give the computer the first two cards.
	Sleep(1500);
	
	while (sum_com < 21 && (sum_com <= sum_player || (sum_com == sum_player && cards_com <= cards_player))){
			cout << "  The computer has asked for one more card: ";
			sum_com += deal();
			cout << endl;		
			Sleep(1000);
			cout << "  The total value of the cards of the computer is: " << sum_com << endl;
			Sleep(1500);
		}																				/*The computer keeps asking for more cards until
																							(1)the total value of the cards is 21
																						  or(2)the total value of the cards is more than that of the player
																						  or(3)the total value of the cards is equal to that of the player, but
																								the computer has got more cards.*/
	if (sum_com > 21){
		cout << "Congratulations! You win!" << endl;
		return -1;
	}													//When the total value is over 21, the player wins the game.
	return sum_com; 
}

int main()
{	char judge;
	srand(time(NULL));
	cout << "Start the game?(Y/N)" << endl;
	judge = input();
	while (judge == 'Y' || judge == 'y'){
		shuffle();		
		if (player_phase() != -1){
			if (com_phase() != -1){
				if (sum_player == sum_com && cards_player == cards_com)
					cout << "Draw." << endl;							//The same number of cards with the same value means a draw.
				else{
					if (sum_player > sum_com || (sum_player == sum_com && cards_player < cards_player) )
						cout << "Congratulations! You win!" << endl;
					else
						cout << "You lose..." << endl;
				}											/*The player wins if his or her cards have more value than those of the computer,
															  or more cards with equal value, and vice versa.*/
			}
		}
		Sleep(2000);
		cout << "Play again?(Y/N)" << endl;
		judge = input();
	}
	return 0;
}
