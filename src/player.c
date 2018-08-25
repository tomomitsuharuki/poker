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
HAND_CARD s_handCard[E_PLAYER_MODE_MAX] = {};

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
 * @param[in]	player	プレイヤー情報
 * @param[in]	id		カード情報
 */
void player_receiveCard(E_PLAYER_MODE player, CID id)
{
	M_ENTRY();
	if (s_handCard[player].num >= D_POKER_HAND_CARD_MAX) {
		M_ERROR("maximum number of cards.\n");
		return;
	}
	s_handCard[player].id[s_handCard[player].num] = id;
	s_handCard[player].num ++;
}

/**
 * @brief	手札を出す
 * @note	手札情報を出力する
 *
 * @param[in]	player	プレイヤー情報
 * @return
 * |値 | 説明 |
 * |---|------|
 * | HAND_CARD |手札情報|
 */
HAND_CARD player_handCard(E_PLAYER_MODE player)
{
	M_ENTRY();
	return s_handCard[player];
}

/**
 * @brief	手札を戻す
 * @note	手札情報を初期化する
 * @param[in]	player	プレイヤー情報
 */
void player_restoreCard(E_PLAYER_MODE player)
{
	M_ENTRY();
	memset(&s_handCard[player], 0, sizeof(s_handCard[player]));
}

/**
 * @brief	取り替えたいカードを決める
 * @note	カード取り換え情報を設定する
 *
 * @param[in]	player	プレイヤー情報
 * @param[in]	cardIndex	手札の番号
 */
void player_selectCard(E_PLAYER_MODE player, U1 cardIndex)
{
	M_ENTRY("cardIndex=%d",cardIndex);
	if (cardIndex > s_handCard[player].num) {
		M_ERROR("cardIndex Error:%d\n",cardIndex);
	}
	/* 指定されたカードを選択状態にする */
	/* 選択済みの場合は解除する */
	if (s_handCard[player].change[cardIndex] == E_CARD_CHANGE_NOT_SELECT) {
		s_handCard[player].change[cardIndex] = E_CARD_CHANGE_SELECTED;
	} else {
		s_handCard[player].change[cardIndex] = E_CARD_CHANGE_NOT_SELECT;
	}
}

/**
 * @brief	取り替えるカードの枚数を取得
 * @note	カード取り換え情報の数を返す
 *
 * @param[in]	player	プレイヤー情報
 * @return	入力したコード
 */
U1 player_changeCardNum(E_PLAYER_MODE player)
{
	M_ENTRY();
	U1 selectedNum = 0;
	U1 i = 0;
	for (i = 0; i < s_handCard[player].num; i++) {
		if (s_handCard[player].change[i] == E_CARD_CHANGE_SELECTED) {
			selectedNum ++;
		}
	}
	return selectedNum;
}

/**
 * @brief	カードを1枚取り替える
 * @note	カード取り換え情報が選択中のカードを取り替える
 *
 * @param[in]	player	プレイヤー情報
 * @param[in]	id	カード情報
 */
void player_changeCard(E_PLAYER_MODE player, CID id)
{
	M_ENTRY();
	U1 i = 0;
	for (i = 0; i < s_handCard[player].num; i++) {
		if (s_handCard[player].change[i] == E_CARD_CHANGE_SELECTED) {
			s_handCard[player].id[i] = id;
			s_handCard[player].change[i] = E_CARD_CHANGE_NOT_SELECT;
			return;
		}
	}
	M_ERROR("Not Changed");
}

/**
 * @brief	取り替えるカードを選択する
 * @note	COM用
 *
 * @param[in]	player	プレイヤー情報
 */
E_UI_SELECT_CODE player_selectCardForCOM(E_PLAYER_MODE player)
{
	if ((player == E_PLAYER_1) || (player == E_PLAYER_2)) {
		return E_UI_OTHER;
	}
	if (player == E_PLAYER_COM_EASY) {
		return E_UI_OTHER;
	}

	/* レジェンドモード：AI機能 */
	/* s_handCard[player].id[0-4] からいらないカードを選択する */
	/* Coming Soon ... sorry */
	return E_UI_OTHER;
}

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
