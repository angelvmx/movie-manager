#include "gtest/gtest.h"
#include "TheMovieDbDataFactory.h"

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

TEST(TheMovieDbDataFactoryTests_CreateFromJson_PassValidString_ReturnMovieDetails)
{
    std::string input = "{\"id\":284052,\"imdb_id\":\"tt1211837\",\"overview\":\"The movie's plot\",\"title\":\"a movie\",\"runtime\":115}";

    TheMovieDbDataFactory factory;

    auto result = factory.CreateFromJson(input);

    EXPECT_EQ(result->GetImdbId(), "tt1211837");
    EXPECT_EQ(result->GetTitle(), "a movie");
    EXPECT_EQ(result->GetPlot(), "The movie's plot");
    EXPECT_EQ(result->GetLengthMin(), 115);
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

	EXPECT_EQ(3, result.size());
	EXPECT_EQ("John Smith", result[0]);
	EXPECT_EQ("Jane Doe", result[1]);
	EXPECT_EQ("Some Guy", result[2]);
}