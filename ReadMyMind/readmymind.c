#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


struct Card
{
    char type;
    char value;
};


void printCard(struct Card *ptrC)
{
    if(ptrC->value == '0')
    {
        printf(" %d%c", 10, ptrC->type);
    }
    else
        printf(" %c%c", ptrC->value, ptrC->type);
}

void populateDeck(struct Card *deck, char types[], char values[])
{
    int index;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            index = i * 13 + j;
            (deck + index)->type = types[i];
            (deck +index)->value = values[j];
            //printCard(deck[index]);
        }
    }
}

void pick21Cards(struct Card *dealtHand[], bool selected[], struct Card *deck)
{
    for(int i = 0; i < 21; i++)
    {
        int random;
        random = rand() % 52;
        if(selected[random] == true)
        {
            i--;
            continue;
        }
        dealtHand[i] = deck + random;
        selected[random] = true;
        //printCard(dealtHand[i]);
    }
}

void populateLeftMiddleRight(struct Card **left, struct Card **middle, struct Card **right, struct Card *dealtHand[])
{
    for(int i = 0; i < 7; i++)
    {
        left[i] = dealtHand[i*3];
        middle[i] = dealtHand[i*3+1];
        right[i] = dealtHand[i*3 + 2 ];
    }
}

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

void populateDealtHand(struct Card **left, struct Card **middle, struct Card **right, struct Card *dealtHand[])
{
    for(int i = 0; i < 7; i ++)
    {
        dealtHand[i] = left[i];
        dealtHand[i+7] = middle[i];
        dealtHand[i+14] = right[i];
    }
}

void shiftColumn(struct Card ***left, struct Card ***middle, struct Card ***right, char *userInput)
{
    struct Card **temp;
    if(*userInput == 'L')
    {
        temp = *middle;
        *middle = *left;
        *left = temp;
    }
    if(*userInput == 'R')
    {
        temp = *middle;
        *middle = *right;
        *right = temp;
    }
    if(*userInput == 'M')
    {
        
    }
    
}

void getUserInput(char *userInput)
{
    printf("Tell me which column your card is in L for left M for middle and R for right\n" );
    scanf(" %c", userInput);
    printf("%c\n", *userInput);
    
}

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

void printSelectedCard(struct Card ***middle)
{
    printf("The card you chose is!!!: ");
    printCard( middle[3]);
}

int main()
{
    
    printf("read mind \n");
    char userInput;
    struct Card deckAll[52];
    struct Card *deck = deckAll;
    bool selected[52];
    char types[] = {'C', 'S', 'D', 'H'};
    char values[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
    struct Card *dealtHand[21];
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
    pick21Cards(dealtHand, selected, deck);
    populateLeftMiddleRight(left, middle, right, dealtHand);
    printFormattedDeck(left, middle, right);
    doTrick(&left, &middle, &right, dealtHand, &userInput);
    printSelectedCard(middle);
    printf("\n");
}



