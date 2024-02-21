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

bool Extensions::AuxCurl::GET(const std::string& URL, std::string& response, const std::vector<AuxPort::StringPair>& headers)
{
	response.clear();
	curl_easy_reset(curlHandle);
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&response);
	curl_slist* headersList = generateHeadersList(headers);
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headersList);

	CURLcode responseCode = curl_easy_perform(curlHandle);
	curl_slist_free_all(headersList);

	if (responseCode != CURLE_OK)
	{
		response = "Error in curl_easy_perform(): ";
		response += curl_easy_strerror(responseCode);
		return false;
	}
	return true;
}

bool Extensions::AuxCurl::POST(const std::string& URL, const std::vector<AuxPort::StringPair>& postFields, std::string& response, const std::vector<AuxPort::StringPair>& headers)
{
	response.clear();
	curl_easy_reset(curlHandle);
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
	AuxPort::String postFieldString = generatePostFieldString(postFields);
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postFieldString.getCString());
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&response);
	curl_slist* headersList = generateHeadersList(headers);
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headersList);

	CURLcode responseCode = curl_easy_perform(curlHandle);
	curl_slist_free_all(headersList);

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

AuxPort::String Extensions::AuxCurl::generatePostFieldString(const std::vector<AuxPort::StringPair>& postFields)
{
	if (postFields.empty()) return "";
	AuxPort::String postFieldString = postFields[0].key() + "=" + postFields[0].value();
	for (int i = 1; i < postFields.size(); i++)
	{
		postFieldString = postFieldString + "&" + postFields[i].key() + "=" + postFields[i].value();
	}
	return postFieldString;
}

curl_slist* Extensions::AuxCurl::generateHeadersList(const std::vector<AuxPort::StringPair>& headers)
{
	curl_slist* headersList = nullptr;
	for (int i = 0; i < headers.size(); i++)
	{
		headersList = curl_slist_append(headersList, (headers[i].key() + ": " + headers[i].value()).getCString());
	}
	return headersList;
}
