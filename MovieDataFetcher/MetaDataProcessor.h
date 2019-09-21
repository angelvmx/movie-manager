#pragma once

#include <vector>
#include <string>
#include "MovieMetaDataRepository.h"
#include <memory>
#include "Logger.h"

class MovieData;

typedef std::vector<std::shared_ptr<MovieData>> Movies;

class MetaDataProcessor
{
	MovieMetaDataRepository& m_repository;
	std::shared_ptr<LoggerFactory> m_loggerFactory;

public:
	MetaDataProcessor(MovieMetaDataRepository& respository);
	MetaDataProcessor(MovieMetaDataRepository& repository, std::shared_ptr<LoggerFactory> loggerFactory);
	~MetaDataProcessor();

	void ProcessMovies(const std::vector<std::string>& movieNames, Movies& result);
};