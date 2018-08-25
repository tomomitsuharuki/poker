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
	E_MAIN_GAME_MIDDLE1,
	E_MAIN_GAME_MIDDLE2,
	E_MAIN_GAME_MIDDLE3,
	E_MAIN_GAME_LEGEND,
} E_MAIN_GAME_TYPE;

/************************************************************************************************/
/*	クラス内参照メンバー変数																	*/
/************************************************************************************************/

/************************************************************************************************/
/*	内部関数プロトタイプ宣言																	*/
/************************************************************************************************/
static E_MAIN_GAME_TYPE game_selectMainGame(void);
static E_BOOL game_executeRookie(void);
static E_BOOL game_executeMiddle1(void);
static E_BOOL game_executeGame(E_UI_MENU gameMode, E_PLAYER_MODE player1, E_PLAYER_MODE player2, E_BOOL withJoker);
static void game_executeGameDeal(E_PLAYER_MODE player);
static void game_executeGameSelect(E_UI_MENU gameMode, E_PLAYER_MODE player);
static void game_executeGameChange(E_PLAYER_MODE player);

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
		case E_MAIN_GAME_MIDDLE1:
			continueGame = game_executeMiddle1();
			break;
		case E_MAIN_GAME_MIDDLE2:
		{
			E_UI_MENU gameMode = E_UI_MENU_MIDDLE2;
			E_PLAYER_MODE player1 = E_PLAYER_1;
			E_PLAYER_MODE player2 = E_PLAYER_2;
			E_BOOL withJoker = E_FALSE;
			continueGame = game_executeGame(gameMode, player1, player2, withJoker);
		} break;
		case E_MAIN_GAME_MIDDLE3:
		{
			E_UI_MENU gameMode = E_UI_MENU_MIDDLE3;
			E_PLAYER_MODE player1 = E_PLAYER_1;
			E_PLAYER_MODE player2 = E_PLAYER_COM_EASY;
			E_BOOL withJoker = E_FALSE;
			continueGame = game_executeGame(gameMode, player1, player2, withJoker);
		} break;
		case E_MAIN_GAME_LEGEND:
		{
			E_UI_MENU gameMode = E_UI_MENU_LEGEND;
			E_PLAYER_MODE player1 = E_PLAYER_1;
			E_PLAYER_MODE player2 = E_PLAYER_COM_NORMAL;
			E_BOOL withJoker = E_TRUE;
			continueGame = game_executeGame(gameMode, player1, player2, withJoker);
		} break;
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

	ui_showMenuTitle(E_UI_MENU_MAIN);
	ui_showMenu(E_UI_MENU_MAIN);
	E_UI_SELECT_CODE selectCode = ui_getSelectCode();	
	switch (selectCode) {
	case E_UI_1:
		gameType = E_MAIN_GAME_ROOKIE;
		break;
	case E_UI_2:
		gameType = E_MAIN_GAME_MIDDLE1;
		break;
	case E_UI_3:
		gameType = E_MAIN_GAME_MIDDLE2;
		break;
	case E_UI_4:
		gameType = E_MAIN_GAME_MIDDLE3;
		break;
	case E_UI_5:
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
	E_PLAYER_MODE rookie = E_PLAYER_1;
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenuTitle(E_UI_MENU_ROOKIE);
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
		player_receiveCard(rookie, card_deal());
		player_receiveCard(rookie, card_deal());
		player_receiveCard(rookie, card_deal());
		player_receiveCard(rookie, card_deal());
		player_receiveCard(rookie, card_deal());
		/* 手札を出す */
		HAND_CARD handCard = player_handCard(rookie);
		POKER_HAND judgeResult = poker_judgment(handCard);
		/* 結果を表示する */
		ui_showHandCard(handCard);
		ui_showPokerResult(judgeResult);
		ui_pleaseEnterSomething();
		/* 手札を戻す */
		player_restoreCard(rookie);
	}
	return continueGame;
}

/**
 * @brief	ミドルモード開始
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static E_BOOL game_executeMiddle1(void)
{
	M_ENTRY();
	E_PLAYER_MODE single = E_PLAYER_1;
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenuTitle(E_UI_MENU_MIDDLE1);
		ui_showMenu(E_UI_MENU_MIDDLE1);
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
		player_receiveCard(single, card_deal());
		player_receiveCard(single, card_deal());
		player_receiveCard(single, card_deal());
		player_receiveCard(single, card_deal());
		player_receiveCard(single, card_deal());

		E_BOOL finishSelect = E_TRUE;
		while(finishSelect == E_TRUE) {
			/* タイトル表示 */
			ui_showMenuTitle(E_UI_MENU_MIDDLE1);
			/* 手札を出す */
			HAND_CARD handCard = player_handCard(single);
			ui_showHandCard(handCard);
			/* カード交換選択 */
			E_UI_SELECT_CODE selectCode = ui_getSelectCode();
			M_INFO("selectCode=%d",selectCode);
			if ((E_UI_1 <= selectCode) && (selectCode <= E_UI_5)) {
				U1 changeCardIndex = selectCode - 1;
				player_selectCard(single, changeCardIndex);
			} else {
				finishSelect = E_FALSE;
			}
		}
		/* カード交換 */
		U1 changeNum = player_changeCardNum(single);
		U1 i = 0;
		for (i = 0; i < changeNum; i++) {
			player_changeCard(single, card_deal());
		}
		/* 結果を表示する */
		HAND_CARD handCard = player_handCard(single);
		POKER_HAND judgeResult = poker_judgment(handCard);
		ui_showHandCard(handCard);
		ui_showPokerResult(judgeResult);
		ui_pleaseEnterSomething();
		/* 手札を戻す */
		player_restoreCard(single);
	}
	return continueGame;
}

#if 0
/**
 * @brief	ミドルモード開始
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static E_BOOL game_executeMiddle2(void)
{
	M_ENTRY();
	E_PLAYER_MODE player1 = E_PLAYER_1;
	E_PLAYER_MODE player2 = E_PLAYER_2;
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenuTitle(E_UI_MENU_MIDDLE2);
		ui_showMenu(E_UI_MENU_MIDDLE2);
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
		/* Player1 */
		player_receiveCard(player1, card_deal());
		player_receiveCard(player1, card_deal());
		player_receiveCard(player1, card_deal());
		player_receiveCard(player1, card_deal());
		player_receiveCard(player1, card_deal());
		/* Player2 */
		player_receiveCard(player2, card_deal());
		player_receiveCard(player2, card_deal());
		player_receiveCard(player2, card_deal());
		player_receiveCard(player2, card_deal());
		player_receiveCard(player2, card_deal());

		/* Player1 */
		E_BOOL finishSelect = E_TRUE;
		while(finishSelect == E_TRUE) {
			/* タイトル表示 */
			ui_showMenuTitle(E_UI_MENU_MIDDLE2);
			ui_showSubTitle(player1);
			/* 手札を出す */
			HAND_CARD handCard = player_handCard(player1);
			ui_showHandCard(handCard);
			/* カード交換選択 */
			E_UI_SELECT_CODE selectCode = ui_getSelectCode();
			M_INFO("selectCode=%d",selectCode);
			if ((E_UI_1 <= selectCode) && (selectCode <= E_UI_5)) {
				U1 changeCardIndex = selectCode - 1;
				player_selectCard(player1, changeCardIndex);
			} else {
				finishSelect = E_FALSE;
			}
		}

		/* Player2 */
		finishSelect = E_TRUE;
		while(finishSelect == E_TRUE) {
			/* タイトル表示 */
			ui_showMenuTitle(E_UI_MENU_MIDDLE2);
			ui_showSubTitle(player2);
			/* 手札を出す */
			HAND_CARD handCard = player_handCard(player2);
			ui_showHandCard(handCard);
			/* カード交換選択 */
			E_UI_SELECT_CODE selectCode = ui_getSelectCode();
			M_INFO("selectCode=%d",selectCode);
			if ((E_UI_1 <= selectCode) && (selectCode <= E_UI_5)) {
				U1 changeCardIndex = selectCode - 1;
				player_selectCard(player2, changeCardIndex);
			} else {
				finishSelect = E_FALSE;
			}
		}

		/* カード交換：Player1 */
		U1 changeNum = player_changeCardNum(player1);
		U1 i = 0;
		for (i = 0; i < changeNum; i++) {
			player_changeCard(player1, card_deal());
		}
		/* カード交換：Player2 */
		changeNum = player_changeCardNum(player2);
		i = 0;
		for (i = 0; i < changeNum; i++) {
			player_changeCard(player2, card_deal());
		}

		ui_showMenuTitle(E_UI_MENU_MIDDLE2);
		/* 結果を表示する */
		HAND_CARD handCard1 = player_handCard(player1);
		HAND_CARD handCard2 = player_handCard(player2);
		POKER_HAND judgeResult1 = poker_judgment(handCard1);
		POKER_HAND judgeResult2 = poker_judgment(handCard2);
		ui_showSubTitle(player1);
		ui_showHandCard(handCard1);
		ui_showSubTitle(player2);
		ui_showHandCard(handCard2);
		E_POKER_COMP_RESULT compResult = poker_judgmentComp(handCard1, handCard2);
		ui_showPokerResult2(judgeResult1, judgeResult2, compResult);

		ui_pleaseEnterSomething();
		/* 手札を戻す */
		player_restoreCard(player1);
		player_restoreCard(player2);
	}
	return continueGame;
}
#endif

/**
 * @brief	ゲーム開始(ミドル・レジェンドモード)
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static E_BOOL game_executeGame(E_UI_MENU gameMode, E_PLAYER_MODE player1, E_PLAYER_MODE player2, E_BOOL withJoker)
{
	M_ENTRY();
	E_BOOL continueGame = E_TRUE;
	while(continueGame == E_TRUE) {
		/* メニュー表示 */
		ui_showMenuTitle(gameMode);
		ui_showMenu(gameMode);
		E_UI_SELECT_CODE selectCode = ui_getSelectCode();
		if (selectCode != E_UI_1) {
			continueGame = E_FALSE;
			continue;
		}

		/* カードを箱から出す */
		card_outOfBox(withJoker);
		/* シャッフル */
		card_shuffle();
		card_shuffle();

		/* カードを配って手札にする */
		/* Player1 */
		game_executeGameDeal(player1);
		/* Player2 */
		game_executeGameDeal(player2);

		/* カードを表示して取り替えたいカードを選ぶ */
		/* Player1 */
		game_executeGameSelect(gameMode, player1);
		/* Player2 */
		game_executeGameSelect(gameMode, player2);

		/* カード交換 */
		/* Player1 */
		game_executeGameChange(player1);
		/* Player2 */
		game_executeGameChange(player2);

		/* 結果を表示する */
		ui_showMenuTitle(gameMode);
		HAND_CARD handCard1 = player_handCard(player1);
		HAND_CARD handCard2 = player_handCard(player2);
		POKER_HAND judgeResult1 = poker_judgment(handCard1);
		POKER_HAND judgeResult2 = poker_judgment(handCard2);
		ui_showSubTitle(player1);
		ui_showHandCard(handCard1);
		ui_showSubTitle(player2);
		ui_showHandCard(handCard2);
		E_POKER_COMP_RESULT compResult = poker_judgmentComp(handCard1, handCard2);
		ui_showPokerResult2(judgeResult1, judgeResult2, compResult);
		ui_pleaseEnterSomething();

		/* 手札を戻す */
		player_restoreCard(player1);
		player_restoreCard(player2);
	}
	return continueGame;
}

/**
 * @brief	ゲーム実施：カードを配る
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static void game_executeGameDeal(E_PLAYER_MODE player)
{
	M_ENTRY();
	/* カードを配って手札にする */
	player_receiveCard(player, card_deal());
	player_receiveCard(player, card_deal());
	player_receiveCard(player, card_deal());
	player_receiveCard(player, card_deal());
	player_receiveCard(player, card_deal());
}

/**
 * @brief	ゲーム実施：カードを選ぶ
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static void game_executeGameSelect(E_UI_MENU gameMode, E_PLAYER_MODE player)
{
	M_ENTRY();
	E_BOOL finishSelect = E_TRUE;
	while(finishSelect == E_TRUE) {
		/* タイトル表示 */
		ui_showMenuTitle(gameMode);
		ui_showSubTitle(player);
		/* 手札を出す */
		HAND_CARD handCard = player_handCard(player);
		ui_showHandCard(handCard);
		/* カード交換選択 */
		E_UI_SELECT_CODE selectCode = E_UI_OTHER;
		if ((player == E_PLAYER_1) || (player == E_PLAYER_2)) {
			ui_showMessageSelectCard();
			selectCode = ui_getSelectCode();
		} else {
			selectCode = player_selectCardForCOM(player);
		}
		M_INFO("selectCode=%d",selectCode);
		if ((E_UI_1 <= selectCode) && (selectCode <= E_UI_5)) {
			U1 changeCardIndex = selectCode - 1;
			player_selectCard(player, changeCardIndex);
		} else {
			finishSelect = E_FALSE;
		}
	}
}

/**
 * @brief	ゲーム実施：カードを取り替える
 * @note	
 * @return
 * |値 | 説明 |
 * |---|------|
 * | E_TRUE |ゲームを続ける|
 * | E_FALSE |ゲームを終了する|
 */
static void game_executeGameChange(E_PLAYER_MODE player)
{
	M_ENTRY();
	U1 changeNum = player_changeCardNum(player);
	U1 i = 0;
	for (i = 0; i < changeNum; i++) {
		player_changeCard(player, card_deal());
	}
}
