/*
 * Copyright 2016-2016 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#include "benchmark.h"
#include <algorithm>
#include <math.h>

#define countof(N) (sizeof(N)/sizeof(N[0]))

float benchmark(std::function<void(Benchmark&)> func)
{
	float times[10];
	for(int i=0;i<countof(times);++i)
	{
		Benchmark b;
		func(b);
		times[i] = b.getFullTime();
	}
	//compute median with disregarding outliers
	std::sort(times, times+countof(times));
	
	float median = times[countof(times)/2];
	
	int countNotOutlier = 0;
	float sum = 0.0;
	for(int i=0;i<countof(times);++i)
	{
		if ( fabsf(median-times[i]) < median * 0.1f )
		{
			++countNotOutlier;
			sum += times[i];
		}
	}
	
	return (float)((double)sum / countNotOutlier);
}


void Benchmark::use(...)
{
	
}
