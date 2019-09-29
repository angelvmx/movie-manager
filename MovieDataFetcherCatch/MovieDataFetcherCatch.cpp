#include "stdafx.h"

#include "Catch/catch.hpp"

#include "MetaDataProcessor.h"
#include "TheMovieDbDataFactory.h"
#include "Fakes.h"
#include "MovieNotFoundException.h"

using namespace std;
using namespace testing;
TEST_CASE("ProcessMovies returns movie data")
{
	TheMovieDbDataFactory factory;

	auto fakeLoggerFactory = make_shared<NiceMock<FakeLoggerFactory>>();
	auto fakeLogger = make_shared<FakeLogger>();
	ON_CALL(*fakeLoggerFactory, CreateLogger()).WillByDefault(Return(fakeLogger));

	FakeMovieMetaDataRepository fakeRepository;
	MetaDataProcessor processor(fakeRepository, fakeLoggerFactory);

	Movies result;

	SECTION("Return empty result for empty list")
	{
		processor.ProcessMovies({}, result);

		REQUIRE(result.size() == 0);
	}

	SECTION("Log exceptions thrown during processing")
	{
		MovieNotFoundException testException("My Movie");
		EXPECT_CALL(fakeRepository, FindMovieData(_)).WillRepeatedly(Throw(testException));
		EXPECT_CALL(*fakeLogger, LogError("My Movie")).Times(0);

		processor.ProcessMovies({"My Movie"}, result);
		ASSERT_EQ(0, result.size());
	}
}