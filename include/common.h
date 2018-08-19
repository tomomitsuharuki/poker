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
typedef U2					POKER_HAND;		/**< Pokerの役 */
/*@}*/

/**
 * @enum	E_BOOL
 * @brief	Bool型
 */
typedef enum {
	E_TRUE = 0,
	E_FALSE = 1,
} E_BOOL;

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "config.h"
#include "debug.h"

#endif /* __COMMON_H_ */