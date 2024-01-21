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

/*===================================================================================*/
#include "AuxFile.h"
#include <cstdlib>
#include <assert.h>

AuxPort::File::File()
{
#if _WIN32 || _WIN64
	char buff[FILENAME_MAX];
	auto getcwd = GetCurrentDir(buff, FILENAME_MAX);
	std::string location(buff);
	this->defaultDirectory = location;
#else
	this->defaultDirectory = "";
#endif
	this->mode = Idle;
}


std::vector<std::string>& AuxPort::File::getListOfFiles(const std::string& extension)
{
#if _WIN32 || _WIN64
	WIN32_FIND_DATA data;
	auto directory = defaultDirectory + "\\*";
	HANDLE hFind = FindFirstFile(LPCSTR(directory.c_str()), &data);
	listOfFiles.clear();
	std::string file;
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			file = data.cFileName;
			auto loc = file.find('.');
			if(loc > 0 && loc < FILENAME_MAX)
				listOfFiles.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
#endif
	return listOfFiles;
}

void AuxPort::File::Log()
{
	setColour(AuxPort::ColourType::Cyan);
	std::cout << "Directory : "<<defaultDirectory << std::endl;
	switch (this->mode)
	{
	case Mode::Idle:std::cout << "Stream Mode : Idle" << std::endl;
		break;
	case Mode::Read:std::cout << "Stream Mode : Read" << std::endl;
		break;
	case Mode::Write:std::cout << "Stream Mode : Write" << std::endl;
		break;
	}
	this->fileName == "" ? std::cout << "File Name : N/A" << std::endl : std::cout << "File Name : " + fileName << std::endl;
	this->fileName == "" ? std::cout << "Full Path : N/A" << std::endl : std::cout << "Full Path : " << defaultDirectory + "\\" + fileName << std::endl;
	
	setColour(AuxPort::ColourType::White);
}


std::string AuxPort::File::getCurrentDirectory()
{
	return defaultDirectory;
}



bool AuxPort::TextFile::open(const std::string& fileName,const Mode& mode, bool log)
{
	if (mode == Mode::Read)
	{
		if(log)
			AuxPort::Logger::Log("Trying to Open " + fileName);
		try
		{
			fileReader.reset(new std::ifstream(fileName));
			if (log)
			{
				if (fileReader->is_open())
					Logger::Log("Successfully Opened " + fileName);
			}
			this->fileName = fileName;
			auto dotIndex = fileName.find('.');
			this->fileExtension = fileName.substr(dotIndex+1, fileName.size() - dotIndex);
		}
		catch (std::ifstream::failure failure)
		{
			AuxPort::Logger::Log("Failed to open " + fileName, AuxPort::LogType::Error, AuxPort::ColourType::Red);
		}
		
		this->mode = mode;
		return fileReader->is_open();
	}
	else if (mode == Mode::Write)
	{
		if(log)
			AuxPort::Logger::Log("Trying to Open " + fileName); //char(28)
		try
		{
			fileWriter.reset(new std::ofstream(fileName));
			auto open = fileWriter->is_open();
			if (log)
			{
				open == true ? AuxPort::Logger::Log(fileName + " opened successfully", AuxPort::LogType::Success, AuxPort::ColourType::Green) :
					AuxPort::Logger::Log("Failed to open " + fileName, AuxPort::LogType::Error, AuxPort::ColourType::Red);
			}
			this->mode = mode;
			this->fileName = fileName;
			auto dotIndex = fileName.find('.');
			this->fileExtension = fileName.substr(dotIndex + 1, fileName.size() - dotIndex);
		}
		catch (std::ofstream::failure fail)
		{
			AuxPort::Logger::Log("Failed to open " + fileName, AuxPort::LogType::Error, AuxPort::ColourType::Red);
		}
		return fileWriter->is_open();
	}
	else
	{
		return false;
	}
}

void AuxPort::TextFile::close(bool log)
{
	if (log)
		AuxPort::Logger::Log("Trying to close the file");
	if (mode == Mode::Read && fileReader->is_open())
	{
		try
		{
			fileReader->close();
		}
		catch(std::ifstream::failure fail)
		{
			AuxPort::Logger::Log("Exception closing file", AuxPort::LogType::Error, AuxPort::ColourType::Red);
		}	
	}
	if (mode == Mode::Write && fileWriter->is_open())
	{
		try
		{
			fileWriter->close();
		}
		catch (std::ifstream::failure fail)
		{
			AuxPort::Logger::Log("Exception closing file", AuxPort::LogType::Error, AuxPort::ColourType::Red);
		}
		
	}
	if (log)
		AuxPort::Logger::Log("File Closed Successfully", AuxPort::LogType::Success, AuxPort::ColourType::Green);
}

std::string& AuxPort::TextFile::readFileAsString()
{
	if (fileReader->is_open())
	{
		std::string line;
		while (getline(*fileReader, line))
		{
			rawData += line;
		}
		return rawData;
	}
	else
	{
		AuxPort::Logger::Log("Unable to open File and Read Data");
	}
	return rawData;
}

void AuxPort::TextFile::writeLineToFile(const std::string& data,bool log)
{
	AuxAssert(fileWriter != nullptr, "No File is selected for parsing");
	AuxAssert(fileWriter->is_open() == true && fileWriter != nullptr, "Please open a stream to the file, before reading from it");
	*fileWriter.get() << data << "\n";
	if (log)
		AuxPort::Logger::Log("Line written successfully to the file",AuxPort::LogType::Success,AuxPort::ColourType::Green);
}

std::string AuxPort::TextFile::readLineFromFile(bool log)
{
	AuxAssert(fileReader != nullptr, "No File is selected for parsing");
	AuxAssert(fileReader->is_open() == true && fileReader != nullptr, "Please open a stream to the file, before reading from it");
	getline(*fileReader, line);
	if (log)
		AuxPort::Logger::Log(line, AuxPort::LogType::Success, AuxPort::ColourType::Yellow);
	return line;
	
}

bool AuxPort::BinaryFile::open(const std::string& fileName, const Mode& mode, bool log)
{
	return false;
}

void AuxPort::BinaryFile::close(bool log)
{

}



void AuxPort::TextFormat::Log()
{
	setColour(AuxPort::ColourType::Cyan);
	std::cout << "Format Name : " << formatName << std::endl;
	std::cout << "UID : " << uniqueIdentifier << std::endl;
	std::cout << "Extension : " << extensionName <<std::endl;
	setColour(AuxPort::ColourType::White);
}

std::string& AuxPort::TextFormat::getFormatName()
{
	return formatName;
}

std::string& AuxPort::TextFormat::getUniqueIdentifier()
{
	return uniqueIdentifier;
}

std::string& AuxPort::TextFormat::getExtensionName()
{
	return extensionName;
}

void AuxPort::TextFormat::setExtensionName(const std::string& extensionName)
{
	this->extensionName = extensionName;
}

void AuxPort::TextFormat::setUniqueIdentifier(const std::string& uniqueIdentifier)
{
	this->uniqueIdentifier = uniqueIdentifier;
}

void AuxPort::TextFormat::setFormatName(const std::string& formatName)
{
	this->formatName = formatName;
}

AuxPort::CSV::CSV()
{
	this->extensionName = "csv";
	this->formatName = "Comma Seperated Values";
	this->uniqueIdentifier = "CSV v1.0";
}

void AuxPort::CSV::read(std::string& line,int props)
{	
	AuxAssert(this->fileExtension == this->extensionName, "Can only read .csv files");
	if (props == 0)
	{
		AuxAssert(this->fileReader->is_open() == true, "Please load up a .csv file before trying to read anything from it");
		fileReader->clear();
		fileReader->seekg(0, std::ios_base::beg);
		line = readLineFromFile();
	}
	if (props == 1)
	{
		AuxAssert(this->fileReader->is_open() == true, "Please load up a .csv file before trying to read anything from it");
		fileReader->clear();
		fileReader->seekg(0, std::ios_base::beg);
		getline(*fileReader, line);
		line = readLineFromFile();
	}
		
}

void AuxPort::CSV::write(const std::string& line,int props)
{
	AuxAssert(this->fileExtension == this->extensionName, "Can only write to .csv files, please update extension");
	if (props == 0)
	{
		AuxAssert(this->fileWriter->is_open() == true, "Please open a .csv file in write mode");
		fileWriter->seekp(0, std::ios_base::beg);
		writeLineToFile(line);
	}
}

void AuxPort::CSV::Log()
{
	setColour(AuxPort::ColourType::Cyan);
	std::cout << "Format Name : " << this->formatName << std::endl;
	std::cout << "Extension Name : " << this->extensionName << std::endl;
	std::cout << "UID : " << this->uniqueIdentifier << std::endl;
	std::cout << "Current Directory : " << this->getCurrentDirectory();
	setColour(AuxPort::ColourType::White);
}

void AuxPort::CSV::setHeaders(const std::vector<std::string>& headers)
{
	this->headers = headers;
}

void AuxPort::CSV::addData(const std::vector<std::string>& data)
{
	if (this->headers.size() > 0)
	{
		this->data.reserve(10);
		this->data.resize(10);
	}
		
}
