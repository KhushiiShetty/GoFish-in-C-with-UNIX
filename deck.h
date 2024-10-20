#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include "player.h"
#include "card.h"

#define size_deck 52



struct deck {
  struct card list[size_deck];
  int top;
};


extern struct deck deck_instance; 


int shuffle(struct deck* d);
void create_deck(struct deck* d);

int add_card_deck(struct deck* d, struct card* c);


// int deal_player_cards(struct player* target, struct deck* d);//not working will do in main




struct card* next_card(struct deck* d);

int deck_size(const struct deck* d);
struct card* deck_draw(struct deck* d);
#endif
