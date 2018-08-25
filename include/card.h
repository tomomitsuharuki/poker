/**
 * @brief Cardクラスヘッダー
 * 
 * @file card.h
 */
#ifndef __CARD_H__
#define __CARD_H__

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
/** @name カード基本情報
 */
/*@{*/
#define D_CARD_NUMBER				(13)
#define D_CARD_MARK					(4)
#define D_CARD_NUM_MAX				(D_CARD_NUMBER * D_CARD_MARK + 1)
/*@}*/

/** @name カードマーク情報
 */
/*@{*/
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
/*@}*/

/** @def
 * カードIDからカード番号を取得
 */
#define M_CARD_NUMBER_ID(cid)		(cid & 0x0F)
/** @def
 * カードIDからマーク種別を取得
 */
#define M_CARD_MARK_ID(cid)			(cid & 0xF0)

// #define M_CARD_NUMBER(cid)			((cid & 0x0F) + 1)
// #define M_CARD_MARK(cid)			debug_print_mark(cid)

/************************************************************************************************/
/*	構造体定義																					*/
/************************************************************************************************/
/**
 * @struct	CARD
 * @brief	カード情報構造体
 */
typedef struct {
	CID	id[D_CARD_NUM_MAX];
	U1	startIndex;
	U1	remainingNumber;
} CARD;

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/

/**
 * @brief	カードを箱から出す
 * @note	カード情報を初期化する
 *
 * @param[in]	withJoker	Jokerの有無
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |Jokerを入れる|
 * | E_FALSE |Jokerを入れない|
 */
void card_outOfBox(E_BOOL withJoker);

/**
 * @brief	カードをシャッフルする
 * @note	カード情報をランダムに並べる
 *
 */
void card_shuffle(void);

/**
 * @brief	カードを1枚配る
 * @note	カード情報を1つ出力する
 *
 * @return
 * |値 | 説明 |
 * |---|------|
 * | CID |カードID|
 */
CID card_deal(void);




#endif /* __CARD_H__ */