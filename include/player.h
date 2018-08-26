/**
 * @class Playerクラス
 * @brief Playerクラス
 * ゲームプレイヤーを管理します
 * 対人用・COM用に対応します
 * @note
 * 本来は、対人用COM用に継承してインスタンス化して使用したいところです
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
 * @param[in]	player	プレイヤー情報
 * @param[in]	id		カード情報
 */
void player_receiveCard(E_PLAYER_MODE player, CID id);

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
HAND_CARD player_handCard(E_PLAYER_MODE player);

/**
 * @brief	手札を戻す
 * @note	手札情報を初期化する
 * @param[in]	player	プレイヤー情報
 */
void player_restoreCard(E_PLAYER_MODE player);

/**
 * @brief	取り替えたいカードを決める
 * @note	カード取り換え情報を設定する
 *
 * @param[in]	player	プレイヤー情報
 * @param[in]	cardIndex	手札の番号
 */
void player_selectCard(E_PLAYER_MODE player, U1 cardIndex);

/**
 * @brief	取り替えるカードの枚数を取得
 * @note	カード取り換え情報の数を返す
 *
 * @param[in]	player	プレイヤー情報
 * @return	入力したコード
 */
U1 player_changeCardNum(E_PLAYER_MODE player);

/**
 * @brief	カードを1枚取り替える
 * @note	カード取り換え情報が選択中のカードを取り替える
 *
 * @param[in]	player	プレイヤー情報
 * @param[in]	id	カード情報
 */
void player_changeCard(E_PLAYER_MODE player, CID id);

/**
 * @brief	取り替えるカードを選択する
 * @note	COM用
 *
 * @param[in]	player	プレイヤー情報
 */
E_UI_SELECT_CODE player_selectCardForCOM(E_PLAYER_MODE player);

#endif /* __PLAYER_H__ */