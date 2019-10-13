#include "MovieAnalyzer.h"
#include <gtest/gtest.h>
#include "FakeMovieMetaDataRepository.h"

using namespace testing;

class FakeStream
{
public:
	MOCK_METHOD1(open, void(std::string));
	MOCK_CONST_METHOD0(is_open, bool());
	MOCK_METHOD0(getstring, std::string());
	MOCK_METHOD0(close, void());
	MOCK_METHOD0(eof, bool());

	void getline(char* output, size_t size)
	{
		std::memcpy(output, getstring().c_str(), size);
	}
};

TEST(MovieAnalyzerTests, ProcessFromFile_FileIsEmpty_DoNotCallDB)
{
	FakeMovieMetaDataRepository fakeRepository;

	MovieAnalyzer<FakeStream> analyzer(fakeRepository);

	NiceMock<FakeStream> fakeStream;
	EXPECT_CALL(fakeStream, is_open()).WillRepeatedly(Return(true));
	EXPECT_CALL(fakeStream, eof()).WillRepeatedly(Return(true));

	analyzer.ProcessFromFile(fakeStream);

	// ???
}