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
#include "card.h"
#include "player.h"
#include "poker.h"

/************************************************************************************************/
/*	定義値																						*/
/************************************************************************************************/

/************************************************************************************************/
/*	構造体定義																					*/
/************************************************************************************************/

/************************************************************************************************/
/*	関数プロトタイプ宣言																		*/
/************************************************************************************************/
/**
 * @brief	画面クリア
 * @note	
 */
void ui_clear(void);

/**
 * @brief	メニュータイトルを表示する
 * @note	コンソール向け
 */
void ui_showMenuTitle(E_UI_MENU menuId);

/**
 * @brief	サブタイトル（プレイヤー）を表示する
 * @note	コンソール向け
 */
void ui_showSubTitle(E_PLAYER_MODE subId);

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
 * @param[in]	pokerHand	ポーカーの役
 */
void ui_showPokerResult(E_POKER_HAND pokerHand);

/**
 * @brief	ポーカーの役を表示する
 * @note	
 *
 * @param[in]	pokerHand1	ポーカーの役
 * @param[in]	pokerHand2	ポーカーの役
 * @param[in]	compResult	勝敗情報
 */
void ui_showPokerResult2(E_POKER_HAND pokerHand1, E_POKER_HAND pokerHand2, E_POKER_COMP_RESULT compResult);

/**
 * @brief	メッセージを表示する
 * @note	
 *
 */
void ui_showMessageSelectCard(void);

#endif /* __UI_H__ */