/**
 * @brief Playerクラスヘッダー
 * 
 * @file player.h
 */
#ifndef __PLAYER_H__
#define __PLAYER_H__

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

/** @name 手札情報
 */
/*@{*/
#define D_POKER_HAND_CARD_MAX			(5)
/*@}*/

/************************************************************************************************/
/*	構造体定義																					*/
/************************************************************************************************/
/**
 * @struct	HAND_CARD
 * @brief	手札情報構造体
 */
typedef struct {
	CID	id[D_POKER_HAND_CARD_MAX];
	U1	num;
} HAND_CARD;

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/

/**
 * @brief	カードを1枚もらう
 * @note	カード情報を取得する
 *
 * @param[in]	id	カード情報
 */
void player_receiveCard(CID id);

/**
 * @brief	手札を出す
 * @note	手札情報を出力する
 *
 * @return
 * |値 | 説明 |
 * |---|------|
 * | HAND_CARD |手札情報|
 */
HAND_CARD player_handCard(void);

/**
 * @brief	手札を戻す
 * @note	手札情報を初期化する
 *
 * @return
 * |値 | 説明 |
 * |---|------|
 * | HAND_CARD |手札情報|
 */
HAND_CARD player_restoreCard(void);


#endif /* __PLAYER_H__ */