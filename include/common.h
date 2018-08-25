/**
 * @brief 共通ヘッダ
 * 
 * @file common.h
 */
#ifndef __COMMON_H_
#define __COMMON_H_

/************************************************************************************************/
/*	型定義																						*/
/************************************************************************************************/
/**
 * @name 型定義
 */
/*@{*/
typedef char				C1;
typedef signed char			S1;
typedef signed short		S2;
typedef signed long			S4;
typedef signed long long	S8;
typedef unsigned char		U1;
typedef unsigned short		U2;
typedef unsigned long		U4;
typedef unsigned long long	U8;
/*@}*/

/**
 * @name カード情報の型
 */
/*@{*/
typedef U1					CID;			/**< Card ID */
// typedef U2					POKER_HAND;		/**< Pokerの役 */
/*@}*/

/**
 * @enum	E_BOOL
 * @brief	Bool型
 */
typedef enum {
	E_FALSE = 0,			/**< False */
	E_TRUE = 1,				/**< True */
} E_BOOL;

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
	E_UI_MENU_MIDDLE1,		/**< ミドル1メニュー */
	E_UI_MENU_MIDDLE2,		/**< ミドル2メニュー */
	E_UI_MENU_MIDDLE3,		/**< ミドル3メニュー */
	E_UI_MENU_LEGEND,		/**< レジェンドメニュー */
} E_UI_MENU;

/**
 * @enum	E_PLAYER_MODE
 * @brief	プレイヤーモード
 */
typedef enum {
	E_PLAYER_1,				/**< Player1:対人先行 */
	E_PLAYER_2,				/**< Player1:対人後攻 */
	E_PLAYER_COM_EASY,		/**< COM(Easy):ミドル3モード */
	E_PLAYER_COM_NORMAL,	/**< COM(Normal):レジェンドモード */

	E_PLAYER_MODE_MAX,		/**< Do not use */
} E_PLAYER_MODE;

/**
 * @enum	E_CARD_CHANGE
 * @brief	カード取り替え情報
 */
typedef enum {
	E_CARD_CHANGE_NOT_SELECT,	/**< カード取り換え：未選択 */
	E_CARD_CHANGE_SELECTED,		/**< カード取り換え：選択中 */

	E_CARD_CHANGE_MAX,			/**< Do not use */
} E_CARD_CHANGE;

/**
 * @enum	E_POKER_COMP_RESULT
 * @brief	Poker勝敗情報
 */
typedef enum {
	E_POKER_COMP_DRAW,
	E_POKER_COMP_PLAYER1_WON,
	E_POKER_COMP_PLAYER2_WON,

	E_POKER_COMP_RESULT_MAX,	/**< Do not use */
} E_POKER_COMP_RESULT;

/**
 * @enum	E_POKER_HAND
 * @brief	Pokerの役
 */
typedef enum {
	E_POKER_HAND_ROYAL_STRAIGHT_FLASH,
	E_POKER_HAND_FIVE_CARD,
	E_POKER_HAND_STRAIGHT_FLASH,
	E_POKER_HAND_FOUR_CARD,
	E_POKER_HAND_FULL_HOUSE,
	E_POKER_HAND_FLASH,
	E_POKER_HAND_STRAIGHT,
	E_POKER_HAND_THREE_CARD,
	E_POKER_HAND_TWO_PAIR,
	E_POKER_HAND_ONE_PAIR,
	E_POKER_HAND_BUHI,

	E_POKER_HAND_TYPE_MAX,							/**< Do not use */
} E_POKER_HAND;

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "config.h"

#endif /* __COMMON_H_ */