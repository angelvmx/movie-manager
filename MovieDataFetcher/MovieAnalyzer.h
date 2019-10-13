#pragma once

#include "MetaDataProcessor.h"
#include "DAL.h"
#include "FileNotFoundException.h"

template <class TStream>
class MovieAnalyzer
{
	MovieMetaDataRepository& m_repository;
	DataLayer &m_dal;

public:
	MovieAnalyzer(MovieMetaDataRepository& repository, DataLayer& dal) : m_repository(repository), m_dal(dal) {}
	~MovieAnalyzer() {}

	void ProcessFromFile(TStream& filestream);

private:
	static void ReadFile(TStream& filestream, std::vector<std::basic_string<char>>& movieNames);
};

template <class TStream>
void MovieAnalyzer<TStream>::ProcessFromFile(TStream& filestream)
{
	std::vector<std::string> movieNames;

	ReadFile(filestream, movieNames);

	Movies result;

	MetaDataProcessor processor(m_repository);
	processor.ProcessMovies(movieNames, result);

	for (auto movie : result)
	{
		if (m_dal.MovieExist(movie->GetTitle()))
		{
			m_dal.Update(movie);
		}
		else
		{
			m_dal.Create(movie);
		}
	}

}

template <class TStream>
void MovieAnalyzer<TStream>::ReadFile(TStream& filestream, std::vector<std::basic_string<char>>& movieNames)
{
	char movieName[1024];

	if (!filestream.is_open())
	{
		throw FileNotFoundException();
	}

	while (!filestream.eof())
	{
		filestream.getline(movieName, 1024);
		movieNames.push_back(movieName);
	}

}