#include <bx/bx.h>
#include <bx/timer.h>
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


//TODO: insert(iterator) is not in std

#include <stdio.h>
#include <assert.h>

class Benchmark
{
public:
	Benchmark() : startTime(0)
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
	
	void finishAndLog(const char* title)
	{
		printf("%50s: %15.0f\n", title, (double)fullTime);
		fullTime = 0;
	}
	

protected:
	int64_t fullTime;
	int64_t startTime;
};


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



int main()
{
	const uint32_t numElements   = 4<<10;
	const uint32_t numIterations = 4*16;
	
	Benchmark b;

	for(int i=0; i < 3;++i)
	{
		string_construct_destruct_bench<tinystl_original::string>(b);
		b.finishAndLog("tinystl_original::string construct/destruct");
		
		string_construct_destruct_bench<tinystl::string>(b);
		b.finishAndLog("tinystl::string construct/destruct");
		
		string_construct_destruct_bench<std::string>(b);
		b.finishAndLog("std::string construct/destruct");
		
		string_construct_destruct_bench<eastl::string>(b);
		b.finishAndLog("eastl::string construct/destruct");
	}

	for(int i=0; i < 3;++i)
	{
		string_resize_bench<tinystl_original::string>(b);
		b.finishAndLog("tinystl_original::string resize");
		
		string_resize_bench<tinystl::string>(b);
		b.finishAndLog("tinystl::string resize");
		
		string_resize_bench<std::string>(b);
		b.finishAndLog("std::string resize");
		
		string_resize_bench<eastl::string>(b);
		b.finishAndLog("eastl::string resize");
		
	}

	
	for(int i=0; i < 3;++i)
	{
		string_reserve_bench<tinystl_original::string>(b);
		b.finishAndLog("tinystl_original::string reserve");
		
		string_reserve_bench<tinystl::string>(b);
		b.finishAndLog("tinystl::string reserve");
		
		string_reserve_bench<std::string>(b);
		b.finishAndLog("std::string reserve");
		
		string_reserve_bench<eastl::string>(b);
		b.finishAndLog("eastl::string reserve");
		
	}
	
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
