
#include "deck.h"
#include "card.h"
#include <stdlib.h>
#include <string.h>
// #define Max_cards 52
/*
 * Variable: deck_instance
 * -----------------------
 *  
 * Go Fish uses a single deck
 */

// struct deck *remaining_pile;
// struct deck *discard_pile;



int shuffle(struct deck* d){
  int replacements = rand() % 901 + 100;  //Random no. to determine iterations of below for loop
    for (int i = 0; i < replacements; i++) {
        int A = rand() % size_deck;  // Random index 
        int B = rand() % size_deck;  
        
        
        struct card temp = d->list[A];
        d->list[A] = d->list[B];
        d->list[B] = temp;
    }
  return 0;

}

void create_deck(struct deck* d){
    d->top = -1;
    rank rank;
    suit suit;

    for(suit = S; suit <=MAX_SUIT; suit++ ){
        for(rank = R2; rank <= MAX_RANK; rank++ ){
            struct card card;
            card.suit = suit;
            card.rank = rank;
            if (add_card_deck(d, &card)){ //***check if add_card can accept deck, or create deck_put */
              exit(1);
            }
        }


    }
}


int add_card_deck(struct deck* d, struct card* c){
  if(d->top == size_deck - 1)
  {
    exit(1);
  }
  d->top++;
  d->list[d->top] = *c;

  return 0;
}

 struct card* next_card(struct deck* d){
    if (d == NULL || d->top < 0) {
        return NULL; 
    }

    struct card* drawn_card = &d->list[d->top];

    d->top--;

    return drawn_card; 
}

int deck_size(const struct deck* d){
    if (d == NULL) {
        return -1; 
    }
    
    return d->top + 1; 
}

struct card* deck_draw(struct deck* d) {
    // Check if the deck is empty
    if (d == NULL || d->top < 0) {
        return NULL;  
    }

    // Allocate memory for a new card
    struct card* c = malloc(sizeof(struct card));
    if (c == NULL) {
        return NULL;  
    }

    
    memcpy(c, &d->list[d->top], sizeof(struct card));

    memset(&d->list[d->top], 0, sizeof(struct card));

    d->top--;
    return c; //ks: do you need rank and suit or should we do that in main?
}

