#ifndef CARD_H
#define CARD_H
#define MAX_RANK 14
#define MAX_SUIT 4

extern const char* rank_names[];
enum Rank 
{
  R2= 2, R3, R4, R5, R6, R7,
	R8, R9, R10, RJ , RQ , RK , RA
};
typedef int rank;


enum Suit{
  S = 1, C, H, D
};
typedef int suit;


struct card
{
  suit suit;
  rank rank;
};




struct hand {
  struct card top;
  struct hand* next;
};



#endif
