/*
  Counts cards in a game

  The user inputs card values that are counted
  The current value of the game is printed every time it is updated

*/

#include <stdio.h>
#include <stdlib.h>

/*Looks up and returns the value of the given card

  K,Q, and J are given a value of 10, number cards are given their number value

  card_name: name of the user inputed card
*/
int getCardValue(char card_name[]){
  int val = 0;
  switch(card_name[0]){
  case 'K':
  case 'Q':
  case 'J':
    val = 10;
    break;
  case 'A':
    val = 11;
    break;
  case 'X':
    break;
  default:
    val = atoi(card_name);
  }
  return val;

}

/*Asks the user the for the name of the card and stores it in the buffer

  User input's first two characters are saved

  card_name: buffer where result is stored
*/
void getCardName(char *card_name){
  puts("Enter the card name: ");
  scanf("%2s", card_name);
}

/*Updates the card count based on the given value

  Card values between 2 and 7 increase the count by one
  Card values above 10 decrese the count by one
  Other card values are not accepted

  count: buffer where count is increased
  val: value of the user's card
*/
void updateCount(int *count, int val){

  if((val > 2) && (val<7)){
    *count = *count + 1;
  }else if(val > 10){
    *count = *count -1;
  }else{
    puts("I don't understand that value!\n");
  }
}

/*Takes in user card values to create a count of the cards

  An 'X' user input stops the counting and exits
  Otherwise, the card value is found and count is incremented appropritly
  The value of count is printed everytime it is changed

*/
int main(){
  char exitChar = 'X';
  char card_name[3];
  int val = 0;
  int count = 0;
  while(card_name[0]!=exitChar){
    getCardName(card_name);
    if(card_name[0] == exitChar){
      continue;
    }
    val = getCardValue(card_name);
    updateCount(&count, val);
    printf("Current count is %i\n", count);
  }
    return 0;
}
