#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef char				C1;
typedef signed char			S1;
typedef signed short		S2;
typedef signed long			S4;
typedef signed long long	S8;
typedef unsigned char		U1;
typedef unsigned short		U2;
typedef unsigned long		U4;
typedef unsigned long long	U8;
typedef U1					CID; /* Card ID */
typedef U2					POKER_HAND; /* Pokerの役 */

#define D_POKER_CARD_NUMBER				(13)
#define D_POKER_CARD_MARK				(4)
#define D_POKER_CARD_NUM_MAX			(D_POKER_CARD_NUMBER * D_POKER_CARD_MARK + 1)

#define D_CARD_MARK_SPADE				(0x80)
#define D_CARD_MARK_HEART				(0x40)
#define D_CARD_MARK_CLOVER				(0x20)
#define D_CARD_MARK_DIAMOND				(0x10)
#define D_CARD_MARK_JOKER				(0xF0)
#define D_CARD_MARK_SPADE_S				"Spade"
#define D_CARD_MARK_HEART_S				"Heart"
#define D_CARD_MARK_CLOVER_S			"Clover"
#define D_CARD_MARK_DIAMOND_S			"Diamond"
#define D_CARD_MARK_JOKER_S				"Joker"

#define D_POKER_HAND_CARD_MAX			(5)


#define M_ERROR(...)			printf(__VA_ARGS__)

#define M_CARD_NUMBER_ID(cid)		(cid & 0x0F)
#define M_CARD_NUMBER(cid)			((cid & 0x0F) + 1)
#define M_CARD_MARK_ID(cid)			(cid & 0xF0)
#define M_CARD_MARK(cid)			debug_print_mark(cid)



typedef enum {
	E_TRUE = 0,
	E_FALSE = 1,
} E_BOOL;

typedef struct {
	CID	id[D_POKER_CARD_NUM_MAX];
	U1	startIndex;
	// U1	lastIndex;
	U1	remainingNumber;
} CARD;

typedef struct {
	CID	id[D_POKER_HAND_CARD_MAX];
	U1	num;
} HAND_CARD;

CARD s_card = {};

void card_plusJoker()
{
	s_card.id[s_card.remainingNumber] = 0xFF;
	s_card.remainingNumber += 1;
}

void card_outOfBox()
{
	CARD initial_card = {
		{
			0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
			0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
			0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
			0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D,
		},
		0, 
		// D_POKER_CARD_NUMBER * D_POKER_CARD_MARK,
		D_POKER_CARD_NUMBER * D_POKER_CARD_MARK,
	};

	s_card = initial_card;
	card_plusJoker();
}

void system_random_init()
{
	srand((unsigned)time(NULL));
}

int system_random()
{
	int r = rand();
	// printf("rand = %d\n", r);
	return r;
}

void card_fisherYatesShuffle(CID id[], U1 size)
{
	system_random_init();
	U1 i = 0;
	for (i = 0; i < size; i++) {
		U1 j = system_random() % size;
		CID temp = id[i];
		id[i] = id[j];
		id[j] = temp;
	}
}

CID card_deal()
{
	CID dealCard = s_card.id[s_card.startIndex];
	s_card.startIndex ++;
	s_card.remainingNumber --;
	return dealCard;
}

void card_shuffle()
{
	card_fisherYatesShuffle(&(s_card.id[s_card.startIndex]), s_card.remainingNumber);
}

HAND_CARD s_handCard = {};
void player_receiveCard(CID id)
{
	if (s_handCard.num >= D_POKER_HAND_CARD_MAX) {
		M_ERROR("maximum number of cards.\n");
		return;
	}
	s_handCard.id[s_handCard.num] = id;
	s_handCard.num ++;
}

HAND_CARD player_handCard()
{
	return s_handCard;
}

void card_bubbleSort(HAND_CARD *card)
{
	U1 i = 0;
	U1 j = 0;
	for (i=0; i < card->num; i++) {
		for (j = card->num - 1; j > i; j--) {
			if( card->id[j] < card->id[j-1]) {
				CID temp = card->id[j];
				card->id[j] = card->id[j-1];
				card->id[j-1] = temp;
			}
		}
	}
}

void player_sort()
{
	if (s_handCard.num < D_POKER_HAND_CARD_MAX) {
		M_ERROR("cards is small.\n");
		return;
	}
	card_bubbleSort(&s_handCard);
}

E_BOOL poker_hasJoker(HAND_CARD card)
{
	if (M_CARD_MARK_ID(card.id[card.num-1]) == D_CARD_MARK_JOKER) {
		return E_TRUE;
	} else {
		return E_FALSE;
	}
}

void poker_removeJoker(HAND_CARD *card)
{
	if (M_CARD_MARK_ID(card->id[card->num-1]) == D_CARD_MARK_JOKER) {
		card->num --;
	}
}

E_BOOL poker_isFlash(HAND_CARD card)
{
	CID judgeMark = 0xF0;
	/* card.id[0] & card.id[1] & card.id[2] & card.id[3] & card.id[4] */
	U1 i = 0;
	for (i = 0; i < card.num; i++) {
		judgeMark &= M_CARD_MARK_ID(card.id[i]);
	}
	printf("judgeMark = 0x%02x\n", judgeMark);
	if ((judgeMark == D_CARD_MARK_SPADE) || 
		(judgeMark == D_CARD_MARK_HEART) || 
		(judgeMark == D_CARD_MARK_DIAMOND) || 
		(judgeMark == D_CARD_MARK_SPADE) ) {
		return E_TRUE;
	} else {
		return E_FALSE;
	}
}

E_BOOL poker_isStraightWithoutJoker(HAND_CARD card)
{
	CID beforNumber = M_CARD_NUMBER_ID(card.id[0]);
	U1 i = 0;
	for (i = 1; i < card.num; i++) {
		CID currentNumber = M_CARD_NUMBER_ID(card.id[i]);
		if (currentNumber - beforNumber > 1) {
			return E_FALSE;
		} else if (currentNumber - beforNumber == 1) {
			/* valid decision */
			/* do nothing */
		} else {
			/* Pair judgment */
			return E_FALSE;
		}
		beforNumber = currentNumber;
	}
	return E_TRUE;
}

E_BOOL poker_isStraightWithJoker(HAND_CARD card)
{
	U1 withJoker = 0;
	CID beforNumber = M_CARD_NUMBER_ID(card.id[0]);
	U1 i = 0;
	for (i = 1; i < card.num; i++) {
		CID currentNumber = M_CARD_NUMBER_ID(card.id[i]);
		if (currentNumber - beforNumber > 2) {
			return E_FALSE;
		} else if (currentNumber - beforNumber == 2) {
			/* valid decision */
			withJoker ++;
			if (withJoker > 1) {
				return E_FALSE;
			}
		} else if (currentNumber - beforNumber == 1) {
			/* valid decision */
			/* do nothing */
		} else {
			/* Pair judgment */
			return E_FALSE;
		}
		beforNumber = currentNumber;
	}
	return E_TRUE;
}

E_BOOL poker_isStraight(HAND_CARD card)
{
	if (poker_hasJoker(card) == E_FALSE) {
		return poker_isStraightWithoutJoker(card);
	} else {
		poker_removeJoker(&card);
		return poker_isStraightWithJoker(card);
	}
}


CID poker_totalId(HAND_CARD card)
{
	CID totalId = 0;
	U1 i = 0;
	for (i = 0; i < card.num; i++) {
		totalId += M_CARD_NUMBER_ID(card.id[0]);
	}
	return totalId;
}

#define D_POKER_HAND_ROYAL_STRAIGHT_FLASH			(1<<0)
#define D_POKER_HAND_FIVE_CARD						(1<<1)
#define D_POKER_HAND_STRAIGHT_FLASH					(1<<2)
#define D_POKER_HAND_FOUR_CARD						(1<<3)
#define D_POKER_HAND_FULL_HOUSE						(1<<4)
#define D_POKER_HAND_FLASH							(1<<5)
#define D_POKER_HAND_STRAIGHT						(1<<6)
#define D_POKER_HAND_THREE_CARD						(1<<7)
#define D_POKER_HAND_TWO_PAIR						(1<<8)
#define D_POKER_HAND_ONE_PAIR						(1<<9)
#define D_POKER_HAND_BUHI							(0x00)
#define D_POKER_HAND_TYPE_MAX						(11)

#define D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITHOUT_J	(55)
#define D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITH_J		(42)


POKER_HAND poker_judgeRoyalStraightFlash(HAND_CARD card)
{
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	if (poker_hasJoker(card) == E_FALSE) {
		CID totalId = poker_totalId(card);
		if (totalId >= D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITHOUT_J) {
			judgeResult |= D_POKER_HAND_ROYAL_STRAIGHT_FLASH;
		}
	} else {
		poker_removeJoker(&card);
		CID totalId = poker_totalId(card);
		if (totalId >= D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITH_J) {
			judgeResult |= D_POKER_HAND_ROYAL_STRAIGHT_FLASH;
		}
	}
	return judgeResult;
}


POKER_HAND poker_judgeStraightFlash(HAND_CARD card)
{
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	if (poker_isStraight(card) == E_TRUE) {
		judgeResult |= D_POKER_HAND_STRAIGHT_FLASH;
	}
	return judgeResult;
}

POKER_HAND poker_judgePairWithoutJoker(HAND_CARD card)
{
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	U1 matchCount = 0;
	U1 i = 0;
	U1 j = 0;
	for (i = 0; i < card.num; i++) {
		for (j = i + 1; j < card.num; j++) {
			if (M_CARD_NUMBER_ID(card.id[i]) == M_CARD_NUMBER_ID(card.id[j])) {
				matchCount ++;
			}
		}
	}
	if (matchCount >= 6) {
		judgeResult |= D_POKER_HAND_FOUR_CARD;
	} else if (matchCount >= 4) {
		judgeResult |= D_POKER_HAND_FULL_HOUSE;
	} else if (matchCount == 3) {
		judgeResult |= D_POKER_HAND_THREE_CARD;
	} else if (matchCount == 2) {
		judgeResult |= D_POKER_HAND_TWO_PAIR;
	} else if (matchCount == 1) {
		judgeResult |= D_POKER_HAND_ONE_PAIR;
	} else {
		judgeResult |= D_POKER_HAND_BUHI;
	}

	return judgeResult;
}

POKER_HAND poker_judgePairWithJoker(HAND_CARD card)
{
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	U1 matchCount = 0;
	U1 i = 0;
	U1 j = 0;
	for (i = 0; i < card.num; i++) {
		for (j = i + 1; j < card.num; j++) {
			if (M_CARD_NUMBER_ID(card.id[i]) == M_CARD_NUMBER_ID(card.id[j])) {
				matchCount ++;
			}
		}
	}
	printf("matchCount = %d\n",matchCount);
	if (matchCount >= 6) {
		judgeResult |= D_POKER_HAND_FIVE_CARD;
	// } else if (matchCount >= 4) {
	// 	judgeResult |= D_POKER_HAND_FULL_HOUSE;
	} else if (matchCount == 3) {
		judgeResult |= D_POKER_HAND_FOUR_CARD;
	} else if (matchCount == 2) {
		judgeResult |= D_POKER_HAND_FULL_HOUSE;
	} else if (matchCount == 1) {
		judgeResult |= D_POKER_HAND_THREE_CARD;
	} else {
		judgeResult |= D_POKER_HAND_ONE_PAIR;
	}

	return judgeResult;
}

POKER_HAND poker_judgePair(HAND_CARD card)
{
	if (poker_hasJoker(card) == E_FALSE) {
		return poker_judgePairWithoutJoker(card);
	} else {
		poker_removeJoker(&card);
		return poker_judgePairWithJoker(card);
	}
}

E_BOOL poker_validCard(HAND_CARD card)
{
	if (card.num < D_POKER_HAND_CARD_MAX) {
		M_ERROR("cards is small.\n");
		return E_FALSE;
	}
	U1 i = 0;
	for (i = 0; i < card.num; i++) {
		if (card.id[i] == 0x00) {
			M_ERROR("invalid card.\n");
			return E_FALSE;
		}
	}

	return E_TRUE;
}

POKER_HAND poker_judgment(HAND_CARD card)
{
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	if (poker_validCard(card) == E_FALSE) {
		M_ERROR("card error.\n");
		return judgeResult;
	}
	card_bubbleSort(&card);
	
	if (poker_isFlash(card) == E_TRUE) {
		judgeResult |= poker_judgeRoyalStraightFlash(card);
		judgeResult |= poker_judgeStraightFlash(card);
		judgeResult |= D_POKER_HAND_FLASH;
	} else if (poker_isStraight(card) == E_TRUE) {
		judgeResult |= D_POKER_HAND_STRAIGHT;
	} else {
		judgeResult |= poker_judgePair(card);
	}

	return judgeResult;
}

C1* debug_print_mark(CID cid)
{
	switch (M_CARD_MARK_ID(cid)) {
		case D_CARD_MARK_SPADE:		return D_CARD_MARK_SPADE_S;
		case D_CARD_MARK_HEART:		return D_CARD_MARK_HEART_S;
		case D_CARD_MARK_CLOVER:	return D_CARD_MARK_CLOVER_S;
		case D_CARD_MARK_DIAMOND:	return D_CARD_MARK_DIAMOND_S;
		default:					return D_CARD_MARK_JOKER_S;
	}
}


void debug_print_card()
{
	U1 i = 0;
	for (i = s_card.startIndex; i < s_card.remainingNumber; i++) {
		printf("Number=%2d, Mark=%s\n", M_CARD_NUMBER(s_card.id[i]), M_CARD_MARK(s_card.id[i]));
	}
}

void debug_print_hand()
{
	U1 i = 0;
	for (i = 0; i < s_handCard.num; i++) {
		printf("Number=%2d, Mark=%s\n", M_CARD_NUMBER(s_handCard.id[i]), M_CARD_MARK(s_handCard.id[i]));
	}
}

#define D_POKER_HAND_ENABLE_BIT		(0x01)
U1 poker_handNumber(POKER_HAND pokerHand)
{
	U1 i = 0;
	for (i = 0; i < D_POKER_HAND_TYPE_MAX - 1; i++) {
		if ((pokerHand & D_POKER_HAND_ENABLE_BIT) == D_POKER_HAND_ENABLE_BIT) {
			return i;
		}
		pokerHand >>= 1;
	}
	return i;
}

void debug_judgeResult(POKER_HAND pokerHand)
{
	const C1 *hand[D_POKER_HAND_TYPE_MAX] = {
		"Royal Straight Flash",
		"Five Card",
		"Straight Flash",
		"Four Card",
		"Full House",
		"Flash",
		"Straight",
		"Three Card",
		"Two Pair",
		"One Pair",
		"Buhi",
	};
	U1 handNumber = poker_handNumber(pokerHand);
	printf("handNumber = %d\n",handNumber);
	printf("Result (0x%04x)[%s]\n",pokerHand ,hand[handNumber]);
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	
	card_outOfBox();
	// debug_print_card();
	card_shuffle();
	// debug_print_card();
	// card_shuffle();
	// debug_print_card();

	player_receiveCard(card_deal());
	player_receiveCard(card_deal());
	player_receiveCard(card_deal());
	player_receiveCard(card_deal());
	player_receiveCard(card_deal());
	// player_receiveCard(card_deal());
	debug_print_hand();
	// player_sort();
	// debug_print_hand();

	POKER_HAND judgeResult = poker_judgment(player_handCard());
	debug_judgeResult(judgeResult);
	player_sort();
	debug_print_hand();

	return 0;
}
