#ifndef RANDOM_H
#define RANDOM_H

#include <math.h>
#include <time.h>
#include <random>

#include <fuzzy.hpp>

class random
{
public:

	inline static void seed(__int64* seed)
	{
		__int64 _seed = time(0);
		if (seed != 0)
		{
			*seed = _seed;
		}

		srand((unsigned int)_seed);
	}
	inline static void set(__int64 seed)
	{
		srand((unsigned int)seed);
	}

	inline static char range(char min, char max)
	{
		return interp(scalar(), min, max);
	}
	inline static int range(int min, int max)
	{
		return interp(scalar(), min, max);
	}
	inline static long long range(long long min, long long max)
	{
		return interp(scalar(), min, max);
	}
	inline static float range(float min, float max)
	{
		return interp(scalar(), min, max);
	}
	inline static double range(double min, double max)
	{
		return interp(scalar(), min, max);
	}

	inline static int d100()
	{
		return (rand() % 100) + 1;
	}
	inline static int d50()
	{
		return (rand() % 50) + 1;
	}
	inline static int d32()
	{
		return (rand() % 32) + 1;
	}
	inline static int d24()
	{
		return (rand() % 24) + 1;
	}
	inline static int d20()
	{
		return (rand() % 20) + 1;
	}
	inline static int d16()
	{
		return (rand() % 16) + 1;
	}
	inline static int d12()
	{
		return (rand() % 12) + 1;
	}
	inline static int d10()
	{
		return (rand() % 10) + 1;
	}
	inline static int d8()
	{
		return (rand() % 8) + 1;
	}
	inline static int d6()
	{
		return (rand() % 6) + 1;
	}
	inline static int d4()
	{
		return (rand() % 4) + 1;
	}
	inline static int d3()
	{
		return (rand() % 3) + 1;
	}
	inline static bool coin()
	{
		if (rand() % 2 == 0) return true;
		return false;
	}
	inline static float scalar()
	{
		return float(rand() % 10000) / 10000.0f;
	}

	inline static char alpha()
	{
		if (coin())
		{
			return range('A', 'Z');
		}
		return range('a', 'z');
	}
	inline static char num()
	{
		return range('0', '9');
	}
	inline static char alphanum()
	{
		int type = d3();
		switch (type)
		{
		case 1:
			return range('0', '9');
			break;
		case 2:
			return range('A', 'Z');
			break;
		case 3:
			return range('a', 'z');
			break;
		default:
			return range('0', '9');
			break;
		}
	}

};

#endif