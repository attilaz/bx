#include <bx/bx.h>
#include <bx/handlealloc.h>
#include <bx/maputil.h>

#define tinystl tinystl_original
#include <TINYSTL_ORIGINAL/allocator.h>
#include <TINYSTL_ORIGINAL/string.h>
#undef tinystl

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

#include <functional>

#include "dbg.h"
//TODO: insert(iterator) is not in std

#include <stdio.h>
#include <assert.h>

#define countof(N) (sizeof(N)/sizeof(N[0]))


void benchmark(std::function<void(Benchmark&)> func)
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
	
	printf("%15.0f", (double)sum / countNotOutlier);
}


#define BENCHMARK(function, title)\
template <typename Container> void function##_call(Benchmark& b); \
void function() \
{\
printf("%30s", title);\
benchmark(function##_call<tinystl::string>);	\
benchmark(function##_call<tinystl_original::string>);	\
benchmark(function##_call<std::string>);	\
benchmark(function##_call<eastl::string>);	\
printf("\n");\
}\
template <typename Container> void function##_call(Benchmark& b)


#define BENCHMARK_NO_TINYSTL(function, title)\
template <typename Container> void function##_call(Benchmark& b); \
void function() \
{\
printf("%30s", title);\
benchmark(function##_call<tinystl::string>);	\
printf("%15.0f", 0.0f);\
benchmark(function##_call<std::string>);	\
benchmark(function##_call<eastl::string>);	\
printf("\n");\
}\
template <typename Container> void function##_call(Benchmark& b)


//stringT(const stringT<Alloc>& other);
BENCHMARK(string_construct_string_destruct_bench, "construct(string&)/destruct")
{
	Container c("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	b.start();
	{
		for(int i=0;i<100000;++i)
		{
			Container a(c);
		}
	}
	b.stop();
}

//stringT(const char* sz, size_t len);
BENCHMARK(string_construct_char_len_destruct_bench, "construct(char*,int)/destruct")
{
	const char* c = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	size_t len = strlen(c);
	b.start();
	{
		for(int i=0;i<100000;++i)
		{
			Container a(c,len);
		}
	}
	b.stop();
}

//stringT(const char* sz);
BENCHMARK(string_construct_char_destruct_bench, "construct(char*)/destruct")
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

// stringT<Alloc>& operator=(const stringT<Alloc>& other);
BENCHMARK(string_set_value_string, "set value string&")
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

// stringT<Alloc>& operator=(const char* other);
BENCHMARK(string_set_value_constchar, "set value const char*")
{
	for(int i=0;i<100000;++i)
	{
		Container a;
		b.start();
		a = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		b.stop();
	}
}

//void resize(size_t _size);
BENCHMARK(string_resize_bench, "resize")
{
	for(int i=0;i<100000;++i)
	{
		Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
		b.start();	//test construct/destruct
		a.resize(1000);
		b.stop();
	}
}

//void reserve(size_t _size);
BENCHMARK(string_reserve_bench, "reserve")
{
	for(int i=0;i<100000;++i)
	{
		Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
		b.start();
		a.reserve(100);
		b.stop();
	}
}

//char& operator[](size_t pos);
BENCHMARK_NO_TINYSTL(string_bracket_get_bench, "[] get")
{
	Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	size_t asize = a.size();
	char accum;
	b.start();
	for(int i=0;i<100000;++i)
	{
		for(int j=0;j<asize;++j)
			accum += a[j];
	}
	b.use(accum);
	b.stop();
}


//const char& operator[](size_t pos) const;
BENCHMARK_NO_TINYSTL(string_bracket_set_bench, "[] set")
{
	const char* s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	Container a(s);
	size_t asize = a.size();
	b.start();
	for(int i=0;i<100000;++i)
	{
		for(int j=0;j<asize;++j)
			a[j] = s[(j+1)%asize];
	}
	b.use(a.c_str());
	b.stop();
}

//size_t size() const;
BENCHMARK(string_size_bench, "size")
{
	Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	b.start();
	for(int i=0;i<100000;++i)
	{
		b.use( a.size() );
	}
	b.stop();
}

//bool empty() const;
BENCHMARK_NO_TINYSTL(string_empty_bench, "empty")
{
	Container a("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
	b.start();
	for(int i=0;i<100000;++i)
	{
		b.use( a.empty() );
	}
	b.stop();
}

//void append(const char* first, const char* last);
BENCHMARK(string_append_range_bench, "append range")
{
	const char* str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	Container a = str;
	for(int i=0;i<100000;++i)
	{
		b.start();
		a.append(str + 5, str + 10 );
		b.stop();
	}
}


//void append(const char* str);
BENCHMARK_NO_TINYSTL(string_append_char_bench, "append char*")
{
	const char* str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	Container a = str;
	for(int i=0;i<100000;++i)
	{
		b.start();
		a.append(str + 5);
		b.stop();
	}
}

//void swap(stringT<Alloc>& other);
BENCHMARK_NO_TINYSTL(string_swap_bench, "swap")
{
	for(int i=0;i<100000;++i)
	{
		Container s0 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		Container s1 = "Lorem ipsum ";
		b.start();
		s0.swap(s1);
		b.stop();
		b.use(s0.c_str());
	}
}

//inline bool operator==(const stringT<Alloc>& lhs, const stringT<Alloc>& rhs)
BENCHMARK(string_compare_string, "compare string")
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

//inline bool operator==(const stringT<Alloc>& lhs, const char* rhs) {
BENCHMARK(string_compare_const_char, "compare const char*")
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

void string_benchmarks()
{
	Benchmark b;
	
	printf("%30s%15s%15s%15s%15s\n", "string feature", "TinySTL", "TinySTLO", "std", "EASTL");
	string_construct_string_destruct_bench();
	string_construct_char_destruct_bench();
	string_construct_char_len_destruct_bench();
	string_resize_bench();
	
	string_reserve_bench();
	
	string_bracket_get_bench();
	string_bracket_set_bench();
	
	string_size_bench();
	string_empty_bench();
	
	string_append_range_bench();
	string_append_char_bench();
	string_swap_bench();
	
	string_set_value_constchar();
	
	string_set_value_string();
	
	string_compare_string();
	string_compare_const_char();
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
