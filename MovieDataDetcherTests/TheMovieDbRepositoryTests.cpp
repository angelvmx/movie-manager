#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TheMovieDbRepository.h"
#include "TheMovieDbDataFactory.h"
#include "MovieNotFoundException.h"
#include "FakeRestApiClient.h"

using namespace testing;

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnEmptyString_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;
	EXPECT_CALL(fakeClient, HttpGet(_)).WillOnce(Return(""));

	TheMovieDbRepository repository("api-key", factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}

TEST(TheMovieDbRepositoryTests, FindMovieData_ApiReturnsStringWithoutMovie_ThrowException)
{
	TheMovieDbDataFactory factory;
	FakeRestApiClient fakeClient;
	EXPECT_CALL(fakeClient, HttpGet(_)).WillOnce(Return("{\"results\":[]}"));

	TheMovieDbRepository repository("api-key", factory, fakeClient);

	ASSERT_THROW(
		repository.FindMovieData("movie name"), MovieNotFoundException);
}