
#include <string.h> 
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <time.h> 

#include "card.h"
#include "deck.h"
#include "player.h"
#define Dialogue_speed 1

struct player player1 = {"Player1", NULL, {0}, 0 }; // Initialize player1
struct player computer = { "Player2",NULL, {0}, 0 }; // Initialize computer

struct player* game_players[] = { &player1, &computer }; // Array of player pointers

struct deck deck_instance;

const char* rank_names[] = {NULL, NULL,"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
};

const char* suit_names[] = {
    NULL, "S", "C", "H", "D"
};

void print_deck(const struct deck* d);
void print_player_hand(const struct player* target);
void print_player_book(const struct player* target);
void player_turn(struct player* current_player, struct player* opponent);
void game_loop();
void reset_game();



int main(int args, char* argv[]) 
{
    srand(time(NULL));

    create_deck(&deck_instance);
    shuffle(&deck_instance);
    printf("Shuffling Deck....\n");
    
    int deal_cards = 7;

    // Loop through each player and deal cards
    for (int player_num = 0; player_num < 2; player_num++) 
    {
        struct player* p = game_players[player_num]; 
        for (int card_count = 0; card_count < deal_cards; card_count++)
        {
            // Draw a card from the deck
            struct card* c = deck_draw(&deck_instance);
            if (c == NULL) {
                printf("No more cards in the deck!\n");
                break; 
            }

            // Add the card to the player's hand
            int result = add_card(p, c); 
            if (result == -1) {
                printf("Error\n");
                free(c); 
            } else if (result == -2) {
                printf("Error\n");
                free(c); 
            } else if (result != 0) {
                printf("Error\n");
                free(c); 
            } else {
                
                free(c); 
            }

        }
        
    }

    
    
    game_loop();

    return 0;
}

void print_player_hand(const struct player* target) {
    struct hand* current = target->card_list;
    printf("%s's Hand: ", target->name);
    while (current != NULL) {
        // Print the rank
        if (current->top.rank == 10) {
            printf("10"); 
        } else if (current->top.rank == 11) {
            printf("J"); 
        } else if (current->top.rank == 12) {
            printf("Q"); 
        } else if (current->top.rank == 13) {
            printf("K"); 
        } else if (current->top.rank == 14) {
            printf("A"); 
        } else {
            printf("%d", current->top.rank); 
        }

        // Print the suit
        switch (current->top.suit) {
            case S: printf("S "); break; 
            case C: printf("C "); break; 
            case H: printf("H "); break; 
            case D: printf("D "); break; 
        }

        current = current->next; // Move to the next card
    }
    printf("\n");
}





void print_player_book(const struct player* target) {
    
    printf("%s's Book: ",target->name);
    for (int i = 0; i < 7; i++) {
        // Print only non-empty entries
        if (target->book[i] != '\0') {
            
            if (target->book[i] == 10) {
                printf("10 "); 
            } else if (target->book[i] == 11) {
                printf("J "); 
            } else if (target->book[i] == 12) {
                printf("Q "); 
            } else if (target->book[i] == 13) {
                printf("K "); 
            } else if (target->book[i] == 14) {
                printf("A "); 
            } else {
                printf("%d ", target->book[i]); 
            }
        }
    }
    printf("\n");
}

void game_loop() {
    int game_over_flag = 0;
    int player_turn = 1;

    while (!game_over_flag) {
        if (player_turn){
        print_player_hand(&player1);
        print_player_book(&player1);
        print_player_book(&computer);
    
        char user_rank = user_play(&player1);
   
        if (search(&computer, user_rank)) {
            sleep(Dialogue_speed);
            int transferred = transfer_cards(&computer, &player1, user_rank);
        
            if (transferred > 0) {
                // Successfully transferred cards
                
                int booked1 = check_add_book(&player1);
                if (booked1 != 0) {
                    printf("       -Player1 booked %d\n", booked1);
                    printf("       -Player1's turn\n");
		    printf("\n");

                    
                    continue;
                }
                printf("        - Player 1 took %d card(s) from Player 2.\n", transferred);
                int booked11 = check_add_book(&player1);
                if (booked11 != 0) {
                    printf("       -Player1 booked %d\n", booked1);
                    printf("       -Player1's turn");

                    
                    continue;
                }
                printf("        - Player1's turn\n");
                printf("\n");
                continue;
            }
        } else {
            sleep(Dialogue_speed);
            printf("       -Player2 has no %d's\n", user_rank);
           
            struct card* new_card = deck_draw(&deck_instance);
            printf("       - Go Fish! Player1 draws %s%s\n", rank_names[new_card->rank], suit_names[new_card->suit]);
            
            add_card(&player1, new_card);
            int booked2 = check_add_book(&player1);
            if (booked2 != 0) {
                printf("       -Player1 booked %d\n", booked2);
                printf("       -Player 1 gets another turn.\n");
                printf("\n");
                continue;
            } else if (new_card->rank == user_rank) {
                int booked3 = check_add_book(&player1);
                if (booked3 != 0) {
                    printf("       -Player1 booked %d\n",booked3 );
                    
                    continue;
                }
                printf("       - Player1's turn\n"); 
                printf("\n");
                continue;
            }
            printf("       - Player2's turn\n");
            printf("\n");
            sleep(Dialogue_speed);
        }
        
        
        int booked4 = check_add_book(&player1);
        if (booked4 != 0) {
            printf("       -Player1 booked %d\n",booked4 );
            
            continue;
        }
        printf("\n");
        } else {
        // Computer's turn
        sleep(Dialogue_speed);
        print_player_hand(&player1);
        print_player_book(&player1);
        
        char comp_rank = computer_play(&computer);
        // check_add_book(&computer);
        print_player_book(&computer);
        printf("Player2 asks for rank: %d\n", comp_rank);
    
        if (search(&player1, comp_rank)) {
            sleep(Dialogue_speed);
            int transferred = transfer_cards(&player1, &computer, comp_rank);
            if (transferred > 0) {
                printf("       - Player2 took %d card(s) from Player 1.\n", transferred);
                
                
                int booked5 = check_add_book(&computer);
                if (booked5 != 0) {
                    printf("       -Player2 booked %d\n", booked5);
                    printf("       -Player2's turn\n");
                    printf("\n");
                    continue;
                } 
                printf("       - Player2's turn\n");
                printf("\n");
                continue;
            } 
        } else {
            sleep(Dialogue_speed);
            printf("       - Go Fish! Player2 draws a card\n");
           
            // Draw a card for the computer
            struct card* new1_card = deck_draw(&deck_instance);
            add_card(&computer, new1_card);
            printf("\n");
            int booked6 = check_add_book(&computer);
            if (booked6 != 0) {
                print_player_book(&computer);
                printf("       -Player 2 booked %d!\n", booked6);
                printf("       -Player 2 gets another turn.\n");
                printf("\n");
                continue;
            }
            if (new1_card->rank == comp_rank) {
                // printf("                - Player 2 draws %s%s from the deck.\n", rank_names[new1_card->rank], suit_names[new1_card->suit]);
                printf("       -Player 2 gets another turn\n");
                int booked7 = check_add_book(&computer);
                if (check_add_book(&computer) != 0) {
                    printf("       -Player2 booked %d\n", booked7);
                    
                    continue;
                } 
                
            }
		printf("	-Player1's turn\n");
		printf("\n");
        }
        
        }
    
        
        int booked8 = check_add_book(&computer);
        if (booked8!= 0) {
            printf("       -Player2 booked %d\n", booked8);
            print_player_book(&computer);
            continue;
        }
        
        printf("\n");
        player_turn = !player_turn;
        if (player1.book_count == 7) {
            printf("Player 1 wins! %zu - %zu \n", player1.book_count, computer.book_count);

            printf("Do you want to play again? [Y/N]: ");
            char choice;
            scanf(" %c", &choice); 

            if (choice == 'Y' || choice == 'y') {
		printf("\n");
                reset_game(); 
            } else if (choice == 'N' || choice == 'n') {
                printf("Thanks for playing!\n");
                exit(0); 
            } else {
                printf("Invalid choice! Exiting game.\n");
                exit(0); 
            }
        }

        if (computer.book_count == 7) {
            printf("Player2 won! %zu - %zu\n", computer.book_count, player1.book_count);

            printf("Do you want to play again? [Y/N]: ");
            char choice;
            scanf(" %c", &choice); 
            if (choice == 'Y' || choice == 'y') {
                reset_game();
            } else if (choice == 'N' || choice == 'n') {
                printf("Thanks for playing!\n");
                exit(0); 
            } else {
                printf("Invalid choice! Exiting game.\n");
                exit(0); 
            }
        }
    }
}



// void print_deck(const struct deck* d) {
//     for (int i = 0; i < 52; i++) {
//         struct card current_card = d->list[i];
//         printf("%s of %s\n", rank_names[current_card.rank], suit_names[current_card.suit]);
//     }
// }

void reset_game() {
    create_deck(&deck_instance);
    shuffle(&deck_instance);
    reset_player(&player1);
    reset_player(&computer);
    int deal_cards = 7;
    for (int player_num = 0; player_num < 2; player_num++) {
        struct player* p = game_players[player_num];
        for (int card_count = 0; card_count < deal_cards; card_count++) {
            struct card* c = deck_draw(&deck_instance);
            int result = add_card(p, c);
            if (result == 0) free(c);
            else free(c);
        }
    }
}


