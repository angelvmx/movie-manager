#include "pch.h"
#include "ApiKey.h"
#include "CppUnitTest.h"
#include "MetaDataProcessor.h"
#include "MovieData.h"
#include "TheMovieDbDataFactory.h"
#include "TheMovieDbRepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MovieDataFetcherMSTest
{
	TEST_CLASS(MetaDataProcessorTests)
	{
		TheMovieDbDataFactory dataFactory;
		TheMovieDbRepository* repository;
		MetaDataProcessor* processor;
		RestApiClient client;

	public:
		MetaDataProcessorTests()
		{
			repository = new TheMovieDbRepository(MY_API_KEY, dataFactory, client);
			processor = new MetaDataProcessor(*repository);
		}

		~MetaDataProcessorTests()
		{
			delete processor;
			delete repository;
		}

		TEST_METHOD(ProcessMovies_PassEmptyMovieList_ReturnEmptyResult)
		{
			Movies result;
			processor->ProcessMovies({}, result);

			Assert::AreEqual<size_t>(0, result.size());
		}

		TEST_METHOD(ProcessMovies_PassValidMovie_ReturnMovieData)
		{
			Movies result;
			processor->ProcessMovies({"Batman Begins"}, result);

			Assert::AreEqual<rsize_t>(1, result.size());
			Assert::AreEqual("Batman Begins", result[0]->GetTitle().c_str());
		}

		TEST_METHOD(ProcessMovies_PassValidMovies_ReturnMoviesData)
		{
			Movies result;
			processor->ProcessMovies({"Batman Begins", "Apocalypse Now", "Dumb and Dumber"}, result);

			Assert::AreEqual<size_t>(3, result.size());
			Assert::AreEqual("Batman Begins", result[0]->GetTitle().c_str());
			Assert::AreEqual("Apocalypse Now", result[1]->GetTitle().c_str());
			Assert::AreEqual("Dumb and Dumber", result[2]->GetTitle().c_str());
		}
	};
}
