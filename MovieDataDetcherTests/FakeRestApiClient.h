#pragma once

#include "RestApiClient.h"

class FakeRestApiClient : public RestApiClient
{
	std::string m_result;
public:
	FakeRestApiClient(std::string result) :m_result(result){}
	std::string HttpGet(std::string& url) override {
		return m_result;
	}
};