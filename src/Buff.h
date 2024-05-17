#ifndef _BUFF_H_
#define _BUFF_H_

namespace Buff
{
	enum BUFF_IDX
	{
		BANGRY = 0,
		BDIZZINESS = 1,
		BPOISONED = 2,
		BSPEEDUP = 3
	};

	struct Buff
	{
		int buffIdx;
		int turn;
	};

}

#endif // _BUFF_H_