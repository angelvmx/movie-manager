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

class FakeDataLayer : public DataLayer
{
public:
	MOCK_METHOD1(MovieExist, bool(const std::string&));
	MOCK_METHOD1(Create, void(std::shared_ptr<MovieData>));
	MOCK_METHOD1(Update, void(std::shared_ptr<MovieData>));
};

TEST(MovieAnalyzerTests, ProcessFromFile_FileIsEmpty_DoNotCallDB)
{
	FakeMovieMetaDataRepository fakeRepository;
	FakeDataLayer fakeDataLayer;
	EXPECT_CALL(fakeDataLayer, Create(_)).Times(0);
	EXPECT_CALL(fakeDataLayer, Update(_)).Times(0);

	MovieAnalyzer<FakeStream> analyzer(fakeRepository, fakeDataLayer);

	NiceMock<FakeStream> fakeStream;
	EXPECT_CALL(fakeStream, is_open()).WillRepeatedly(Return(true));
	EXPECT_CALL(fakeStream, eof()).WillRepeatedly(Return(true));

	analyzer.ProcessFromFile(fakeStream);
}