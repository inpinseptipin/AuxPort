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
#include <memory>

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

namespace AuxPort
{
#if AUXPORT_CXX_VER >= 17
	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief The Directory class provides an interface for interacting with directories and files.
	/// It offers functionalities to retrieve information about files and directories.
	/// @details
	/// Example Usage:
	/// @code
	/// Directory dir;
	/// dir.setDirectory("/path/to/directory");
	/// uint32_t textFileCount = dir.count("txt");
	/// @endcode
	///////////////////////////////////////////////////////////////////////////////////////
	class Directory : public ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Specifies whether to list Files or Directories or Both
		///////////////////////////////////////////////////////////////////////////////////////
		enum Type
		{
			Dir, File, All
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Specifies the format of the path (Relative or Absolute).
		///////////////////////////////////////////////////////////////////////////////////////
		enum PathFormat
		{
			Relative, Absolute
		};
		
		Directory();
		~Directory() = default;
		Directory(const Directory& directory) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the current working directory. This function accepts the absolute path of the directory.
		/// @note Use any separator for paths (Both '/' and '\' will work).
		///////////////////////////////////////////////////////////////////////////////////////
		void setDirectory(const std::string& absolutePath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Counts the number of files with the specified extension in the current working directory.
		/// @note The extension parameter needs to be passed along with dot(.)
		/// Example: ".mp3"
		///////////////////////////////////////////////////////////////////////////////////////
		uint32_t count(const std::string& fileExtension);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Counts the number of files of different extensions in the current working directory. 
		/// @returns Returns a hashmap with file extensions as keys and the number of files as the value.
		///////////////////////////////////////////////////////////////////////////////////////
		std::unordered_map<std::string, uint32_t> count();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a list of entries (Files, Directories or Both) present in the current working
		/// directory.
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> getList(Type type = Type::File, PathFormat pathFormat = PathFormat::Absolute);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a list of files with the specified extension present in the current working
		/// directory. It returns the absolute paths of the files.
		/// @note The extension parameter needs to be passed along with dot(.)
		/// Example: ".mp3"
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string> getListOfFiles(const std::string& fileExtension);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Logs the details about current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the size (in bytes) of the current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		unsigned long long getSize();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the size (in bytes) of a regular file or directory in current working directory.
		/// @note Use any separator for paths (Both '/' and '\\' work).
		/// @note The path should be valid. In case of a file, it should correspond to a regular file.
		///////////////////////////////////////////////////////////////////////////////////////
		unsigned long long getSize(const std::string& relativePath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the last write time of the current working directory
		///////////////////////////////////////////////////////////////////////////////////////
		std::time_t getLastWriteTime();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the last write time of a file/directory in current working directory
		/// @note Use any separator for paths (Both '/' and '\\' work).
		/// @note The path should be valid.
		///////////////////////////////////////////////////////////////////////////////////////
		std::time_t getLastWriteTime(const std::string& relativePath);
	
	private:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Helper Function to get the last write time for a path.
		/// @note The given path should be valid.
		///////////////////////////////////////////////////////////////////////////////////////
		static std::time_t _getLastWriteTime(const std::filesystem::path& path);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Helper Function to calculate the size of a directory.
		/// @note The given path should be valid and should correspond to a directory.
		///////////////////////////////////////////////////////////////////////////////////////
		static unsigned long long _getDirectorySize(const std::filesystem::path& directoryPath);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Helper Function which counts the number of files and number of directories in the 
		/// current working directory.
		///////////////////////////////////////////////////////////////////////////////////////
		void _count();
		
		std::filesystem::path path;
		uint32_t numberOfFiles = 0;
		uint32_t numberOfDirectories = 0;
	};
#endif

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an interface for working with files
	///////////////////////////////////////////////////////////////////////////////////////
	class File : virtual public ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Easy way to specify the Read/Write behavior of the File Stream
		///////////////////////////////////////////////////////////////////////////////////////
		enum Mode
		{
			Idle = 0, Read = 1, Write = 2
		};

		File();
		~File() = default;
		File(const File& file) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Implement this function to specify the opening behavior of the File
		///////////////////////////////////////////////////////////////////////////////////////
		virtual bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Implement this function to specify the closing behavior of the File
		///////////////////////////////////////////////////////////////////////////////////////
		virtual bool close(bool log = false) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the current directory, the program is running in
		///////////////////////////////////////////////////////////////////////////////////////
		std::string getCurrentDirectory();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns list of files present in the current directory
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::string>& getListOfFiles(const std::string& extension = "");

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Override this function to specify logging behavior
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
	/// @brief Abstraction over C++ Standard File Handling for ASCII based Text Files.
	/// 
	/// For Example :
	/// @code AuxPort::TextFile textFile(); @endcode
	///////////////////////////////////////////////////////////////////////////////////////
	class TextFile : public File
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Default Constructor, Initializes the TextFile API.
		///////////////////////////////////////////////////////////////////////////////////////
		TextFile() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Default Destructor
		///////////////////////////////////////////////////////////////////////////////////////
		~TextFile() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads the entire text file and saves it in a String
		///////////////////////////////////////////////////////////////////////////////////////
		std::string& readFileAsString();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Writes a line to the Text File
		///////////////////////////////////////////////////////////////////////////////////////
		void writeLineToFile(const std::string& data, bool log = false);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads a line to the Text File
		///////////////////////////////////////////////////////////////////////////////////////
		bool readLineFromFile(std::string& line, bool log = false);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Opens the given file as a text file
		///////////////////////////////////////////////////////////////////////////////////////
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) override;
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Closes current text file stream
		///////////////////////////////////////////////////////////////////////////////////////
		bool close(bool log = false) override;
	private:
		std::string rawData;
		std::string line;
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an interface for working with binary files
	///////////////////////////////////////////////////////////////////////////////////////
	class BinaryFile : public File
	{
	public:
		BinaryFile() = default;
		~BinaryFile() = default;
		BinaryFile(const BinaryFile& binaryFile) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Opens the given file as a binary file
		///////////////////////////////////////////////////////////////////////////////////////
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Closes current binary file stream
		///////////////////////////////////////////////////////////////////////////////////////
		bool close(bool log = false) override;
	private:
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an interface to manage File Format Details
	///////////////////////////////////////////////////////////////////////////////////////
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
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Return the format name
		///////////////////////////////////////////////////////////////////////////////////////	
		std::string& getFormatName();
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Return the unique identifier for the text format
		///////////////////////////////////////////////////////////////////////////////////////	
		std::string& getUniqueIdentifier();
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the extension name
		///////////////////////////////////////////////////////////////////////////////////////	
		std::string& getExtensionName();
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the extension name
		///////////////////////////////////////////////////////////////////////////////////////	
		void setExtensionName(const std::string& extensionName);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the unique identifier for the text format
		///////////////////////////////////////////////////////////////////////////////////////	
		void setUniqueIdentifier(const std::string& uniqueIdentifier);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the format name
		///////////////////////////////////////////////////////////////////////////////////////	
		void setFormatName(const std::string& formatName);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Implement this function to specify the read operation for the file
		///////////////////////////////////////////////////////////////////////////////////////	
		virtual void read(std::string& line, int props = 0) = 0;
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Implement this function to specify the write operation for the file
		///////////////////////////////////////////////////////////////////////////////////////	
		virtual void write(const std::string& line, int props = 0) = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides functionality to read and write CSV Files.
	///////////////////////////////////////////////////////////////////////////////////////
	class CSV : protected TextFile, public TextFormat
	{
	public:
		CSV();
		~CSV() = default;
		CSV(const CSV& csv) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Opens a CSV File
		///////////////////////////////////////////////////////////////////////////////////////
		bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool containsHeader = false, const char& delimiter = ',', bool log = false);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Closes the stream to currently opened CSV File
		///////////////////////////////////////////////////////////////////////////////////////
		bool close(bool log = false);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads data from a CSV file and stores it in the 2-d Vector.
		/// @note If the containsHeader Flag has been set to false, all rows in the file will be considered as data rows.
		/// Otherwise, the first row will not be considered a data row and will not be populated in the given vector.
		///////////////////////////////////////////////////////////////////////////////////////
		void read(std::vector<std::vector<std::string>>& data);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads data from a CSV file.
		/// @note If the containsHeader Flag has been set to false, all rows in the file will be considered as data rows and there will be no header rows.
		/// Otherwise, the first row will be considered a header row and all successive rows will be considered data rows.
		///////////////////////////////////////////////////////////////////////////////////////
		void read(std::vector<std::vector<std::string>>& data, std::vector<std::string>& headers);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads a specific data row from the file.
		/// @returns true if the read was sucessful. Otherwise, it returns false in case the given rowNum is greater than number of data rows in the file.
		/// @note If the containsHeader Flag has been set to false, all rows in the file will be considered as data rows and there will be no header rows.
		/// Otherwise, the first row will be considered a header row and all successive rows will be considered data rows.
		///////////////////////////////////////////////////////////////////////////////////////
		bool getDataRow(std::vector<std::string>& dataRow, size_t rowNum);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the header row to be written to the CSV File.
		/// @note This function does not write the headers to CSV File, instead, it sets the headers which will be written to file later using write().
		///////////////////////////////////////////////////////////////////////////////////////
		void setHeader(const std::vector<std::string>& header);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Adds a data row to be written to the CSV File.
		/// @note This function does not write the data row to CSV File. Added data rows are written to file when write() is called.
		///////////////////////////////////////////////////////////////////////////////////////
		void addDataRow(const std::vector<std::string>& dataRow);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Writes a CSV file using information set through addDataRow(), setHeader() functions.
		/// @note File must be opened in Write mode.
		/// @note If containsHeader flag is set to false, then headers will not be written (even if they have been set using setHeaders()).
		///////////////////////////////////////////////////////////////////////////////////////		
		void write();
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Writes a CSV file with the given data and header rows.
		/// @note File must be opened in Write mode.
		/// @note If containsHeader flag is set to false, then headers will not be written (even if they have been set using setHeaders()).
		///////////////////////////////////////////////////////////////////////////////////////	
		void write(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& header = std::vector<std::string>());
	
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Logs the file info
		///////////////////////////////////////////////////////////////////////////////////////
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