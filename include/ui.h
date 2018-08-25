/**
 * @brief UIクラスヘッダー
 * 
 * @file ui.h
 */
#ifndef __UI_H__
#define __UI_H__

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "card.h"
#include "player.h"

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	構造体定義																					*/
/************************************************************************************************/
/**
 * @enum	E_UI_SELECT_CODE
 * @brief	ユーザー入力選択ID
 */
typedef enum {
	E_UI_ERROR = 0,
	E_UI_1 = 1,
	E_UI_2,
	E_UI_3,
	E_UI_4,
	E_UI_5,
	E_UI_OTHER,
	E_UI_RETURN = 0xFF,
} E_UI_SELECT_CODE;

/**
 * @enum	E_UI_MENU
 * @brief	メニュー画面
 */
typedef enum {
	E_UI_MENU_MAIN,			/**< メインメニュー */
	E_UI_MENU_ROOKIE,		/**< ルーキーメニュー */
	E_UI_MENU_ROOKIE2,		/**< ルーキー2メニュー */
	E_UI_MENU_MIDDLE,		/**< ミドルメニュー */
	E_UI_MENU_LEGEND,		/**< レジェンドメニュー */
} E_UI_MENU;

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/
/**
 * @brief	画面クリア
 * @note	
 */
void ui_clear(void);

/**
 * @brief	メニューを表示する
 * @note	コンソール向け
 */
void ui_showMenu(E_UI_MENU menuId);

/**
 * @brief	ユーザーが入力したコードを取得する
 * @note	コンソール向け
 *
 * @return	入力したコード
 */
E_UI_SELECT_CODE ui_getSelectCode(void);

/**
 * @brief	なにか入力してください。
 * @note	
 */
void ui_pleaseEnterSomething(void);

/**
 * @brief	手札を表示する
 * @note	
 *
 * @param[in]	pokerHand	手札情報
 */
void ui_showHandCard(HAND_CARD handCard);

/**
 * @brief	ポーカーの役を表示する
 * @note	
 *
 * @param[in]	pokerHand	手札情報
 * @param[in]	pokerHand	ポーカーの役
 */
void ui_showPokerResult(HAND_CARD handCard, POKER_HAND pokerHand);

#endif /* __UI_H__ */