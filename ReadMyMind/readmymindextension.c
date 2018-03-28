#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

// this is the struct for the card, it is essentially the equivalent of a java object class
struct Card
{
    char type;
    char value;
};

// the basic method for printing out the information on the card
void printCard(struct Card *ptrC)
{
    if(ptrC->value == '0') // this check right here is because if the value given was 0, it was supposed to represent 10, so it makes sure that 10 is printed instead of 0
    {
        printf(" %d%c", 10, ptrC->type); // this notation '->' is used because the variable is a pointer
    }
    else
        printf(" %c%c", ptrC->value, ptrC->type);
}

// this is the method that is used for creating the entire deck of 52 cards
void populateDeck(struct Card *deck, char types[], char values[])
{
    int index;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            index = i * 13 + j;
            (deck + index)->type = types[i]; // using the '->' for the reason that the variable being called is a pointer
            (deck +index)->value = values[j];
            //printCard(deck[index]);
        }
    }
}

// picking 21 unique cards from a deck of 52 cards
void pick21Cards(struct Card *dealtHand[], bool selected[], struct Card *deck)
{
    for(int i = 0; i < 52; i++)
    {
        selected[i] = false; // first populating an array of bools to keep track of which card has been drawn or not
        
    }
    for(int i = 0; i < 21; i++) // this is the loop that is used to select the 21 cards
    {
        int random;
        random = rand() % 52;
        if(selected[random] == true) // telling the program to get another card because the card has been chosen
        {
            i--;
            continue;
        }
        dealtHand[i] = deck + random;
        selected[random] = true; // setting the value in the selected array to be true because it means the card in that postion has been chosen
        //printCard(dealtHand[i]);
    }
}

// this populates the left middle and right columns for the first iteration from the unshuffled 21 cards
void populateLeftMiddleRight(struct Card **left, struct Card **middle, struct Card **right, struct Card *dealtHand[])
{
    for(int i = 0; i < 7; i++)
    {
        left[i] = dealtHand[i*3];
        middle[i] = dealtHand[i*3+1];
        right[i] = dealtHand[i*3 + 2 ];
    }
}

// this prints out the deck in the proper format
void printFormattedDeck(struct Card **left, struct Card **middle, struct Card **right)
{
    for(int i = 0; i < 7; i++)
    {
        printCard(left[i]);
        printf(" ");
        printCard(middle[i]);
        printf(" ");
        printCard(right[i]);
        printf("\n");
        
    }
}

// this repopulates the set of dealt hands so that it is properly shuffled
void populateDealtHand(struct Card **left, struct Card **middle, struct Card **right, struct Card *dealtHand[])
{
    for(int i = 0; i < 7; i ++)
    {
        dealtHand[i] = left[i];
        dealtHand[i+7] = middle[i];
        dealtHand[i+14] = right[i];
    }
}

// this is the simple shifting of the columns to assist with the shuffling
void shiftColumn(struct Card ***left, struct Card ***middle, struct Card ***right, char *userInput)
{
    struct Card **temp;
    if(*userInput == 'L')
    {
        temp = *middle;
        *middle = *left;
        *left = temp;
    }
    else if(*userInput == 'R')
    {
        temp = *middle;
        *middle = *right;
        *right = temp;
    }
    else if(*userInput == 'M')
    {
        
    }
    
    
}

// This gets the user input and decides if the input is valid or not.
void getUserInput(char *userInput)
{
    while(1 == 1) // this loop was added in for the extension because it checks if the user gives valid input for the swapping of columns.
    {
        printf("Tell me which column your card is in L for left M for middle and R for right\n" );
        scanf(" %c", userInput);
        printf("%c\n", *userInput);
        if(*userInput == 'L' || *userInput == 'R' || *userInput == 'M' )
            return ;
        printf("Invalid input, please try again \n");
    }
    
}

// This combines the necessary methods so that we can perform the trick successfully.
void doTrick(struct Card ***left, struct Card ***middle, struct Card ***right, struct Card *dealtHand, char *userInput)
{
    for(int i = 0; i < 3; i++)
    {
        getUserInput(userInput);
        shiftColumn(left, middle, right, userInput);
        populateDealtHand(*left, *middle, *right, dealtHand);
        populateLeftMiddleRight(*left, *middle, *right, dealtHand);
        printFormattedDeck(*left, *middle, *right);
        
    }
}

// this simply gets the position of the card that is chosen
void printSelectedCard(struct Card ***middle)
{
    printf("The card you chose is!!!: \n");
    printCard( middle[3]);
}


// this is the main method where everything is ran
int main()
{
    
    printf("read mind \n");
    char userInput;
    char continueInput = 'Y';
    struct Card deckAll[52];
    struct Card *deck = deckAll;
    bool selected[52];
    char types[] = {'C', 'S', 'D', 'H'}; // these are the card symbols C for Clover, S for Spade, D for Diamond, H for Heart
    char values[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'}; // these are the values of the card ranging from Ace all the up to king
    struct Card *dealtHand[21]; // 21 cards in the game, all of them pointers
    struct Card *leftDeck[7];
    struct Card **left = leftDeck;
    struct Card *middleDeck[7];
    struct Card **middle = middleDeck;
    struct Card *rightDeck[7];
    struct Card **right = rightDeck;
    populateDeck(deck, types, values);
    srand((unsigned) time(NULL));
    int random;
    for(int i = 0; i < 10; i++)
    {
        random = rand() % 52;
        //printf("%d\n", random);
    }
    //struct Card x;
    /*x.value = '0';
     x.type = 'S';
     printCard(x);*/
    while(continueInput == 'Y') // this is the part of the extension meant for allowing the user to replay the program for an indefinite amount of times.
    {
        pick21Cards(dealtHand, selected, deck);
        populateLeftMiddleRight(left, middle, right, dealtHand);
        printFormattedDeck(left, middle, right);
        doTrick(&left, &middle, &right, dealtHand, &userInput);
        printSelectedCard(middle);
        printf("\n");
        while( 1 == 1) // also part of the extension for checking if the input for replaying the game is valid.
        {
            printf("Would you like to play again? Y for yes N for no");
            scanf(" %c", &continueInput);
            if(continueInput == 'Y' || continueInput == 'N')
            {
                break;
            }
            printf("Invalid input, please try again \n");
        }
        
    }
}

