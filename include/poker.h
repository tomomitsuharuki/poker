/**
 * @brief Pokerクラスヘッダー
 * 
 * @file poker.h
 */
#ifndef __POKER_H__
#define __POKER_H__

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "player.h"

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
/*	構造体定義																					*/
/************************************************************************************************/

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/

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
POKER_HAND poker_judgment(HAND_CARD card);



#endif /* __POKER_H__ */