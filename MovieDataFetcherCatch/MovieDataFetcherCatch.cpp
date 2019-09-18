// MovieDataFetcherCatch.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "stdafx.h"

#define CATCH_CONFIG_MAIN
#include "Catch/catch.hpp"
#include "ApiKey.h"
#include "MetaDataProcessor.h"
#include "MovieData.h"
#include "TheMovieDbRepository.h"
#include "TheMovieDbDataFactory.h"

TEST_CASE("ProcessMovies returns movie data")
{
	TheMovieDbDataFactory factory;
	TheMovieDbRepository repository(MY_API_KEY, factory);
	MetaDataProcessor processor(repository);

	Movies result;
	SECTION("Return empty result for empty list")
	{
		processor.ProcessMovies({}, result);

		REQUIRE(result.size() == 0);
	}

	SECTION("Get result for one movie")
	{
		processor.ProcessMovies({"Batman Begins"}, result);

		CHECK(result.size() == 1);
		REQUIRE(result[0]->GetTitle() == "Batman Begins");
	}

	SECTION("Get results for several movies")
	{
		processor.ProcessMovies({"Batman Begins", "Apocalypse Now", "Dumb and Dumber"}, result);

		CHECK(result.size() == 3);
		CHECK(result[0]->GetTitle() == "Batman Begins");
		CHECK(result[1]->GetTitle() == "Apocalypse Now");
		CHECK(result[2]->GetTitle() == "Dumb and Dumber");
	}
}