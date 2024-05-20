/***********************************************************************
 * File: Buff.h
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-20
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-20
 * Description: This header file defines the Buff namespace,
 *				which contains an enum BUFF_IDX representing different types of buffs and
 *				a struct Buff representing a buff with its type and duration.
***********************************************************************/
#ifndef _BUFF_H_
#define _BUFF_H_

namespace Buff
{
	/**
	 * Enum representing different types of buffs.
	 */
	enum BUFF_IDX
	{
		BANGRY = 0,       // Angry buff index
		BDIZZINESS = 1,   // Dizziness buff index
		BPOISONED = 2,    // Poisoned buff index
		BSPEEDUP = 3      // Speedup buff index
	};

	/**
	 * Struct representing a buff with its type and duration.
	 */
	struct Buff
	{
		int buffIdx;  // Index of the buff type
		int turn;     // Duration of the buff in turns
	};
}

#endif // _BUFF_H_