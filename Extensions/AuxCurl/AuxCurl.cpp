#include "AuxCurl.h"

Extensions::AuxCurl::AuxCurl()
{
	curlHandle = curl_easy_init();
	AuxAssert(curlHandle, "Error creating CURL Handle!");

	headersList = nullptr;
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&responseData);
}

Extensions::AuxCurl::~AuxCurl()
{
	curl_slist_free_all(headersList);
	curl_easy_cleanup(curlHandle);
}

void Extensions::AuxCurl::setURL(const std::string& URL)
{
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
}

void Extensions::AuxCurl::setHeaders(const std::vector<AuxPort::StringPair>& headers)
{
	curl_slist_free_all(headersList);
	for (int i = 0; i < headers.size(); i++)
	{
		headersList = curl_slist_append(headersList, (headers[i].key() + ":" + headers[i].value()).getCString());
	}
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headersList);
}

void Extensions::AuxCurl::setPostFields(const std::vector<AuxPort::StringPair>& postFieldValuePairs)
{
	postData = "{";
	if (!postFieldValuePairs.empty())
	{
		postData = postData + "\'" + postFieldValuePairs[0].key() + "\': \'" + postFieldValuePairs[0].value() + "\'";
		for (int i = 1; i < postFieldValuePairs.size(); i++)
		{
			postData = postData + ",\'" + postFieldValuePairs[i].key() + "\': \'" + postFieldValuePairs[i].value() + "\'";
		}
	}
	postData.pushBack("}");
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postData.getCString());
}

void Extensions::AuxCurl::setResponseHandler(const std::function<void(const std::string& responseData)>& responseHandler)
{
	this->responseHandler = responseHandler;
}

bool Extensions::AuxCurl::sendRequest(const RequestType& type)
{
	switch (type)
	{
	case GET:
		curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);
		break;
	case POST:
		curl_easy_setopt(curlHandle, CURLOPT_POST, 1L);
		break; 
	}

	CURLcode responseCode = curl_easy_perform(curlHandle);
	if (responseCode != CURLE_OK)
	{
		responseData = "Error: ";
		responseData += curl_easy_strerror(responseCode);
		responseHandler(responseData);
		return false;
	}
	responseHandler(responseData);
	return true;
}

std::string Extensions::AuxCurl::getResponseAsString()
{
	return responseData;
}

size_t Extensions::AuxCurl::writeCallback(void* data, size_t size, size_t nmemb, void* clientp)
{
	std::string* responseDataPtr = (std::string*)clientp;
	responseDataPtr->append((const char*)data, size * nmemb);
	return size * nmemb;
}