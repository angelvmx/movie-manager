#include "stdafx.h"

#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"
#include "gmock/gmock.h"
#include "CatchTestEventListener.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);

	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
	listeners.Append(new CatchTestEventListener());
	delete listeners.Release(listeners.default_result_printer());

	return Catch::Session().run(argc, argv);
}