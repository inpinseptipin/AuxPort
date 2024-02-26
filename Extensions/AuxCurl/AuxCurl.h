#ifndef AUXPORT_CURL_H
#define AUXPORT_CURL_H
/*
			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2023, Satyarth Arora
			All rights reserved.

			Redistribution and use in source and binary forms, with or without
			modification, are permitted provided that the following conditions are met:

			1. Redistributions of source code must retain the above copyright notice, this
			   list of conditions and the following disclaimer.

			2. Redistributions in binary form must reproduce the above copyright notice,
			   this list of conditions and the following disclaimer in the documentation
			   and/or other materials provided with the distribution.

			3. Neither the name of the copyright holder nor the names of its
			   contributors may be used to endorse or promote products derived from
			   this software without specific prior written permission.

			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#define CURL_STATICLIB
#include "curl/curl.h"
#include "AuxPort.h"
#include <string>

namespace Extensions
{
	class AuxCurl
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Specifies the Type of Request to perform
		///////////////////////////////////////////////////////////////////////////////////////
		enum RequestType {GET, POST};
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Initializes the AuxCurl Object
		///////////////////////////////////////////////////////////////////////////////////////
		AuxCurl();

		///////////////////////////////////////////////////////////////////////////////////////	
		/// Destructs and cleans up the AuxCurl Object
		///////////////////////////////////////////////////////////////////////////////////////
		~AuxCurl();
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Sets the target URL for the Request
		///////////////////////////////////////////////////////////////////////////////////////
		void setURL(const std::string& URL);
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Sets the Request Headers
		/// To unset a header, provide the header name with an empty value.
		///////////////////////////////////////////////////////////////////////////////////////
		void setHeaders(const std::vector<AuxPort::StringPair>& headers);
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Sets the HTTP POST Fields. The POST fields are sent in JSON format.
		///////////////////////////////////////////////////////////////////////////////////////
		void setPostFields(const std::vector<AuxPort::StringPair>& postFieldValuePairs);
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Sets a custom handler to handle the Response Data. The passed function/lambda will be called after completion of an request and will receive the Response Data as a string argument.
		/// You can provide access to local variables using lambda captues.
		/// 
		/// Example Usage:
		///	Extensions::AuxCurl obj;
		///	...
		///	std::string res;
		///	obj.setResponseHandler( [&res] (const std::string& responseData) { res = responseData; } );
		///////////////////////////////////////////////////////////////////////////////////////
		void setResponseHandler(const std::function<void(const std::string& responseData)>& responseHandler);
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Sends the request to the target URL and executes the response Handler upon completion
		/// Returns true if there was no error in the transfer, oherwise false.
		///////////////////////////////////////////////////////////////////////////////////////
		bool sendRequest(const RequestType& type);
		
		///////////////////////////////////////////////////////////////////////////////////////	
		/// Returns the Response Data of the last sent Request as a String Object
		///////////////////////////////////////////////////////////////////////////////////////
		std::string getResponseAsString();
	private:
		CURL* curlHandle;
		curl_slist* headersList;
		AuxPort::String postData;
		std::string responseData;
		std::function<void(const std::string& responseData)> responseHandler;
		static size_t writeCallback(void* data, size_t size, size_t nmemb, void* clientp);
	};
}

#endif