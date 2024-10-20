#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include "card.h"

#define Hand_size 7

struct player {
    char* name;
    struct hand* card_list; // Linked list of cards
    char book[7]; // Array to hold the ranks of completed books
    size_t hand_size; // Current number of cards in hand
    size_t book_count; // New member to track the number of books
};


extern struct player user;
extern struct player computer;


int add_card(struct player* target, struct card* new_card);
char check_add_book(struct player* target);

int remove_card(struct player* target, char rank);


int search(struct player* target, char rank);

int transfer_cards(struct player* src, struct player* dest, char rank);


char computer_play(struct player* target);


char user_play(struct player* target);
int reset_player(struct player* target);

#endif

