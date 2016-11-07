#include <bx/bx.h>
#include <bx/handlealloc.h>
#include <bx/maputil.h>

#include <tinystl_original/allocator.h>
#include <tinystl_original/string.h>


#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
#include <tinystl/string.h>

#include <EASTL/map.h>
#include <EASTL/hash_map.h>
#include <EASTL/vector_map.h>
#include <EASTL/fixed_map.h>
#include <EASTL/string.h>

#include <string>
#include <vector>
#include <unordered_map>


#include "dbg.h"
//TODO: insert(iterator) is not in std

#include <stdio.h>
#include <assert.h>



template <typename Container>
void string_construct_destruct_bench(Benchmark& b)
{
	b.start();
	{
		for(int i=0;i<100000;++i)
		{
			Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
		}
	}
	
	b.stop();
}

template <typename Container>
void string_resize_bench(Benchmark& b)
{
	{
		for(int i=0;i<100000;++i)
		{
			Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
			b.start();	//test construct/destruct
			a.resize(1000);
			b.stop();
		}
	}
}

template <typename Container>
void string_reserve_bench(Benchmark& b)
{
	{
		for(int i=0;i<100000;++i)
		{
			Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
			b.start();
			a.reserve(100);
			b.stop();
		}
	}
}

template <typename Container>
void string_set_value_string(Benchmark& b)
{
	{
		Container s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		
		for(int i=0;i<100000;++i)
		{
			Container a;
			b.start();
			a = s;
			b.stop();
		}
	}
}

template <typename Container>
void string_set_value_constchar(Benchmark& b)
{
	{
		for(int i=0;i<100000;++i)
		{
			Container a;
			b.start();
			a = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
			b.stop();
		}
	}
}

template <typename Container>
void string_compare_string(Benchmark& b)
{
	{
		Container s0 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		Container s1 = "Lorem ipsum ";
		Container s2 = "dolor sit amet, consectetur adipiscing elit.";
		
		b.start();
		for(int i=0;i<100000;++i)
		{
			b.use(s0 == s1);
			b.use(s1 == s2);
			b.use(s2 == s2);
			
		}
		b.stop();
	}
}

template <typename Container>
void string_compare_const_char(Benchmark& b)
{
	{
		const char* cs0 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		const char* cs1 = "Lorem ipsum ";
		const char* cs2 = "dolor sit amet, consectetur adipiscing elit.";
		
		Container s0 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		Container s1 = "Lorem ipsum ";
		Container s2 = "dolor sit amet, consectetur adipiscing elit.";
		
		b.start();
		for(int i=0;i<100000;++i)
		{
			b.use(s0 == cs1);
			b.use(s1 == cs2);
			b.use(s2 == cs2);
			b.use(s2 == cs0);
		}
		b.stop();
	}
}




#define TEST(function, name)\
{\
function<tinystl::string>(b);	\
b.finishAndLog("tinystl" name);	\
function<tinystl_original::string>(b);	\
b.finishAndLog("tinystl_original" name);\
function<std::string>(b);	\
b.finishAndLog("std" name);	\
function<eastl::string>(b);	\
b.finishAndLog("eastl" name);\
}

#define TEST_NO_TINYSTLORIG(function, name)\
{\
function<tinystl::string>(b);	\
b.finishAndLog("tinystl" name);	\
function<std::string>(b);	\
b.finishAndLog("std" name);	\
function<eastl::string>(b);	\
b.finishAndLog("eastl" name);\
}


int main()
{
	const uint32_t numElements   = 4<<10;
	const uint32_t numIterations = 4*16;
	
	Benchmark b;

#if 0
	for(int i=0; i < 3;++i)
		TEST(string_construct_destruct_bench, "::string construct/destruct");

	for(int i=0; i < 3;++i)
		TEST(string_resize_bench, "::string resize");
	
	for(int i=0; i < 3;++i)
		TEST(string_reserve_bench, "::string reserve");

	for(int i=0; i < 3;++i)
		TEST(string_set_value_constchar, "::string set value const char*");
	for(int i=0; i < 3;++i)
		TEST(string_set_value_string, "::string set value string");
#endif

	for(int i=0; i < 3;++i)
		TEST(string_compare_string, "::string compare string");

	for(int i=0; i < 3;++i)
		TEST_NO_TINYSTLORIG(string_compare_const_char, "::string compare const char*");
	
	//
	{
		int64_t elapsed = -bx::getHPCounter();

		for (uint32_t ii = 0; ii < numIterations; ++ii)
		{
			typedef tinystl::unordered_map<uint64_t, uint16_t> TinyStlUnorderedMap;
			TinyStlUnorderedMap map;
//			map.reserve(numElements);
			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				tinystl::pair<TinyStlUnorderedMap::iterator, bool> ok = map.insert(tinystl::make_pair(uint64_t(jj), uint16_t(jj) ) );
				assert(ok.second);
			}

			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				bool ok = bx::mapRemove(map, uint64_t(jj) );
				assert(ok);
			}

			assert(map.size() == 0);
		}

		elapsed += bx::getHPCounter();
		printf("       TinyStl: %15.0f\n", double(elapsed) );
	}

	///
	{
		int64_t elapsed = -bx::getHPCounter();

		for (uint32_t ii = 0; ii < numIterations; ++ii)
		{
			typedef std::unordered_map<uint64_t, uint16_t> StdUnorderedMap;
			StdUnorderedMap map;
			map.reserve(numElements);
			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				std::pair<StdUnorderedMap::iterator, bool> ok = map.insert(std::make_pair(uint64_t(jj), uint16_t(jj) ) );
				assert(ok.second);
			}

			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				bool ok = bx::mapRemove(map, uint64_t(jj) );
				assert(ok);
			}

			assert(map.size() == 0);
		}

		elapsed += bx::getHPCounter();
		printf("           STL: %15.0f\n", double(elapsed) );
	}

	///
	{
		int64_t elapsed = -bx::getHPCounter();
		
		for (uint32_t ii = 0; ii < numIterations; ++ii)
		{
			typedef eastl::fixed_map<uint64_t, uint16_t, numElements+numElements/2, false> StdUnorderedMap;
			StdUnorderedMap map;
			//map.reserve(numElements);
			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				eastl::pair<StdUnorderedMap::iterator, bool> ok =
				map.insert(eastl::make_pair(uint64_t(jj), uint16_t(jj) ) );
				assert(ok.second);
			}
			
			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				bool ok = bx::mapRemove(map, uint64_t(jj) );
				assert(ok);
			}
			
			assert(map.size() == 0);
		}
		
		elapsed += bx::getHPCounter();
		printf("EASTL hash_map: %15.0f\n", double(elapsed) );
	}
	
	
	///
	{
		int64_t elapsed = -bx::getHPCounter();

		for (uint32_t ii = 0; ii < numIterations; ++ii)
		{
			typedef bx::HandleHashMapT<numElements+numElements/2, uint64_t> HandleHashMap;
			HandleHashMap map;
			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				bool ok = map.insert(jj, uint16_t(jj) );
				assert(ok);
			}

			for (uint32_t jj = 0; jj < numElements; ++jj)
			{
				bool ok = map.removeByKey(uint64_t(jj) );
				assert(ok);
			}

			assert(map.getNumElements() == 0);
		}

		elapsed += bx::getHPCounter();
		printf(" HandleHashMap: %15.0f\n", double(elapsed) );
	}

	return EXIT_SUCCESS;
}
