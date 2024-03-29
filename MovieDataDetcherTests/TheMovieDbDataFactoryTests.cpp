#include "gtest/gtest.h"
#include "TheMovieDbDataFactory.h"
#include <gmock/gmock-matchers.h>
#include <gmock/gmock-generated-matchers.h>

TEST(TheMovieDbDataFactoryTests, CreateFromJson_PassEmptyString_ReturnEmptyClass)
{
    TheMovieDbDataFactory factory;

    auto result = factory.CreateFromJson("");

    EXPECT_EQ(result->GetTitle(), "");
    EXPECT_EQ(result->GetActors().size(), 0);
    EXPECT_EQ(result->GetImdbId(), "");
    EXPECT_EQ(result->GetLengthMin(), 0);
    EXPECT_EQ(result->GetPlot(), "");
}

::std::ostream& operator<<(::std::ostream& os, const MovieData& movieData) {
return os << "Id: " << movieData.GetImdbId() << " Title: " << movieData.GetTitle() << " Plot: " << movieData.GetPlot() << " Length: " << movieData.GetLengthMin();
}

MATCHER_P4(MovieDataEq, expectedId, expectedTitle, expectedPlot, expectedLength, "Title: " + std::string(negation ? "isn't": "is") + "Equal to: " + expectedTitle)
{
     return arg.GetImdbId() == expectedId &&
        arg.GetTitle() == expectedTitle &&
        arg.GetPlot() == expectedPlot &&
        arg.GetLengthMin() == expectedLength;
}

TEST(TheMovieDbDataFactoryTests_CreateFromJson_PassValidString_ReturnMovieDetails)
{
    std::string input = "{\"id\":284052,\"imdb_id\":\"tt1211837\",\"overview\":\"The movie's plot\",\"title\":\"a movie\",\"runtime\":115}";

    TheMovieDbDataFactory factory;

    auto result = factory.CreateFromJson(input);

	ASSERT_THAT(*result, MovieDataEq("tt1211837", "a wrong movie", "The movie's plot", 115));
}

TEST(TheMovieDbDataFactoryTests, GetActorList_PassValiedStringWithOneActor_ReturnActor)
{
	std::string input = "{\"id\":550,\"cast\":[{\"cast_id\":4,\"character\":\"Tough guy\",\"credit_id\":\"1\",\"id\":12,\"name\":\"John Smith\",\"order\":0,\"profile_path\":null}],\"crew\": []}";

	TheMovieDbDataFactory factory;

	std::vector<std::string> result;
	factory.GetActors(input, result);

	EXPECT_EQ(1, result.size());
	EXPECT_EQ("John Smith", result[0]);
}

TEST(TheMovieDbDataFactoryTests, GetActorList_PassValidStringWithSeveralActors_ReturnActors)
{
	std::string input = "{\"id\":550,\"cast\":[{\"cast_id\":4,\"character\":\"lorem ipsum\",\"credit_id\":\"1\",\"id\":12,\"name\":\"John Smith\",\"order\":0,\"profile_path\":null},{\"cast_id\":5,\"character\":\"lorem ipsum\",\"id\":12,\"name\":\"Jane Doe\"},{\"cast_id\":6,\"character\":\"lorem ipsum\",\"id\":12,\"name\":\"Some Guy\"}],\"crew\": []}";

	TheMovieDbDataFactory factory;

	std::vector<std::string> result;
	factory.GetActors(input, result);

	ASSERT_THAT(result, testing::UnorderedElementsAre("John Smith", "Jane Doe", "Some Guy"));
}