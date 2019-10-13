#pragma once

#include "gmock/gmock.h"
#include "MovieMetaDataRepository.h"
#include "Logger.h"

class FakeMovieMetaDataRepository : public MovieMetaDataRepository
{
public:
	MOCK_METHOD1(FindMovieData, std::shared_ptr<MovieData>(const std::string& movieName));
};

class FakeLoggerFactory : public LoggerFactory
{
public:
	MOCK_METHOD0(CreateLogger, std::shared_ptr<Logger>());
};

class FakeLogger : public Logger
{
public:
	MOCK_METHOD1(LogError, void(std::string));
	MOCK_METHOD1(LogWarning, void(std::string));
};