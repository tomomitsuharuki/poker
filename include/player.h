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
 * @enum	E_CARD_CHANGE
 * @brief	カード取り替え情報
 */
typedef enum {
	E_CARD_CHANGE_NOT_SELECT,
	E_CARD_CHANGE_SELECTED,
} E_CARD_CHANGE;

/**
 * @struct	HAND_CARD
 * @brief	手札情報構造体
 */
typedef struct {
	U1	num;
	CID	id[D_POKER_HAND_CARD_MAX];
	E_CARD_CHANGE change[D_POKER_HAND_CARD_MAX];
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
 */
void player_restoreCard(void);

/**
 * @brief	取り替えたいカードを決める
 * @note	カード取り換え情報を設定する
 *
 * @param[in]	cardIndex	手札の番号
 */
void player_selectCard(U1 cardIndex);

/**
 * @brief	取り替えるカードの枚数を取得
 * @note	カード取り換え情報の数を返す
 *
 * @return	入力したコード
 */
U1 player_changeCardNum(void);

/**
 * @brief	カードを1枚取り替える
 * @note	カード取り換え情報が選択中のカードを取り替える
 *
 * @param[in]	id	カード情報
 */
void player_changeCard(CID id);

#endif /* __PLAYER_H__ */