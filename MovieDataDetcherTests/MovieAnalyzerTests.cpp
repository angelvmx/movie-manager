#include "MovieAnalyzer.h"
#include <gtest/gtest.h>
#include "FakeMovieMetaDataRepository.h"

TEST(MovieAnalyzerTests, ProcessFromFile_FileIsEmpty_DoNotCallDB)
{
	FakeMovieMetaDataRepository fakeRepository;

	MovieAnalyzer analyzer(fakeRepository);

	std::ifstream fileStream;
	fileStream.open("dummy");

	analyzer.ProcessFromFile(fileStream);

	// ???
}