/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef DBG_H_HEADER_GUARD
#define DBG_H_HEADER_GUARD

#include <stdarg.h> // va_list
#include <stdint.h>
#include <bx/timer.h>


#define DBG_STRINGIZE(_x) DBG_STRINGIZE_(_x)
#define DBG_STRINGIZE_(_x) #_x
#define DBG_FILE_LINE_LITERAL "" __FILE__ "(" DBG_STRINGIZE(__LINE__) "): "
#define DBG(_format, ...) dbgPrintf(DBG_FILE_LINE_LITERAL "" _format "\n", ##__VA_ARGS__)

extern void dbgPrintfVargs(const char* _format, va_list _argList);
extern void dbgPrintf(const char* _format, ...);
extern void dbgPrintfData(const void* _data, uint32_t _size, const char* _format, ...);

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


#endif // DBG_H_HEADER_GUARD
