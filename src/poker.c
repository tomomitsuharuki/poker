/**
 * @brief Pokerクラス
 * 
 * @file poker.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "player.h"
#include "card.h"
#include "poker.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(...)		M_DEBUG_ERROR(D_DEBUG_CLASS_POKER, __VA_ARGS__)
#define M_ENTRY(...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_POKER, __VA_ARGS__)
#define M_INFO(...)			M_DEBUG_INFO(D_DEBUG_CLASS_POKER, __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
/** @name ポーカーの役
 */
/*@{*/
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
/*@}*/

/** @name ロイヤルストレートフラッシュ判定のしきい値
 */
/*@{*/
#define D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITHOUT_J	(55)
#define D_POKER_JUDGE_ROYAL_STRAIGHT_FLASH_WITH_J		(42)
/*@}*/


/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/
static void poker_bubbleSort(HAND_CARD *card);
static E_BOOL poker_hasJoker(HAND_CARD card);
static void poker_removeJoker(HAND_CARD *card);
static E_BOOL poker_isFlash(HAND_CARD card);
static E_BOOL poker_isStraight(HAND_CARD card);
static E_BOOL poker_isStraightWithoutJoker(HAND_CARD card);
static E_BOOL poker_isStraightWithJoker(HAND_CARD card);
static POKER_HAND poker_judgeRoyalStraightFlash(HAND_CARD card);
static POKER_HAND poker_judgeStraightFlash(HAND_CARD card);
static POKER_HAND poker_judgePair(HAND_CARD card);
static POKER_HAND poker_judgePairWithoutJoker(HAND_CARD card);
static POKER_HAND poker_judgePairWithJoker(HAND_CARD card);
static CID poker_totalId(HAND_CARD card);

/************************************************************************************************/
/*	外部公開関数																				*/
/************************************************************************************************/
/**
 * @brief	手札の有効判定
 * @note	手札が揃っているかを判定する
 *
 * @param[in]	card	手札情報
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |有効な手札|
 * | E_FALSE |無効な手札|
 */
E_BOOL poker_validCard(HAND_CARD card)
{
	M_ENTRY();
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

/**
 * @brief	ポーカーの役を判定する
 * @note	役を判定して結果を出力する
 *
 * @param[in]	card	手札情報
 * @return
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |判定結果の役情報|
 */
POKER_HAND poker_judgment(HAND_CARD card)
{
	M_ENTRY();
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	if (poker_validCard(card) == E_FALSE) {
		M_ERROR("card error.\n");
		return judgeResult;
	}

	poker_bubbleSort(&card);
	
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

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
/**
 * @brief	手札を並べ替える
 * @note	Bubble sort
 *
 * @param[in,out]	card	手札情報
 */
static void poker_bubbleSort(HAND_CARD *card)
{
	M_ENTRY();
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

/**
 * @brief	Jokerの有無
 * @note	
 *
 * @param[in]	card	手札情報
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |Jokerあり|
 * | E_FALSE |Jokerなし|
 */
static E_BOOL poker_hasJoker(HAND_CARD card)
{
	M_ENTRY();
	if (M_CARD_MARK_ID(card.id[card.num-1]) == D_CARD_MARK_JOKER) {
		return E_TRUE;
	} else {
		return E_FALSE;
	}
}

/**
 * @brief	Jokerを外す
 * @note	
 *
 * @param[in]	card	手札情報
 * @attention
 * Jokerを外すと手札が4枚になります
 */
static void poker_removeJoker(HAND_CARD *card)
{
	M_ENTRY();
	if (M_CARD_MARK_ID(card->id[card->num-1]) == D_CARD_MARK_JOKER) {
		card->num --;
	}
}

/**
 * @brief	【Flash】判定
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |【Flash】あり|
 * | E_FALSE |【Flash】なし|
 *
 * @attention
 * Jokerあり・なし両対応
 */
static E_BOOL poker_isFlash(HAND_CARD card)
{
	M_ENTRY();
	CID judgeMark = 0xF0;
	/* card.id[0] & card.id[1] & card.id[2] & card.id[3] & card.id[4] */
	U1 i = 0;
	for (i = 0; i < card.num; i++) {
		judgeMark &= M_CARD_MARK_ID(card.id[i]);
	}
	if ((judgeMark == D_CARD_MARK_SPADE) || 
		(judgeMark == D_CARD_MARK_HEART) || 
		(judgeMark == D_CARD_MARK_DIAMOND) || 
		(judgeMark == D_CARD_MARK_SPADE) ) {
		return E_TRUE;
	} else {
		return E_FALSE;
	}
}

/**
 * @brief	【Straight】判定
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |【Straight】あり|
 * | E_FALSE |【Straight】なし|
 * @attention
 * Jokerあり・なし両対応
 */
static E_BOOL poker_isStraight(HAND_CARD card)
{
	M_ENTRY();
	if (poker_hasJoker(card) == E_FALSE) {
		return poker_isStraightWithoutJoker(card);
	} else {
		poker_removeJoker(&card);
		return poker_isStraightWithJoker(card);
	}
}

/**
 * @brief	【Straight】判定(Jokerなし))
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |【Straight】あり|
 * | E_FALSE |【Straight】なし|
 * @attention
 * Jokerなしのみ対応
 */
static E_BOOL poker_isStraightWithoutJoker(HAND_CARD card)
{
	M_ENTRY();
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

/**
 * @brief	【Straight】判定(Jokerあり))
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |【Straight】あり|
 * | E_FALSE |【Straight】なし|
 * @attention
 * Jokerありのみ対応
 */
static E_BOOL poker_isStraightWithJoker(HAND_CARD card)
{
	M_ENTRY();
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

/**
 * @brief	【RoyalStraightFlash】判定
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |役判定結果|
 * @attention
 * Jokerあり・なし両対応
 */
static POKER_HAND poker_judgeRoyalStraightFlash(HAND_CARD card)
{
	M_ENTRY();
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

/**
 * @brief	【StraightFlash】判定
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |役判定結果|
 * @attention
 * Jokerあり・なし両対応
 */
static POKER_HAND poker_judgeStraightFlash(HAND_CARD card)
{
	M_ENTRY();
	POKER_HAND judgeResult = D_POKER_HAND_BUHI;
	if (poker_isStraight(card) == E_TRUE) {
		judgeResult |= D_POKER_HAND_STRAIGHT_FLASH;
	}
	return judgeResult;
}

/**
 * @brief	【Pair/FullHouse/Three,FourCard】判定
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |役判定結果|
 * @attention
 * Jokerあり・なし両対応
 */
static POKER_HAND poker_judgePair(HAND_CARD card)
{
	M_ENTRY();
	if (poker_hasJoker(card) == E_FALSE) {
		return poker_judgePairWithoutJoker(card);
	} else {
		poker_removeJoker(&card);
		return poker_judgePairWithJoker(card);
	}
}

/**
 * @brief	【Pair/FullHouse/Three,FourCard】判定(Jokerなし)
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |役判定結果|
 * @attention
 * Jokerなしのみ対応
 */
static POKER_HAND poker_judgePairWithoutJoker(HAND_CARD card)
{
	M_ENTRY();
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

/**
 * @brief	【Pair/FullHouse/Three,FourCard】判定(Jokerあり)
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | POKER_HAND |役判定結果|
 * @attention
 * Jokerありのみ対応
 */
static POKER_HAND poker_judgePairWithJoker(HAND_CARD card)
{
	M_ENTRY();
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
		judgeResult |= D_POKER_HAND_FIVE_CARD;
	} else if (matchCount >= 4) {
		M_ERROR("Judge error.\n");
		judgeResult |= D_POKER_HAND_BUHI;
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

/**
 * @brief	カード情報の合計値を取得する
 * @note	
 *
 * @param[in]	card	手札情報
 * |値 | 説明 |
 * |---|------|
 * | CID |カード情報の合計値|
 */
static CID poker_totalId(HAND_CARD card)
{
	M_ENTRY();
	CID totalId = 0;
	U1 i = 0;
	for (i = 0; i < card.num; i++) {
		totalId += M_CARD_NUMBER_ID(card.id[0]);
	}
	return totalId;
}
