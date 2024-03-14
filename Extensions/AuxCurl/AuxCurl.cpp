#include "AuxCurl.h"

AuxPort::Extensions::AuxCurl::AuxCurl()
{
	curlHandle = curl_easy_init();
	AuxAssert(curlHandle, "Error creating CURL Handle!");

	headersList = nullptr;
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void*)&responseData);
}

AuxPort::Extensions::AuxCurl::~AuxCurl()
{
	curl_slist_free_all(headersList);
	curl_easy_cleanup(curlHandle);
}

void AuxPort::Extensions::AuxCurl::setURL(const std::string& URL)
{
	curl_easy_setopt(curlHandle, CURLOPT_URL, URL.data());
}

void AuxPort::Extensions::AuxCurl::addHeaders(const std::vector<AuxPort::StringPair>& headers)
{
	for (uint32 i = 0; i < headers.size(); i++)
	{
		headersList = curl_slist_append(headersList, (headers[i].key() + ":" + headers[i].value()).getCString());
	}
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headersList);
}

void AuxPort::Extensions::AuxCurl::clearHeaders()
{
	curl_slist_free_all(headersList);
	headersList = nullptr;	// Calling curl_slist_free_all does not guarantee the pointer to be nullptr
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, nullptr);
}

void AuxPort::Extensions::AuxCurl::setPostFields(const std::string& postFields)
{
	this->postFields = postFields;
	curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, this->postFields.c_str());
}

void AuxPort::Extensions::AuxCurl::setResponseHandler(const std::function<void(const std::string& responseData)>& responseHandler)
{
	this->responseHandler = responseHandler;
}

bool AuxPort::Extensions::AuxCurl::sendRequest(const RequestType& type)
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

	// Making sure responseData does not contain previous responses
	responseData = "";
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

std::string AuxPort::Extensions::AuxCurl::getResponseAsString()
{
	return responseData;
}

size_t AuxPort::Extensions::AuxCurl::writeCallback(void* data, size_t size, size_t nmemb, void* clientp)
{
	std::string* responseDataPtr = (std::string*)clientp;
	responseDataPtr->append((const char*)data, size * nmemb);
	return size * nmemb;
}