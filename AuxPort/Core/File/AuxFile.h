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
#include <unordered_map>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

namespace AuxPort
{
#if AUXPORT_CXX_VER >= 17
	///////////////////////////////////////////////////////////////////////////////////////
	/// The Directory class provides an interface for interacting with directories and files.
	/// It offers functionalities to retrieve information about files and directories.
	/// Example Usage:
	/// Directory dir;
	/// dir.setDirectory("/path/to/directory");
	/// uint32_t textFileCount = dir.count("txt");
	///////////////////////////////////////////////////////////////////////////////////////
	class Directory : public ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// Specifies whether to list Files or Directories or Both
		///////////////////////////////////////////////////////////////////////////////////////
		enum Type
		{
			Dir, File, All
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// Specifies the format of the path (Relative or Absolute).
		///////////////////////////////////////////////////////////////////////////////////////
		enum PathFormat
		{
			Relative, Absolute
		};
		
		Directory();
		~Directory() = default;
		Directory(const Directory& directory) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Sets the current working directory. This function accepts the absolute path of the directory.
		/// Use any separator for paths (Both '/' and '\\' work).
		///////////////////////////////////////////////////////////////////////////////////////
		void setDirectory(const std::string& absolutePath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Counts the number of files with the specified extension in the current working directory.
		/// The extension parameter needs to be passed along with dot(.)
		/// Example: ".mp3"
		///////////////////////////////////////////////////////////////////////////////////////
		uint32_t count(const std::string& fileExtension);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Counts the number of files of different extensions in the current working directory. 
		/// Returns a hashmap with file extensions as keys and the number of files as the value.
		///////////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, uint32_t> count();

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns a list of entries (Files, Directories or Both) present in the current working
		/// directory. 
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> getList(Type type = Type::File, PathFormat pathFormat = PathFormat::Absolute);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns a list of files with the specified extension present in the current working
		/// directory. It returns the absolute paths of the files.
		/// The extension parameter needs to be passed along with dot(.)
		/// Example: ".mp3"
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> getListOfFiles(const std::string& fileExtension);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Logs the details about current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns the size (in bytes) of the current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		unsigned long long getSize();

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns the size (in bytes) of a regular file or directory in current working directory.
		/// The path should be valid. In case of a file, it should correspond to a regular file.
		/// Use any separator for paths (Both '/' and '\\' work).
		///////////////////////////////////////////////////////////////////////////////////////
		unsigned long long getSize(const std::string& relativePath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns the last write time of the current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		std::time_t getLastWriteTime();

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns the last write time of a file/directory in current working directory
		/// The path should be valid.
		/// Use any separator for paths (Both '/' and '\\' work).
		///////////////////////////////////////////////////////////////////////////////////////
		std::time_t getLastWriteTime(const std::string& relativePath);
	
	private:
		///////////////////////////////////////////////////////////////////////////////////////
		/// Helper Function to get the last write time for a path.
		/// The given path should be valid.
		///////////////////////////////////////////////////////////////////////////////////////
		static std::time_t _getLastWriteTime(const std::filesystem::path& path);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Helper Function to calculate the size of a directory.
		/// The given path should be valid and should correspond to a directory.
		///////////////////////////////////////////////////////////////////////////////////////
		static unsigned long long _getDirectorySize(const std::filesystem::path& directoryPath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Helper Function which counts the number of files and number of directories in the 
		/// current working directory.
		///////////////////////////////////////////////////////////////////////////////////////
		void _count();
		
		std::filesystem::path path;
		uint32_t numberOfFiles = 0;
		uint32_t numberOfDirectories = 0;
	};
#endif

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