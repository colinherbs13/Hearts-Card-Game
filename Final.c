#define _CRT_SECURE_NO_WARNINGS
#define SPADE	"\x06"
#define HEART	"\x03"
#define CLUB	"\x05"
#define DIAMOND	"\x04"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Made by Colin Herbert & Prasanna Raut, Updated 11/26/19

/*Skeleton Functions

void turnWinner(card user, card comp1, card comp2); //returns 1 2 or 3 depending on who placed the highest card considering suit
*/

typedef struct card_s {
	char suit[2];
	int face;
	struct card_s* listp;
} card;

void PrintDeck(card* HN) {
	card* temp;
	temp = HN;
	int z = 1;
	while (temp != NULL) {

		if (temp->face == 1) {
			printf("A");
		}
		else if (temp->face == 11) {
			printf("J");
		}
		else if (temp->face == 12) {
			printf("Q");
		}
		else if (temp->face == 13) {
			printf("K");
		}
		else {
			printf("%d", temp->face);
		}
		if (strcmp(temp->suit, HEART) == 0) {
			printf("%s\t", HEART);
		}
		if (strcmp(temp->suit, DIAMOND) == 0) {
			printf("%s\t", DIAMOND);
		}
		if (strcmp(temp->suit, CLUB) == 0) {
			printf("%s\t", CLUB);
		}
		if (strcmp(temp->suit, SPADE) == 0) {
			printf("%s\t", SPADE);
		}
		if (z % 13 == 0) {
			printf("\n");
		}
		temp = temp->listp;
		z++;
	}
}

void Shuffle(card* HN, card* TN, int numCards)
{
	srand((int)time(0));
	card* card1;
	card* card2;
	card* burner;
	int i = 0;
	while (i < 500) {
		int num1, num2;
		num1 = rand() % numCards;
		num2 = rand() % numCards;
		card1 = HN;
		card2 = HN;
		burner = TN;
		for (int j = 0; j < num1; j++) {
			card1 = card1->listp;
		}
		for (int j = 0; j < num2; j++) {
			card2 = card2->listp;
		}
		burner->face = card1->face;
		strcpy(burner->suit, card1->suit);
		card1->face = card2->face;
		strcpy(card1->suit, card2->suit);
		card2->face = burner->face;
		strcpy(card2->suit, burner->suit);
		i++;
	}
}

void getTail(card** head, card** Tail)
{
	card* anothatemp;
	anothatemp = *head;
	while (anothatemp->listp != NULL)
	{

		if (anothatemp->listp == NULL)
		{
			*Tail = anothatemp;
		}
		anothatemp = anothatemp->listp;
	}
	*Tail = anothatemp;


}

void addCard(card** HN, card** TN, int TFace, char Tsuit[2])//adds card to a hand
{
	card* added = (card*)(malloc(sizeof(card)));
	strcpy(added->suit, Tsuit);
	added->face = TFace;
	added->listp = NULL;
	card* temp = *HN;
	card* NewDeck;


	if (*HN == NULL)
	{
		*HN = temp;
	}
	else
	{
		(*TN)->listp = added;
		(*TN) = (*TN)->listp;
	}


}

void removeCard(card** HN, card** TN, int Tface, char Tsuit[2])
{
	card* targetp = *HN; //pointer to the node to be deleted
	card* prev = *HN; // pointer to the head list


	while ((strcmp(targetp->suit, Tsuit) != 0) || (targetp->face != Tface))//a while loop that continues as long as the target is not identified
	{
		targetp = targetp->listp;
	}
	if (targetp == NULL)
	{
		return;
	}
	else
	{
		if (targetp == *HN) //if first node is to be deleted
		{
			*HN = targetp->listp;
		}
		else
		{
			while (prev->listp != targetp)
			{
				prev = prev->listp;
			}
			if (targetp == *TN)
			{
				*TN = prev; //updated tail
				(*TN)->listp = NULL;
			}
			else
			{
				prev->listp = targetp->listp;
			}
			free(targetp);
		}
	}


}

void Deal(card** HN, card** Hand1, card** Hand2, card** Hand3) {
	int i;
	card* temp = *HN, * temp1 = NULL, * temp2 = NULL, * temp3 = NULL;
	for (i = 1; i <= 51; i++, temp = temp->listp) {
		if ((i % 3) == 0) {
			if (temp3 == NULL) { //if the third hand is empty, set pointer to the current card being pointed to
				*Hand3 = temp;
			}
			else { //otherwise, set the next node to the current card
				temp3->listp = temp;
			}
			temp3 = temp; //sets the temp list to the headnode pointer
		}
		else if (((i + 1) % 3) == 0) {
			if (temp2 == NULL) { //if second hand is empty, set pointer to current card being pointed to
				*Hand2 = temp;
			}
			else {
				temp2->listp = temp;
			}
			temp2 = temp;
		}
		else {
			if (temp1 == NULL) { //if first hand is empty, set pointer to current card being pointed to.
				*Hand1 = temp;
			}
			else {
				temp1->listp = temp;
			}
			temp1 = temp;
		}
	}
	temp1->listp = temp2->listp = temp3->listp = NULL; //sets last nodes to NULL in each hand
	*HN = temp; //updates head node with current deck
}

int FirstPlayer(card** Player)//returns 1 if the player had a 2 of clubs
{
	card* targetp;
	targetp = *Player; //target equal to the player pointer

	for (int i = 0; i < 17; i++)//a for loop to loop through all 17 cards in the hand
	{
		if ((targetp->face == 2) && (strcmp(targetp->suit, CLUB) == 0))//if the hand has the 2 of clubs, returns 1
		{
			return 1;
		}
		else
		{

			targetp = targetp->listp;//goes to next card in the list

		}

	}
	return 0;//returns 0 is the 2 of clubs is not found
}

int GetNumCards(card* Hand) { //counts number of cards in a hand
	int count = 0;
	while (Hand != NULL) { //for each node, count incresaes by one
		count++;
		Hand = Hand->listp;
	}
	return(count);
}

void PrintHand(char PlayerName[20], card* H1) { //Print's the hand holder's name, number of cards in the hand, and the cards in the hand using the printDeck function
	printf("%s's hand has %d cards", PlayerName, GetNumCards(H1));
	printf("\n");
	PrintDeck(H1);
}

void PrintCard(card* choice) {
	if (choice->face == 1) {
		printf("A%s\n", choice->suit);
	}
	else if (choice->face == 11) {
		printf("J%s\n", choice->suit);
	}
	else if (choice->face == 12) {
		printf("Q%s\n", choice->suit);
	}
	else if (choice->face == 13) {
		printf("K%s\n", choice->suit);
	}
	else {
		printf("%d%s\n", choice->face, choice->suit);
	}
}

void giveCards(card** player1, card** T1, card** player2, card** T2, card** player3, card** T3) {//prompts the user to give away 3 cards. the computers will give away random cards or the first 3 cards. ordered in terms of winner first
	int inp1 = 0, inp2 = 0, inp3 = 0, i;
	card *card1 = (card*)malloc(sizeof(card)), *card2 = (card*)malloc(sizeof(card)), *card3 = (card*)malloc(sizeof(card)), *hand1 = *player1, *hand2 = *player2, *hand3 = *player3;
	srand((int)time(0));
	while ((inp1 == inp2) || (inp1 == inp3) || (inp2 == inp3) || (inp1 < 1 || inp1 > 17) || (inp2 < 1 || inp2 > 17) || (inp3 < 1 || inp3 > 17)) { //stays in a loop until the user's inputs meet the correct parameters (within the range of cards in the hand and all cards chosen being different).
		printf("\nChoose 3 cards to give away\n");
		printf("Enter card number between 1-17 where 1 is the leftmost card: "); //prompts the user to pick three cards
		scanf("%d %d %d", &inp1, &inp2, &inp3);
		if ((inp1 == inp2) || (inp1 == inp3) || (inp2 == inp3)) {
			printf("\nAll 3 numbers must be different\n");
		}
		if ((inp1 < 1) || (inp2 < 1) || (inp3 < 1)) {
			printf("\nCard number must be greater than 0\n");
		}
		else if ((inp1 > 17) || (inp2 > 17) || (inp3 > 17)) {
			printf("\nCard number must be less than 18\n");
		}
	}
	for (i = 0; i < inp1 - 1; i++) { //locates the first card to be removed
		hand1 = hand1->listp;
	}
	strcpy(card1->suit, hand1->suit); //sets the first card to a temp node to be removed from the hand and added to the next
	card1->face = hand1->face;
	hand1 = *player1; //sets the hand pointer back to the head pointer to locate the second card
	for (i = 0; i < inp2 - 1; i++) { //locates the second card to be removed
		hand1 = hand1->listp;
	}
	strcpy(card2->suit, hand1->suit); //sets the data for the second card to a temp node to be removed from the hand and added to the next
	card2->face = hand1->face;
	hand1 = *player1; //resets the hand pointer back to the head pointer
	for (i = 0; i < inp3 - 1; i++) { //locates the third card to be removed
		hand1 = hand1->listp;
	}
	strcpy(card3->suit, hand1->suit); //sets the data for the third card to a third temp node
	card3->face = hand1->face;
	hand1 = *player1; //resets the hand node to the head
	removeCard(&*player1, &*T1, card1->face, card1->suit); //calls the remove and add functions, using the temp nodes as references
	removeCard(&*player1, &*T1, card2->face, card2->suit);
	removeCard(&*player1, &*T1, card3->face, card3->suit);
	addCard(&*player2, &*T2, card1->face, card1->suit);
	addCard(&*player2, &*T2, card2->face, card2->suit);
	addCard(&*player2, &*T2, card3->face, card3->suit);
	for (i = 0; i < rand() % 17; i++) { //generates a random number for the computers, then locates the first card of the second hand to be removed
		hand2 = hand2->listp;
	}
	strcpy(card1->suit, hand2->suit); //sets the data from the first card of the second hand to a temp node
	card1->face = hand2->face;
	hand2 = *player2; //resets the hand pointer to the head to recount
	for (i = 0; i < rand() % 17; i++) { //generates another random number for the computer to pick, then locates the card
		hand2 = hand2->listp;
	}
	while ((hand2->face == card1->face) && (strcmp(hand2->suit, card1->suit) == 0)) { //while loops restart the process if the random number is a repeat of a previous random card pulled
		hand2 = *player2;
		for (i = 0; i < rand() % 17; i++) {
			hand2 = hand2->listp;
		}
	}
	strcpy(card2->suit, hand2->suit); //sets data to temp node
	card2->face = hand2->face;
	hand2 = *player2; //resets pointer to head node
	for (i = 0; i < rand() % 17; i++) { //locates the third card randomly
		hand2 = hand2->listp;
	}
	while ((hand2->face == card1->face) && (strcmp(hand2->suit, card1->suit) == 0) || (hand2->face == card2->face) && (strcmp(hand2->suit, card2->suit) == 0)) { //finds a different card if the previous card pulled is a repeat
		hand2 = *player2;
		for (i = 0; i < rand() % 17; i++) {
			hand2 = hand2->listp;
		}
	}
	strcpy(card3->suit, hand2->suit); //sets data to temp node
	card3->face = hand2->face;
	hand2 = *player2; //resets pointer to head node
	removeCard(&*player2, &*T2, card1->face, card1->suit); //calls remove functions and add functions to the third hand
	removeCard(&*player2, &*T2, card2->face, card2->suit);
	removeCard(&*player2, &*T2, card3->face, card3->suit);
	addCard(&*player3, &*T3, card1->face, card1->suit);
	addCard(&*player3, &*T3, card2->face, card2->suit);
	addCard(&*player3, &*T3, card3->face, card3->suit);
	for (i = 0; i < rand() % 17; i++) { //repeats first computer's process for second computer
		hand3 = hand3->listp;
	}
	strcpy(card1->suit, hand3->suit);
	card1->face = hand3->face;
	hand3 = *player3;
	for (i = 0; i < rand() % 17; i++) {
		hand3 = hand3->listp;
	}
	while ((hand3->face == card1->face) && (strcmp(hand3->suit, card1->suit) == 0)) {
		hand3 = *player3;
		for (i = 0; i < rand() % 17; i++) {
			hand3 = hand3->listp;
		}
	}
	strcpy(card2->suit, hand3->suit);
	card2->face = hand3->face;
	hand3 = *player3;
	for (i = 0; i < rand() % 17; i++) {
		hand3 = hand3->listp;
	}
	while ((hand3->face == card1->face) && (strcmp(hand3->suit, card1->suit) == 0) || (hand3->face == card2->face) && (strcmp(hand3->suit, card2->suit) == 0)) {
		hand3 = *player3;
		for (i = 0; i < rand() % 17; i++) {
			hand3 = hand3->listp;
		}
	}
	strcpy(card3->suit, hand3->suit);
	card3->face = hand3->face;
	hand3 = *player3;
	removeCard(&*player3, &*T3, card1->face, card1->suit);
	removeCard(&*player3, &*T3, card2->face, card2->suit);
	removeCard(&*player3, &*T3, card3->face, card3->suit);
	addCard(&*player1, &*T1, card1->face, card1->suit);
	addCard(&*player1, &*T1, card2->face, card2->suit);
	addCard(&*player1, &*T1, card3->face, card3->suit);
}

void turnWinner(card* player, card* comp1, card* comp2, int TurnLead, int* playerPoints, int* comp1Points, int* comp2Points, int* TurnWin) {
	if (TurnLead == 1) { //if the person who led the turn was the user...
		if ((comp1->face > player->face) && (strcmp(comp1->suit, player->suit) == 0)) { //if the first computer's suit is the same as the lead card's suit and the face is greater than the lead card
			if ((comp1->face < comp2->face) && (strcmp(comp2->suit, comp1->suit) == 0)) { //tests if the second computer's suit is the same as the first computer's suit and if it's face value is greater
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*comp2Points = *comp2Points + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*comp2Points = *comp2Points + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*comp2Points = *comp2Points + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*comp2Points = *comp2Points + 1;
				}
				*TurnWin = 3;
			}
			else {
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*comp1Points = *comp1Points + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*comp1Points = *comp1Points + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*comp1Points = *comp1Points + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*comp1Points = *comp1Points + 1;
				}
				*TurnWin = 2;
			}
		}
		else {
			if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
				*playerPoints = *playerPoints + 13;
			}
			if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
				*playerPoints = *playerPoints + 1;
			}
			if ((strcmp(comp1->suit, HEART) == 0)) {
				*playerPoints = *playerPoints + 1;
			}
			if ((strcmp(player->suit, HEART) == 0)) {
				*playerPoints = *playerPoints + 1;
			}
			*TurnWin = 1;
		}
	}
	else if (TurnLead == 2) {
		if ((player->face > comp1->face) && (strcmp(player->suit, comp1->suit) == 0)) { //if the user's suit is the same as the lead card's suit and the face is greater than the lead card
			if ((player->face < comp2->face) && (strcmp(comp2->suit, player->suit) == 0)) { //tests if the second computer's suit is the same as the user's suit and if it's face value is greater
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*comp2Points = *comp2Points + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*comp2Points = *comp2Points + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*comp2Points = *comp2Points + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*comp2Points = *comp2Points + 1;
				}
				*TurnWin = 3;
			}
			else {
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*playerPoints = *playerPoints + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*playerPoints = *playerPoints + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*playerPoints = *playerPoints + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*playerPoints = *playerPoints + 1;
				}
				*TurnWin = 1;
			}
		}
		else {
			if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
				*comp1Points = *comp1Points + 13;
			}
			if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
				*comp1Points = *comp1Points + 1;
			}
			if ((strcmp(comp1->suit, HEART) == 0)) {
				*comp1Points = *comp1Points + 1;
			}
			if ((strcmp(player->suit, HEART) == 0)) {
				*comp1Points = *comp1Points + 1;
			}
			*TurnWin = 2;
		}
	}
	else if (TurnLead == 3) {
		if ((player->face > comp2->face) && (strcmp(player->suit, comp2->suit) == 0)) { //if the user's suit is the same as the lead card's suit and the face is greater than the lead card
			if ((player->face < comp1->face) && (strcmp(comp1->suit, player->suit) == 0)) { //tests if the first computer's suit is the same as the user's suit and if it's face value is greater
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*comp1Points = *comp1Points + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*comp1Points = *comp1Points + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*comp1Points = *comp1Points + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*comp1Points = *comp1Points + 1;
				}
				*TurnWin = 2;
			}
			else {
				if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
					*playerPoints = *playerPoints + 13;
				}
				if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
					*playerPoints = *playerPoints + 1;
				}
				if ((strcmp(comp1->suit, HEART) == 0)) {
					*playerPoints = *playerPoints + 1;
				}
				if ((strcmp(player->suit, HEART) == 0)) {
					*playerPoints = *playerPoints + 1;
				}
				*TurnWin = 1;
			}
		}
		else {
			if (((strcmp(comp2->suit, SPADE) == 0) && (comp2->face == 12)) || (strcmp(comp1->suit, SPADE) == 0) && (comp1->face == 12) || (strcmp(player->suit, SPADE) == 0) && (player->face == 12)) { //tests if there is a queen of spades that has been played, and adds 13 points to the winner's point total.
				*comp2Points = *comp2Points + 13;
			}
			if ((strcmp(comp2->suit, HEART) == 0)) { //adds a point to the total if any card played is a heart
				*comp2Points = *comp2Points + 1;
			}
			if ((strcmp(comp1->suit, HEART) == 0)) {
				*comp2Points = *comp2Points + 1;
			}
			if ((strcmp(player->suit, HEART) == 0)) {
				*comp2Points = *comp2Points + 1;
			}
			*TurnWin = 3;
		}
	}
}

void turn(card** user, card** userTail, card** comp1, card** comp1Tail, card** comp2, card** comp2Tail, char userName[20], card** Tail, card** discard, card** discardTail) {//prints out the turn number and prompts the user to place a cards
	//intitalizing every single value
	srand((int)time(0));
	int turnNum = 1, userPoints = 0, comp1Points = 0, comp2Points = 0; int cardNum = 0, comp1cardNum = 0, comp2cardNum = 0;
	card* temp1 = *user, * temp2 = *comp1, * temp3 = *comp2, * userTemp2 = *user, * comp1Temp2 = *comp1, * comp2Temp2 = *comp2;
	card* playerChoice = (card*)malloc(sizeof(card)), * comp1Choice = (card*)malloc(sizeof(card)), * comp2Choice = (card*)malloc(sizeof(card));
	card* lastPlayed = (card*)malloc(sizeof(card));
	int turnLead = 0;
	int numCardsUser = GetNumCards(temp1);
	int comp1NumCards = GetNumCards(temp2);
	int comp2NumCards = GetNumCards(temp3);
	int TurnWin = 0;
	while (numCardsUser > 0){
		cardNum = 0;
		//get the number of cards in each hand
		numCardsUser = GetNumCards(*user);
		comp1NumCards = GetNumCards(*comp1);
		comp2NumCards = GetNumCards(*comp2);
		if (numCardsUser == 0) {
			break;
		}
		//resets the second temps to equal the original temps with the card removed
		temp1 = *user;
		temp2 = *comp1;
		temp3 = *comp2;
		//creates a random number based on the number of cards in the computers hands
		comp1cardNum = rand() % comp1NumCards;
		comp2cardNum = rand() % comp2NumCards;
		if (turnNum == 1) { 
			printf("\n");
			if (FirstPlayer(user) == 1) {
				turnLead = 1;
				printf("\n***Turn %d***\n%s will lead with 2%s\n", turnNum, userName, CLUB);
				playerChoice->face = 2;
				strcpy(playerChoice->suit, CLUB);
				playerChoice->listp = NULL;
				//comp1 turn
				for (int i = 0; i < comp1cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp2 = temp2->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp1Choice->suit, temp2->suit);
				comp1Choice->face = temp2->face;
				temp2 = comp1Temp2;

				//comp2 turn
				for (int i = 0; i < comp2cardNum - 1; i++) {//finds the card based on the random number generated for comp2
					temp3 = temp3->listp;
				}
				//copies the suit and face of the random card
				strcpy(comp2Choice->suit, temp3->suit);
				comp2Choice->face = temp3->face;
				temp3 = comp2Temp2;
				printf("Computer 1's card is ");
				PrintCard(comp1Choice);
				printf("Computer 2's card is ");
				PrintCard(comp2Choice);
			}
			else if (FirstPlayer(comp1) == 1) {
				turnLead = 2;
				printf("\n***Turn %d***\nComputer 1 will lead with 2%s\n", turnNum, CLUB);
				comp1Choice->face = 2;
				strcpy(comp1Choice->suit, CLUB);
				comp1Choice->listp = NULL;
				for (int i = 0; i < comp2cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp3 = temp3->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp2Choice->suit, temp3->suit);
				comp2Choice->face = temp3->face;
				temp3 = comp2Temp2;

				printf("Computer 2's card is ");
				PrintCard(comp2Choice);
				while ((cardNum > numCardsUser) || (cardNum < 1)) {
					printf("Choose a card to play\n");
					PrintHand(userName, temp1);
					printf("\nEnter card number between 1-%d where 1 is the leftmost card: ", numCardsUser);
					scanf("%d", &cardNum);
				}
				for (int i = 0; i < cardNum - 1; i++) {
					temp1 = temp1->listp;
				}
				strcpy(playerChoice->suit, temp1->suit);
				playerChoice->face = temp1->face;
				temp1 = userTemp2;
				printf("%s's card is ", userName);
				PrintCard(playerChoice);
			}
			else if (FirstPlayer(comp2) == 1) {
				turnLead = 3;
				printf("\n***Turn %d***\nComputer 2 will lead with 2%s\n", turnNum, CLUB);
				comp2Choice->face = 2;
				strcpy(comp2Choice->suit, CLUB);
				comp2Choice->listp = NULL;
				for (int i = 0; i < comp1cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp2 = temp2->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp1Choice->suit, temp2->suit);
				comp1Choice->face = temp2->face;
				temp2 = comp1Temp2;
				while ((cardNum > numCardsUser) || (cardNum < 1)) {
					printf("Choose a card to play\n");
					PrintHand(userName, temp1);
					printf("\nEnter card number between 1-%d where 1 is the leftmost card: ", numCardsUser);
					scanf("%d", &cardNum);
				}
				for (int i = 0; i < cardNum - 1; i++) {//goes through a loop to find chosen card
					temp1 = temp1->listp;
				}
				//copies face and suit of card
				strcpy(playerChoice->suit, temp1->suit);
				playerChoice->face = temp1->face;
				temp1 = userTemp2;
				printf("%s's card is ", userName);
				PrintCard(playerChoice);
				printf("Computer 1's card is ");
				PrintCard(comp1Choice);
				
			}
		}
		else
		{
			if (TurnWin == 1)
			{
				turnLead = 1;
				printf("\n***Turn %d***\n%s will Lead", turnNum, userName);
				while ((cardNum > numCardsUser) || (cardNum < 1)) {
					printf("\nChoose a card to play\n");
					PrintHand(userName, temp1);
					printf("\nEnter card number between 1-%d where 1 is the leftmost card: ", numCardsUser);
					scanf("%d", &cardNum);
				}
				for (int i = 0; i < cardNum - 1; i++) {//goes through a loop to find the chose card
					temp1 = temp1->listp;
				}
				//copies face and suit of card
				strcpy(playerChoice->suit, temp1->suit);
				playerChoice->face = temp1->face;
				temp1 = userTemp2;
				printf("%s's card is ", userName);
				PrintCard(playerChoice);
				//comp1 turn
				for (int i = 0; i < comp1cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp2 = temp2->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp1Choice->suit, temp2->suit);
				comp1Choice->face = temp2->face;
				temp2 = comp1Temp2;
				//comp 2 turn
				for (int i = 0; i < comp2cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp3 = temp3->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp2Choice->suit, temp3->suit);
				comp2Choice->face = temp3->face;
				temp3 = comp2Temp2;
				printf("Computer 1's card is ");
				PrintCard(comp1Choice);
				printf("Computer 2's card is ");
				PrintCard(comp2Choice);
			}
			else if (TurnWin == 2)// if comp1 was the winner of the last round
			{
				turnLead = 2;
				//computer 1 turn
				printf("\n***Turn %d***\nComputer 1 will lead \n", turnNum);
				for (int i = 0; i < comp1cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp2 = temp2->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp1Choice->suit, temp2->suit);
				comp1Choice->face = temp2->face;
				temp2 = comp1Temp2;
				printf("Computer 1's card is ");
				PrintCard(comp1Choice);
				//computer 2 turn
				for (int i = 0; i < comp2cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp3 = temp3->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp2Choice->suit, temp3->suit);
				comp2Choice->face = temp3->face;
				temp3 = comp2Temp2;
				printf("Computer 2's card is ");
				PrintCard(comp2Choice);
				//player turn
				while ((cardNum > numCardsUser) || (cardNum < 1)) {
					printf("Choose a card to play\n");
					PrintHand(userName, temp1);
					printf("\nEnter card number between 1-%d where 1 is the leftmost card: ", numCardsUser);
					scanf("%d", &cardNum);
				}
				for (int i = 0; i < cardNum - 1; i++) {//goes through a loop to find the chose card
					temp1 = temp1->listp;
				}
				//copies face and suit of card
				strcpy(playerChoice->suit, temp1->suit);
				playerChoice->face = temp1->face;
				temp1 = userTemp2;
				printf("%s's card is ", userName);
				PrintCard(playerChoice);
			}
			else if (TurnWin == 3)//if comp2 was the winner of the last round
			{
				turnLead = 3;
				printf("\n***Turn %d***\nComputer 2 will lead \n", turnNum);
				//computer 2 turn
				for (int i = 0; i < comp2cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp3 = temp3->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp2Choice->suit, temp3->suit);
				comp2Choice->face = temp3->face;
				temp3 = comp2Temp2;
				printf("Computer 2's card is ");
				PrintCard(comp2Choice);
				//computer 1 turn
				printf("\n***Turn %d***\n Computer 1 will lead \n");
				for (int i = 0; i < comp1cardNum - 1; i++) {//finds the card based on the random number generated for comp1
					temp2 = temp2->listp;
				}
				//copies the face and suit of the random card
				strcpy(comp1Choice->suit, temp2->suit);
				comp1Choice->face = temp2->face;
				temp2 = comp1Temp2;
				printf("Computer 1's card is ");
				PrintCard(comp1Choice);
				//player turn
				while ((cardNum > numCardsUser) || (cardNum < 1)) {
					printf("Choose a card to play\n");
					PrintHand(userName, temp1);
					printf("\nEnter card number between 1-%d where 1 is the leftmost card: ", numCardsUser);
					scanf("%d", &cardNum);
				}
				for (int i = 0; i < cardNum - 1; i++) {//goes through a loop to find the chose card
					temp1 = temp1->listp;
				}
				//copies face and suit of card
				strcpy(playerChoice->suit, temp1->suit);
				playerChoice->face = temp1->face;
				temp1 = userTemp2;
				printf("%s's card is ", userName);
				PrintCard(playerChoice);
			}
		}
		turnWinner(playerChoice, comp1Choice, comp2Choice, turnLead, &userPoints, &comp1Points, &comp2Points, &TurnWin); //determines turn winner and updates points
		if (TurnWin == 0) {
			printf("Turn Win failed to Process (That is Bad) :(");
		}
		//removed each players choice card from their hand
		removeCard(&*user, &*userTail, playerChoice->face, playerChoice->suit); //calls remove functions and add functions to the third hand
		removeCard(&*comp1, &*comp1Tail, comp1Choice->face, comp1Choice->suit);
		removeCard(&*comp2, &*comp2Tail, comp2Choice->face, comp2Choice->suit);
		//adds each players choice card into the discard pile;
		addCard(&*discard, &*discardTail, playerChoice->face, playerChoice->suit);
		addCard(&*discard, &*discardTail, comp1Choice->face, comp1Choice->suit);
		addCard(&*discard, &*discardTail, comp2Choice->face, comp2Choice->suit);
		printf("\n ** TURN SUMMARY **");
		printf("\n%s played ", userName);
		PrintCard(playerChoice);
		printf("Computer 1 played ");
		PrintCard(comp1Choice);
		printf("Computer 2 played ");
		PrintCard(comp2Choice);
		printf("Turn %d, %s, Comp1, Comp2 have %d %d %d points\n", turnNum, userName, userPoints, comp1Points, comp2Points);
		turnNum++;
	}

	if ((userPoints < comp1Points) && (userPoints < comp2Points)) { //determines the winner of the round
		printf("\n%s Wins the Round!!!!\n", userName);
	}
	else if ((comp1Points < userPoints) && (comp1Points < comp2Points)) {
		printf("\nComputer 1 Wins the Round!!!!\n");
	}
	else if ((comp2Points < userPoints) && (comp2Points < comp1Points)) {
		printf("\nComputer 2 Wins the Round!!!!\n");
	}
	else if ((userPoints < comp2Points) && (userPoints == comp1Points)) {
		printf("\n%s & Computer 1 Win the Round!!!!\n", userName);
	}
	else if ((userPoints < comp1Points) && (userPoints == comp2Points)) {
		printf("\n%s & Computer 2 Win the Round!!!!\n", userName);
	}
	else if ((comp1Points < userPoints) && (comp2Points == comp1Points)) {
		printf("\nComputer 1 & Computer 2 Win the Round!!!!\n");
	}
}

int main(void)
{
	char quit = 't';
	while ((quit != 'Q') && (quit != 'q')) {
		card* HN = NULL, * temp, * TN = NULL, * H1 = NULL, * H2 = NULL, * H3 = NULL, * T1 = NULL, * T2 = NULL, * T3 = NULL;
		card* DiscHead = (card*)malloc(sizeof(card));
		DiscHead->face = 2;
		strcpy(DiscHead->suit, CLUB);
		card* DiscTail = DiscHead;
		int i, j;
		char PlayerName[20];
		temp = (card*)malloc(sizeof(card));
		//Build Deck
		for (j = 0; j < 4; j++) { //integrates for each suit
			for (i = 0; i < 13; i++) { //integrates for each face
				if (j == 0) { //if suit = 0, sets suit to spade and integrates for each face
					temp->face = i + 1;
					strcpy(temp->suit, SPADE);
					if (HN == NULL) {
						HN = temp;
						HN->listp = TN;
					}
					else {
						TN->listp = temp;
					}
					TN = temp;
					TN->listp = NULL;
					temp = (card*)malloc(sizeof(card));
				}
				else if (j == 1) {
					temp->face = i + 1;
					strcpy(temp->suit, HEART);
					if (HN == NULL) {
						HN = temp;
						HN->listp = TN;
					}
					else {
						TN->listp = temp;
					}
					TN = temp;
					TN->listp = NULL;
					temp = (card*)malloc(sizeof(card));
				}
				else if (j == 2) {
					temp->face = i + 1;
					strcpy(temp->suit, CLUB);
					if (HN == NULL) {
						HN = temp;
						HN->listp = TN;
					}
					else {
						TN->listp = temp;
					}
					TN = temp;
					TN->listp = NULL;
					temp = (card*)malloc(sizeof(card));
				}
				else if (j == 3) {
					temp->face = i + 1;
					strcpy(temp->suit, DIAMOND);
					if (HN == NULL) {
						HN = temp;
						HN->listp = TN;
					}
					else {
						TN->listp = temp;
					}
					TN = temp;
					TN->listp = NULL;
					temp = (card*)malloc(sizeof(card));
				}
			}
		}
		printf("\n					**************** Create 52-Card Deck ****************\n");
		PrintDeck(HN);
		printf("\n					**************** Remove 2 of Diamonds ***************\n");
		removeCard(&HN, &TN, 2, DIAMOND); //remove 2 of Diamonds
		PrintDeck(HN);
		printf("\n");
		//Shuffle Deck

		Shuffle(HN, TN, 51);
		printf("\n					**************** After Shuffle ****************\n");
		PrintDeck(HN);
		printf("\n\n");
		printf("Enter your name: "); //prompts user to enter their name
		scanf("%s", PlayerName);
		printf("\n***---*** ***---*** ***---***\n");
		printf("%s, let's play Hearts\n", PlayerName);
		printf("\n***---*** ***---*** ***---***\n");
		Deal(&HN, &H1, &H2, &H3); //distributes cards to each hand based on their location in the shuffled deck
		getTail(&H1, &T1); //obtains the tail node of each hand list
		getTail(&H2, &T2);
		getTail(&H3, &T3);
		PrintHand(PlayerName, H1); //prints the hand lists as well as the player name and number of cards in each hand
		printf("\n");
		giveCards(&H1, &T1, &H2, &T2, &H3, &T3); //prompts user to give cards to another player, does the same for the computers
		printf("\n");
		PrintHand(PlayerName, H1);
		turn(&H1, &T1, &H2, &T2, &H3, &T3, PlayerName, &TN, &DiscHead, &DiscTail);
		printf("\nWould you like to play again? (Press 'Q' to quit): "); //asks the user if they would like to continue
		scanf(" %c", &quit);
	}
	return(0);
}


