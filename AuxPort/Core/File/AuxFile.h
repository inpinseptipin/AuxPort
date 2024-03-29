#ifndef AUXPORT_FILE_H
#define AUXPORT_FILE_H

/*
*			AuxPort Library
			"Generic Modules to facilitate C++ Windows Application development" - inpinseptipin

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
			DAMAGES (IN CLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
/*===================================================================================*/
#include "../Log/AuxLog.h"
#include "../String/AuxStringPair.h"
#include "../String/AuxString.h"
#include "../../Audio/Buffer/AuxBuffer.h"
#include <filesystem>
#include <fstream>
#include <functional>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

namespace AuxPort
{
	class File : virtual public ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Enum] Easy way to specify the Read/Write behavior of the File Stream
		///////////////////////////////////////////////////////////////////////////////////////
		enum Mode
		{
			Idle = 0, Read = 1, Write = 2
		};

		File();
		~File() = default;
		File(const File& file) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Virtual Function] Implement this function to specify the opening behavior of the File
		///////////////////////////////////////////////////////////////////////////////////////
		virtual bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Virtual Function] Implement this function to specify the closing behavior of the File
		///////////////////////////////////////////////////////////////////////////////////////
		virtual bool close(bool log = false) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Returns the current directory, the program is running in
		///////////////////////////////////////////////////////////////////////////////////////
		std::string getCurrentDirectory();

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Returns list of files present in the current directory
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string>& getListOfFiles(const std::string& extension = "");

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Virtual Function] Override this function to specify logging behavior
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;
	private:
		std::string defaultDirectory;
		std::vector<std::string> listOfFiles;
	protected:
		std::unique_ptr<std::ofstream> fileWriter;
		std::unique_ptr<std::ifstream> fileReader;
		std::string fileName;
		std::string fileExtension;
		std::string errorMessage;
		Mode mode;
	};
}

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	/// TextFile Class, Abstraction over C++ Standard File Handling to read ASCII based Text Files.
	/// For Example : AuxPort::TextFile textFile()
	///////////////////////////////////////////////////////////////////////////////////////
	class TextFile : public File
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// Default Constructor, Initializes the TextFile API.
		///////////////////////////////////////////////////////////////////////////////////////
		TextFile() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Default Destructor
		///////////////////////////////////////////////////////////////////////////////////////
		~TextFile() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Reads the entire text file and saves it in a String
		///////////////////////////////////////////////////////////////////////////////////////
		std::string& readFileAsString();

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Writes a line to the Text File
		///////////////////////////////////////////////////////////////////////////////////////
		void writeLineToFile(const std::string& data, bool log = false);

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Reads a line to the Text File
		///////////////////////////////////////////////////////////////////////////////////////
		bool readLineFromFile(std::string& line, bool log = false);

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Opens a stream to a text file
		///////////////////////////////////////////////////////////////////////////////////////
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) override;
		bool close(bool log = false) override;
	private:
		std::string rawData;
		std::string line;
	};
}

namespace AuxPort
{
	class BinaryFile : public File
	{
	public:
		BinaryFile() = default;
		~BinaryFile() = default;
		BinaryFile(const BinaryFile& binaryFile) = default;
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) override;
		bool close(bool log = false) override;
	private:
	};
}

namespace AuxPort
{
	class TextFormat : virtual public ILog
	{
	public:
		TextFormat() = default;
		~TextFormat() = default;
		TextFormat(const TextFormat& textFormat) = default;
		void Log() override;
	protected:
		std::string formatName;
		std::string uniqueIdentifier;
		std::string extensionName;
	public:
		std::string& getFormatName();
		std::string& getUniqueIdentifier();
		std::string& getExtensionName();
		void setExtensionName(const std::string& extensionName);
		void setUniqueIdentifier(const std::string& uniqueIdentifier);
		void setFormatName(const std::string& formatName);
		virtual void read(std::string& line, int props = 0) = 0;
		virtual void write(const std::string& line, int props = 0) = 0;
	};
}

namespace AuxPort
{
	class CSV : protected TextFile, public TextFormat
	{
	public:
		CSV();
		~CSV() = default;
		CSV(const CSV& csv) = default;
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool containsHeader = false, const char& delimiter = ',', bool log = false);
		bool close(bool log = false);	
		void read(std::vector<std::vector<std::string>>& data, std::vector<std::string>& headers = std::vector<std::string>());
		bool getDataRow(std::vector<std::string>& dataRow, size_t rowNum);
		void write();
		void setHeader(const std::vector<std::string>& header);
		void addDataRow(const std::vector<std::string>& dataRow);
		void write(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& header = std::vector<std::string>());
		void Log() override;
	private:
		char delimiter;
		bool containsHeader;
		std::vector<std::string> header;
		std::vector<std::vector<std::string>> data;

		void read(std::string& line, int props = 0) {};
		void write(const std::string& line, int props = 0) {};
	};
}

#endif