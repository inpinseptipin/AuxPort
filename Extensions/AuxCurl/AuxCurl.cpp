#include "AuxCurl.h"

Extensions::AuxCurl::AuxCurl()
{
	curlHandle = curl_easy_init();
	AuxAssert(curlHandle, "Error creating CURL Handle!");
}

Extensions::AuxCurl::~AuxCurl()
{
	curl_easy_cleanup(curlHandle);
}

bool Extensions::AuxCurl::GET(const std::string& URL, std::string& response)
{
	curl_easy_reset(curlHandle);
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&response);

	response.clear();
	CURLcode responseCode = curl_easy_perform(curlHandle);

	if (responseCode != CURLE_OK)
	{
		response = "Error in curl_easy_perform(): ";
		response += curl_easy_strerror(responseCode);
		return false;
	}
	return true;
}

bool Extensions::AuxCurl::POST(const std::string& URL, const std::string& postFields, std::string& response)
{
	curl_easy_reset(curlHandle);
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postFields.data());
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&response);

	response.clear();
	CURLcode responseCode = curl_easy_perform(curlHandle);

	if (responseCode != CURLE_OK)
	{
		response = "Error in curl_easy_perform(): ";
		response += curl_easy_strerror(responseCode);
		return false;
	}
	return true;
}

size_t Extensions::AuxCurl::writeCallback(void* data, size_t size, size_t nmemb, void* clientp)
{
	std::string* responseStringPtr = (std::string*)clientp;
	responseStringPtr->append((const char*)data, size * nmemb);
	return size * nmemb;
}
