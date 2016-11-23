#include "cpptemplates/iterator.h"
#include "test.h"
#include <tinystl/allocator.h>
#include <tinystl/vector.h>
#include <tinystl/string.h>

TEST_CASE("erase_iterator", "")
{
	tinystl::vector<int> v;
	for(int i=0;i<10;++i)
		v.push_back(i);

	for(auto& item : iter::eraser(v))
	{
		if ( *item == 2)
			item.mark_for_erase();
	}
	//todo: check something
}

TEST_CASE("erase_iterator_string", "")
{
	tinystl::vector<tinystl::string> v;
	v.push_back("a");
	v.push_back("b");
	v.push_back("c");
	
	for(auto& item : iter::eraser(v))
	{
		if ( *item == "b")
			item.mark_for_erase();
	}
	//todo: check something
}