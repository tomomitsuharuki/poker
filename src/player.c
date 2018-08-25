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
#define M_ERROR(...)		M_DEBUG_ERROR(D_DEBUG_CLASS_PLAYER, __VA_ARGS__)
#define M_ENTRY(...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_PLAYER, __VA_ARGS__)
#define M_INFO(...)			M_DEBUG_INFO(D_DEBUG_CLASS_PLAYER, __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

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
	HAND_CARD handCard = s_handCard;
	memset(&s_handCard, 0, sizeof(s_handCard));
	return handCard;
}

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
