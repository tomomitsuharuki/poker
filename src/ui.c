/**
 * @brief UIクラス
 * 
 * @file ui.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "card.h"
#include "player.h"
#include "ui.h"
#include "system.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(format, ...)		M_DEBUG_ERROR(D_DEBUG_CLASS_UI, format, ## __VA_ARGS__)
#define M_ENTRY(format, ...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_UI, format, ## __VA_ARGS__)
#define M_INFO(format, ...)			M_DEBUG_INFO(D_DEBUG_CLASS_UI, format, ## __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
#define D_UI_CONSOLE_BUFFER			(256)
#define D_UI_CONSOLE_IN_ERROR		(-1)
#define D_UI_BASE_10				(10)

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/
static void ui_showCard(CID id, U1 index);
static void ui_showHand(POKER_HAND pokerHand);
static void ui_out(C1 *str);
static E_UI_SELECT_CODE ui_in(C1 *str);

/************************************************************************************************/
/*	外部公開関数																				*/
/************************************************************************************************/
/**
 * @brief	画面クリア
 * @note	
 */
void ui_clear(void)
{
	M_ENTRY();
	system_clear();
}

/**
 * @brief	メニューを表示する
 * @note	コンソール向け
 */
void ui_showMenu(E_UI_MENU menuId)
{
	M_ENTRY();
	ui_clear();

	if (menuId == E_UI_MENU_MAIN) {
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("|                                                             |\n");
		ui_out("|    Main Menu                                                |\n");
		ui_out("|                                                             |\n");
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("\n");
		ui_out("< Select Mode >\n");
		ui_out("  <1> Rookie1 Game Mode\n");
		ui_out("  <2> Rookie2 Game Mode\n");
		ui_out("  <3> Middle Game Mode\n");
		ui_out("  <4> Legend Game Mode\n");
		ui_out("  <other> Quit\n");
	} else if (menuId == E_UI_MENU_ROOKIE) {
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("|                                                             |\n");
		ui_out("|    Rookie Menu                                              |\n");
		ui_out("|                                                             |\n");
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("\n");
		ui_out("< Do you accept 5 cards? >\n");
		ui_out("  <1> Yes\n");
		ui_out("  <other> Quit\n");
	} else if (menuId == E_UI_MENU_ROOKIE2) {
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("|                                                             |\n");
		ui_out("|    Rookie2 Menu(Single Poker)                               |\n");
		ui_out("|                                                             |\n");
		ui_out("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
		ui_out("\n");
		ui_out("< Do you accept 5 cards? >\n");
		ui_out("  <1> Yes\n");
		ui_out("  <other> Quit\n");
	} else {
		M_ERROR("menuId Error:%d\n",menuId);
	}
}

/**
 * @brief	手札を表示する
 * @note	
 *
 * @param[in]	pokerHand	手札情報
 */
void ui_showHandCard(HAND_CARD handCard)
{
	M_ENTRY();
	ui_out("\n");
	ui_out("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	ui_out("  <#> [    Mark :Number]\n");
	U1 i = 0;
	for (i = 0; i < handCard.num; i++) {
		ui_showCard(handCard.id[i], i);
	}
	ui_out("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

/**
 * @brief	ポーカーの役を表示する
 * @note	
 *
 * @param[in]	pokerHand	手札情報
 * @param[in]	pokerHand	ポーカーの役
 */
void ui_showPokerResult(HAND_CARD handCard, POKER_HAND pokerHand)
{
	M_ENTRY();
	ui_out("\n");
	ui_out("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	ui_out("  Result  \n");
	ui_out("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	ui_out("\n");

	U1 i = 0;
	for (i = 0; i < handCard.num; i++) {
		ui_showCard(handCard.id[i], i);
	}
	ui_out("\n");
	ui_showHand(pokerHand);
}

/**
 * @brief	ユーザーが入力したコードを取得する
 * @note	コンソール向け
 *
 * @return	入力したコード
 */
E_UI_SELECT_CODE ui_getSelectCode(void)
{
	M_ENTRY();
	return ui_in("Input select number ==> ");
}

/**
 * @brief	なにか入力してください。
 * @note	
 */
void ui_pleaseEnterSomething(void)
{
	char buffer[D_UI_CONSOLE_BUFFER] = {};
	ui_out("\n\nPlease enter something.....");
	fgets(buffer, D_UI_CONSOLE_BUFFER, stdin);
}

/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
/**
 * @brief	コンソール出力
 * @note	
 */
static void ui_out(C1 *str)
{
	printf("%s", str);
}

/**
 * @brief	コンソール入力
 * @note	str文字列出力後、ユーザー入力待ち状態
 *
 * @param[in]	str	出力文字列
 * @return	入力したコード
 */
static E_UI_SELECT_CODE ui_in(C1 *str)
{
	E_UI_SELECT_CODE selectCode = E_UI_ERROR;
	char buffer[D_UI_CONSOLE_BUFFER] = {};

	ui_out(str);
	if (fgets(buffer, D_UI_CONSOLE_BUFFER, stdin) == NULL) {
		M_ERROR("fgets is NULL\n");
		return selectCode;
	}
	if (buffer[0] == '\n') {
		selectCode = E_UI_RETURN;
		return selectCode;
	}

	long value = strtol(buffer, NULL, D_UI_BASE_10);
	switch (value) {
	case 1:
		selectCode = E_UI_1;
		break;
	case 2:
		selectCode = E_UI_2;
		break;
	case 3:
		selectCode = E_UI_3;
		break;
	case 4:
		selectCode = E_UI_4;
		break;
	case 5:
		selectCode = E_UI_5;
		break;
	default:
		selectCode = E_UI_OTHER;
		break;
	}

	return selectCode;
}

/**
 * @brief	手札を表示する
 * @note	
 *
 * @param[in]	id	カード情報
 */
static void ui_showCard(CID id, U1 index)
{
	/* M_ENTRY(); */
	const C1 *strMark[D_CARD_MARK+1] = { 
				D_CARD_MARK_DIAMOND_S,
				D_CARD_MARK_CLOVER_S,
				D_CARD_MARK_HEART_S,
				D_CARD_MARK_SPADE_S,
				D_CARD_MARK_JOKER_S,
			};
	const C1 *strNumber[D_CARD_NUMBER] = { " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K", " A" };

	CID mark = M_CARD_MARK_ID(id);
	CID number = M_CARD_NUMBER_ID(id) - 1;
	U1 markIndex = 0;
	switch (mark) {
	case D_CARD_MARK_DIAMOND:
		markIndex = 0;
		break;
	case D_CARD_MARK_CLOVER:
		markIndex = 1;
		break;
	case D_CARD_MARK_HEART:
		markIndex = 2;
		break;
	case D_CARD_MARK_SPADE:
		markIndex = 3;
		break;
	case D_CARD_MARK_JOKER:
	default:
		markIndex = 4;
		break;
	}

	// printf("  (0x%x)\n", id);
	if (mark == D_CARD_MARK_JOKER) {
		printf("  <%d> [%8s :--    ]\n", index, strMark[markIndex]);
	} else {
		printf("  <%d> [%8s :%s    ]\n", index, strMark[markIndex], strNumber[number]);
	}
}

#define D_POKER_HAND_TYPE_MAX						(11)
#define D_POKER_HAND_ENABLE_BIT						(0x01)
static U1 poker_handNumber(POKER_HAND pokerHand);

/**
 * @brief	ポーカーの役を表示する
 * @note	
 *
 * @param[in]	pokerHand	手札情報
 */
static void ui_showHand(POKER_HAND pokerHand)
{
	/* M_ENTRY(); */
	const C1 *hand[D_POKER_HAND_TYPE_MAX] = {
		"Royal Straight Flash",
		"Five Card",
		"Straight Flash",
		"Four Card",
		"Full House",
		"Flash",
		"Straight",
		"Three Card",
		"Two Pair",
		"One Pair",
		"Buhi",
	};
	U1 handNumber = poker_handNumber(pokerHand);
	// printf("handNumber = %d\n",handNumber);
	printf("   <<<%s>>>\n" ,hand[handNumber]);
}

static U1 poker_handNumber(POKER_HAND pokerHand)
{
	/* M_ENTRY(); */
	U1 i = 0;
	for (i = 0; i < D_POKER_HAND_TYPE_MAX - 1; i++) {
		if ((pokerHand & D_POKER_HAND_ENABLE_BIT) == D_POKER_HAND_ENABLE_BIT) {
			return i;
		}
		pokerHand >>= 1;
	}
	return i;
}

