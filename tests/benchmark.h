/*
 * Copyright 2016-2016 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef BENCHMARK_H_HEADER_GUARD
#define BENCHMARK_H_HEADER_GUARD

#include <stdint.h>
#include <bx/timer.h>

class Benchmark
{
public:
	Benchmark() : startTime(0), fullTime(0)
	{
	}
	
	void start()
	{
		if ( 0 == startTime )
		{
			startTime = bx::getHPCounter();
		}
	}
	void stop()
	{
		if ( 0 != startTime )
		{
			fullTime += bx::getHPCounter() - startTime;
			startTime = 0;
		}
	}
	
	float getFullTime()
	{
		return fullTime;
	}
	
	void use(...);
	
protected:
	int64_t fullTime;
	int64_t startTime;
};


#endif // BENCHMARK_H_HEADER_GUARD
