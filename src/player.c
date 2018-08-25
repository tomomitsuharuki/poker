/**
 * @brief Playerクラス
 * 
 * @file player.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include <string.h>
#include "common.h"
#include "player.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(format, ...)		M_DEBUG_ERROR(D_DEBUG_CLASS_PLAYER, format, ## __VA_ARGS__)
#define M_ENTRY(format, ...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_PLAYER, format, ## __VA_ARGS__)
#define M_INFO(format, ...)			M_DEBUG_INFO(D_DEBUG_CLASS_PLAYER, format, ## __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
#define D_PLAYER_CHANGE_CARD_MAX				(5)

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/
/** @var 	s_handCard
 *  @brief	手札情報
*/
HAND_CARD s_handCard = {};

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	外部公開関数																				*/
/************************************************************************************************/
/**
 * @brief	カードを1枚もらう
 * @note	カード情報を取得する
 *
 * @param[in]	id	カード情報
 */
void player_receiveCard(CID id)
{
	M_ENTRY();
	if (s_handCard.num >= D_POKER_HAND_CARD_MAX) {
		M_ERROR("maximum number of cards.\n");
		return;
	}
	s_handCard.id[s_handCard.num] = id;
	s_handCard.num ++;
}

/**
 * @brief	手札を出す
 * @note	手札情報を出力する
 *
 * @return
 * |値 | 説明 |
 * |---|------|
 * | HAND_CARD |手札情報|
 */
HAND_CARD player_handCard(void)
{
	M_ENTRY();
	return s_handCard;
}

/**
 * @brief	手札を戻す
 * @note	手札情報を初期化する
 */
void player_restoreCard(void)
{
	M_ENTRY();
	memset(&s_handCard, 0, sizeof(s_handCard));
}

/**
 * @brief	取り替えたいカードを決める
 * @note	カード取り換え情報を設定する
 *
 * @param[in]	cardIndex	手札の番号
 */
void player_selectCard(U1 cardIndex)
{
	M_ENTRY("cardIndex=%d",cardIndex);
	/* すでに2枚選択中の場合は、最初から選択 */
	U1 selectedNum = player_changeCardNum();
	if (selectedNum >= D_PLAYER_CHANGE_CARD_MAX) {
		memset(&(s_handCard.change), E_CARD_CHANGE_NOT_SELECT, sizeof(s_handCard.change));
	}

	if (cardIndex > s_handCard.num) {
		M_ERROR("cardIndex Error:%d\n",cardIndex);
	}
	/* 指定されたカードを選択状態にする */
	s_handCard.change[cardIndex] = E_CARD_CHANGE_SELECTED;
}

/**
 * @brief	取り替えるカードの枚数を取得
 * @note	カード取り換え情報の数を返す
 *
 * @return	入力したコード
 */
U1 player_changeCardNum(void)
{
	M_ENTRY();
	U1 selectedNum = 0;
	U1 i = 0;
	for (i = 0; i < s_handCard.num; i++) {
		if (s_handCard.change[i] == E_CARD_CHANGE_SELECTED) {
			selectedNum ++;
		}
	}
	return selectedNum;
}

/**
 * @brief	カードを1枚取り替える
 * @note	カード取り換え情報が選択中のカードを取り替える
 *
 * @param[in]	id	カード情報
 */
void player_changeCard(CID id)
{
	M_ENTRY();
	U1 i = 0;
	for (i = 0; i < s_handCard.num; i++) {
		if (s_handCard.change[i] == E_CARD_CHANGE_SELECTED) {
			s_handCard.id[i] = id;
			s_handCard.change[i] = E_CARD_CHANGE_NOT_SELECT;
			return;
		}
	}
	M_ERROR("Not Changed");
}

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
