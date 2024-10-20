#include "player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Instance Variables: user, computer   
 * ----------------------------------
 *  
 *  We only support 2 users: a human and a computer
 */
struct player user;
struct player computer1;








int add_card(struct player* target, struct card* new_card) {
    if (target == NULL || new_card == NULL) {
        printf("Error\n");
        return -1;
    }

    
    if (target->hand_size == 0) {
        target->card_list = NULL; 
    }
    struct hand* new_node = malloc(sizeof(struct hand));
    if (new_node == NULL) {
        printf("Error\n");
        return -2;
    }
    //linked list
    new_node->top = *new_card;
    new_node->next = NULL;

    
    if (target->hand_size == 0) {
        target->card_list = new_node;
    } else {
        struct hand* current = target->card_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    target->hand_size++; 
    
    return 0; 
}


int remove_card(struct player* target, char rank) {
    if (target == NULL) {
        return -1;  
    }

    struct hand* current = target->card_list;
    struct hand* previous = NULL;

    while (current != NULL) {
        if (current->top.rank == rank) {
            if (previous == NULL) {
                
                target->card_list = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);  
            target->hand_size--;  //subtract size
            return 0;  
        }
        previous = current;
        current = current->next;
    }

    return -1;  
}


int search(struct player* target, char rank) {
    if (target == NULL || target->card_list == NULL) {
        return 0;  
    }

    //scan linked list
    struct hand* current = target->card_list;
    while (current != NULL) {
        if (current->top.rank == rank) {
            return 1; 
            continue;
        }
        current = current->next;
    }

    return 0;  
}






char check_add_book(struct player* target) {
    int card_counts[MAX_RANK + 1] = {0};

   
    struct hand* current = target->card_list;
    while (current != NULL) {
        card_counts[current->top.rank]++;
        current = current->next;
    }

    
    for (int x = R2; x <= MAX_RANK; x++) {
        if (card_counts[x] >= 4) {
            current = target->card_list;
            struct hand* prev = NULL;

            while (current != NULL) {
                if (current->top.rank == x) {
                    struct hand* to_remove = current;
                    if (prev == NULL) {
                        target->card_list = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    current = current->next;
                    free(to_remove);
                    target->hand_size--;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
            for (int i = 0; i < 7; i++) {
                if (target->book[i] == '\0') {
                    target->book[i] = x;
                    target->book_count++; 
                    break;
                }
            }

            return x; 
        }
    }

    
    return 0; 
}


int transfer_cards(struct player* src, struct player* dest, char rank) {
    if (src == NULL || dest == NULL) {
        return -1;  
    }
    if (!search(src, rank)) { //KS: trying using search, no need to manually scan
        return 0; 
    }

    struct hand* current = src->card_list;
    int cards_transferred = 0;
    struct hand* cards_to_transfer = NULL; 

   //ks: not sure if search will work here, won't return all ranks
    while (current != NULL) {
       
        if (current->top.rank == rank) {
            
            struct card* temp_card = malloc(sizeof(struct card));
            if (temp_card == NULL) {
                while (cards_to_transfer != NULL) {
                    struct hand* temp = cards_to_transfer;
                    cards_to_transfer = cards_to_transfer->next; //ks: need to free ig
                    free(temp);
                }
                return -2;  
            }
            temp_card->rank = current->top.rank;
            temp_card->suit = current->top.suit;

            struct hand* new_hand_node = malloc(sizeof(struct hand));
            if (new_hand_node == NULL) {
                free(temp_card); //gk: should it temp card be free over here as well?
                return -2; 
            }
            new_hand_node->top = *temp_card;
            new_hand_node->next = cards_to_transfer;
            cards_to_transfer = new_hand_node;
            
            
            if (add_card(dest, temp_card) == 0) {
                cards_transferred++;  
            } else {
                
                free(temp_card);
                free(new_hand_node); //gk: something here is causing segmentation fault
            }
        }

        
        current = current->next;
    }
    //ks: to be fixed: should transfer all cards from hand, only transferring 1st card founf

    
    while (cards_to_transfer != NULL) {
        struct hand* temp = cards_to_transfer;
        cards_to_transfer = cards_to_transfer->next;
        
        remove_card(src, temp->top.rank); //gk: check remove_card; giving error
        free(temp); 
    }

    return cards_transferred; 
}




char computer_play(struct player* target) {
    if (target == NULL || target->card_list == NULL) {
        return -1;  
    }

    
    int rank_seen[14] = {0};  //ks: changed this was 13
    struct hand* current = target->card_list;
    int unique_ranks = 0;

    while (current != NULL) {
        if (rank_seen[current->top.rank - 1] == 0) {  
            rank_seen[current->top.rank - 1] = 1;
            unique_ranks++;
        }
        current = current->next;
    }

    int rank_index = rand() % unique_ranks;  
    int current_rank = 0;

   
    for (int i = 1; i < 14; i++) { 
        if (rank_seen[i]) {
            if (current_rank == rank_index) {
                return i + 1;  
            }
            current_rank++;
        }
    }

    return -1;  
}


//ks: this works okay but select input needs to be changed for limits

//gk: error handling is not working properly, accepts erroneous inputs
char user_play(struct player* target) {
    if (target == NULL || target->card_list == NULL) {
        return -1;  
    }

    int selected_rank;
    int valid_rank = 0;
    while (!valid_rank) {
        printf("Player 1's turn, enter a rank: ");
        int result = scanf("%d", &selected_rank);

        if (result != 1) {
            while (getchar() != '\n');  
            printf("Error - invalid input. Please enter a number between 2 and 14.\n");
            continue;  
        }

        if (selected_rank < 2 || selected_rank > 14) {
            printf("Error - invalid rank. Please enter a number between 2 and 14.\n");
            continue;
        }
        
        
        if (!search(target, selected_rank)) {
            printf("Error - must have at least one card of that rank to play.\n");
            continue;
        }
        valid_rank = 1; 
    }
    return selected_rank;  
}









//try using this should work
int reset_player(struct player* target) {
    if (target == NULL) {
        return -1;  
    }

    
    struct hand* current = target->card_list;
    while (current != NULL) {
        struct hand* temp = current;
        current = current->next;
        free(temp);  
    }

    
    target->card_list = NULL;
    target->hand_size = 0;

   
    target->book_count = 0;  
    memset(target->book, 0, sizeof(target->book));  

    return 0;  
}
