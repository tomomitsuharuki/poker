/**
 * @brief Cardクラス
 * 
 * @file card.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "card.h"
#include "system.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(...)		M_DEBUG_ERROR(D_DEBUG_CLASS_CARD, __VA_ARGS__)
#define M_ENTRY(...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_CARD, __VA_ARGS__)
#define M_INFO(...)			M_DEBUG_INFO(D_DEBUG_CLASS_CARD, __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/
/** @var 	s_card
 *  @brief	カード情報
*/
CARD s_card = {};

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/
static CARD _initialCard(void);
static void _plusJoker(void);
static void _fisherYatesShuffle(CID id[], U1 size);

/************************************************************************************************/
/*	外部公開関数																				*/
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
void card_outOfBox(E_BOOL withJoker)
{
	M_ENTRY();
	s_card = _initialCard();
	if (withJoker == E_TRUE) {
		_plusJoker();
	}
}

/**
 * @brief	カードをシャッフルする
 * @note	カード情報をランダムに並べる
 *
 */
void card_shuffle(void)
{
	M_ENTRY();
	_fisherYatesShuffle(&(s_card.id[s_card.startIndex]), s_card.remainingNumber);
}

/**
 * @brief	カードを1枚配る
 * @note	カード情報を1つ出力する
 *
 * @return
 * |値 | 説明 |
 * |---|------|
 * | CID |カードID|
 */
CID card_deal(void)
{
	M_ENTRY();
	CID dealCard = s_card.id[s_card.startIndex];
	s_card.startIndex ++;
	s_card.remainingNumber --;
	return dealCard;
}

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
/**
 * @brief	初期状態カード情報を出力する
 * @note	
 *
 * @return	CARD	初期状態カード情報
 * @attention
 * 初期状態にはJokerは含まれません
 */
static CARD _initialCard(void)
{
	M_ENTRY();
	CARD initialCard = {
		{
			0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
			0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,
			0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
			0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D,
		},
		0,
		D_CARD_NUMBER * D_CARD_MARK,
	};
	return initialCard;
}

/**
 * @brief	Jokerを追加する
 * @note	Jokerのカード情報を追加します
 *
 */
static void _plusJoker(void)
{
	M_ENTRY();
	s_card.id[s_card.remainingNumber] = 0xFF;
	s_card.remainingNumber += 1;
}

/**
 * @brief	カード情報をシャッフルする
 * @note	 Fisher–Yates shuffle
 *
 * @param[in]	id[]	カード情報のポインタ
 * @param[in]	size	カード情報のサイズ
 */
static void _fisherYatesShuffle(CID id[], U1 size)
{
	M_ENTRY();
	system_random_init();
	U1 i = 0;
	for (i = 0; i < size; i++) {
		U1 j = system_random() % size;
		CID temp = id[i];
		id[i] = id[j];
		id[j] = temp;
	}
}
