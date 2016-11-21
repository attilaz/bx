#include <bx/bx.h>
#include <bx/handlealloc.h>
#include <bx/maputil.h>

#include <vector>
#include <unordered_map>

#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>

#include <EASTL/fixed_map.h>

#include "dbg.h"
#include "benchmark.h"
//TODO: insert(iterator) is not in std

#include <stdio.h>
#include <assert.h>

#include <string>

#define countof(N) (sizeof(N)/sizeof(N[0]))

extern void string_benchmarks();

std::string func_str()
{
	return std::string("aaaa");
}


int main()
{
	const uint32_t numElements   = 4<<10;
	const uint32_t numIterations = 4*16;
	
	string_benchmarks();
	
	printf("\n\n");
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
