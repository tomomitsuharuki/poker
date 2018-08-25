/**
 * @brief main
 * 
 * @file main.c
 */

/************************************************************************************************/
/*	インクルードファイル記載																	*/
/************************************************************************************************/
#include "common.h"
#include "game.h"

/************************************************************************************************/
/*	クラス内デバッグ設定																		*/
/************************************************************************************************/
#define M_ERROR(...)		M_DEBUG_ERROR(D_DEBUG_CLASS_MAIN, __VA_ARGS__)
#define M_ENTRY(...)		M_DEBUG_ENTRY(D_DEBUG_CLASS_MAIN, __VA_ARGS__)
#define M_INFO(...)			M_DEBUG_INFO(D_DEBUG_CLASS_MAIN, __VA_ARGS__)

/************************************************************************************************/
/*	main関数																					*/
/************************************************************************************************/
/**
 * @brief 
 * 
 * @param argc 未使用
 * @param argv 未使用
 * @return int 0
 */
int main(int argc, char* argv[])
{
	M_ENTRY();
	(void)argc;
	(void)argv;

	game_start();

	M_ENTRY("finish");
	return 0;
}
