#include "stdafx.h"
#include <gtest/gtest.h>

#include <vector>
#include "MetaDataProcessor.h"
#include "MovieData.h"

using namespace std;

TEST(ProcessMovies_PassEmptyMovieList_ReturnEmptyResult)
{
	MetaDataProcessor processor;
	Movies result;

	processor.ProcessMovies({}, result);

	ASSERT_EQ(0, result.size());
}
