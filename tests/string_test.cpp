/*
 * Copyright 2010-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#include "test.h"
#include <bx/string.h>
#include <bx/crtimpl.h>
#include <bx/handlealloc.h>

#include <tinystl/allocator.h>
#include <tinystl/string.h>

bx::AllocatorI* g_allocator;

TEST_CASE("strnlen", "")
{
	const char* test = "test";

	REQUIRE(0 == bx::strnlen(test, 0) );
	REQUIRE(2 == bx::strnlen(test, 2) );
	REQUIRE(4 == bx::strnlen(test, UINT32_MAX) );
}

TEST_CASE("StringView", "")
{
	bx::StringView sv("test");
	REQUIRE(4 == sv.getLength() );

	bx::CrtAllocator crt;
	g_allocator = &crt;

	typedef bx::StringT<&g_allocator> String;

	String st(sv);
	REQUIRE(4 == st.getLength() );

	st.clear();
	REQUIRE(0 == st.getLength() );
	REQUIRE(4 == sv.getLength() );

	sv.clear();
	REQUIRE(0 == sv.getLength() );
}

TEST_CASE("TinystlString", "")
{
	tinystl::string s("test");
	
	REQUIRE(s[2]=='s');
	
	s[2] = 'x';
	
	REQUIRE(*(s.c_str() + 2) =='x');

	REQUIRE(0 == strcmp(s.c_str(), "text"));

	const char* largeText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	
	tinystl::string s2(largeText);
	REQUIRE(0 == strcmp(s2.c_str(), largeText));
	
	tinystl::string s3("this is text");
	s3.resize(100);
	REQUIRE(0 == strcmp(s3.c_str(), "this is text"));

	tinystl::string s4("this is text");
	s4.reserve(100);
	REQUIRE(0 == strcmp(s4.c_str(), "this is text"));
	
	
}

