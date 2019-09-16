#include "StringHtmlEncoder.h"
#include <gtest/gtest.h>

TEST(StringHtmlEncoderTests, Encode_StringWithoutSpaces_ReturnSameString)
{
	auto result = StringHtmlEncoder::Encode("1234");

	ASSERT_EQ(result, "1234");
}

TEST(StringHtmlEncoderTests, Encode_StringWithOneSpace_ReplaceSpaceWithEncoding)
{
	auto result = StringHtmlEncoder::Encode("A B");

	ASSERT_EQ("A%2fB", result);
}

TEST(StringHtmlEncoderTests, Encode_StringWithMultipleSpaces_ReplaceSpacesWithEncoding)
{
	auto result = StringHtmlEncoder::Encode("A B C D");

	ASSERT_EQ("A%2fB%2fC%2fD", result);
}