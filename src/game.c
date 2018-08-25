/**
 * @brief Gameクラス
 * 
 * @file game.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "game.h"
#include "card.h"
#include "player.h"
#include "poker.h"
#include "ui.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(format, ...)		M_DEBUG_ERROR(D_DEBUG_CLASS_GAME, format, ## __VA_ARGS__)
#define M_ENTRY(format, ...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_GAME, format, ## __VA_ARGS__)
#define M_INFO(format, ...)			M_DEBUG_INFO(D_DEBUG_CLASS_GAME, format, ## __VA_ARGS__)

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/
/**
 * @enum	E_MAIN_GAME_TYPE
 * @brief	Bool型
 */
typedef enum {
	E_MAIN_GAME_QUIT,
	E_MAIN_GAME_ROOKIE,
	E_MAIN_GAME_ROOKIE2,
	E_MAIN_GAME_MIDDLE,
	E_MAIN_GAME_LEGEND,
} E_MAIN_GAME_TYPE;

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/
static E_BOOL game_executeRookie(void);
static E_BOOL game_executeRookiePlus(void);
static E_MAIN_GAME_TYPE game_selectMainGame(void);

/************************************************************************************************/
/*	外部公開関数																				*/
/************************************************************************************************/
/**
 * @brief	ゲームを開始する
 * @note	
 */
void game_start(void)
{
	M_ENTRY();
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		E_MAIN_GAME_TYPE gameType = game_selectMainGame();
		switch (gameType) {
		case E_MAIN_GAME_ROOKIE:
			continueGame = game_executeRookie();
			break;
		case E_MAIN_GAME_ROOKIE2:
			continueGame = game_executeRookiePlus();
			break;
		case E_MAIN_GAME_MIDDLE:
			continueGame = game_executeRookie();
			break;
		case E_MAIN_GAME_LEGEND:
			continueGame = game_executeRookie();
			break;
		case E_MAIN_GAME_QUIT:
		default:
			continueGame = E_FALSE;
			break;
		}
	}
}


/************************************************************************************************/
/*	内部関数																					*/
/************************************************************************************************/
/**
 * @brief	メインゲームを選択する
 * @note	[ルーキー・ミドル・レジェンド]から選択する
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_MAIN_GAME_ROOKIE |ルーキー|
 * | E_MAIN_GAME_MIDDLE |ミドル|
 * | E_MAIN_GAME_LEGEND |レジェンド|
 * | E_MAIN_GAME_QUIT; |ゲームを終了する|
 */
static E_MAIN_GAME_TYPE game_selectMainGame(void)
{
	M_ENTRY();
	E_MAIN_GAME_TYPE gameType = E_MAIN_GAME_QUIT;

	ui_showMenu(E_UI_MENU_MAIN);
	E_UI_SELECT_CODE selectCode = ui_getSelectCode();	
	switch (selectCode) {
	case E_UI_1:
		gameType = E_MAIN_GAME_ROOKIE;
		break;
	case E_UI_2:
		gameType = E_MAIN_GAME_ROOKIE2;
		break;
	case E_UI_3:
		gameType = E_MAIN_GAME_MIDDLE;
		break;
	case E_UI_4:
		gameType = E_MAIN_GAME_LEGEND;
		break;
	default:
		gameType = E_MAIN_GAME_QUIT;
		break;
	}
	return gameType;
}

/**
 * @brief	ルーキーモード開始
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static E_BOOL game_executeRookie(void)
{
	M_ENTRY();
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenu(E_UI_MENU_ROOKIE);
		E_UI_SELECT_CODE selectCode = ui_getSelectCode();
		if (selectCode != E_UI_1) {
			continueGame = E_FALSE;
			continue;
		}

		/* カードを箱から出す */
		card_outOfBox(E_FALSE);
		/* シャッフル */
		card_shuffle();
		card_shuffle();
		/* カードを配って手札にする */
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		/* 手札を出す */
		HAND_CARD handCard = player_handCard();
		POKER_HAND judgeResult = poker_judgment(handCard);
		/* 結果を表示する */
		ui_showPokerResult(handCard, judgeResult);
		ui_pleaseEnterSomething();
	}
	return continueGame;
}

/**
 * @brief	ルーキーモード開始+α
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static E_BOOL game_executeRookiePlus(void)
{
	M_ENTRY();
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenu(E_UI_MENU_ROOKIE2);
		E_UI_SELECT_CODE selectCode = ui_getSelectCode();
		if (selectCode != E_UI_1) {
			continueGame = E_FALSE;
			continue;
		}

		/* カードを箱から出す */
		card_outOfBox(E_TRUE);
		/* シャッフル */
		card_shuffle();
		card_shuffle();
		/* カードを配って手札にする */
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		player_receiveCard(card_deal());
		/* 手札を出す */
		HAND_CARD handCard = player_handCard();
		POKER_HAND judgeResult = poker_judgment(handCard);
		/* 結果を表示する */
		ui_showPokerResult(handCard, judgeResult);
		ui_pleaseEnterSomething();
	}
	return continueGame;
}
