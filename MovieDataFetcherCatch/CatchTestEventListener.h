#pragma once
#include <gtest/gtest.h>
#include <Catch/catch.hpp>

class CatchTestEventListener : public ::testing::EmptyTestEventListener
{
public:
	CatchTestEventListener() {}
	virtual ~CatchTestEventListener() {}

	void OnTestPartResult(const testing::TestPartResult& assertionResult) override
	{
		INFO(assertionResult.message());
		REQUIRE_FALSE(assertionResult.failed());
	}
};