#include "AuxPascal.h"
#include  <algorithm>

AuxPort::AuxPascal::AuxPascal()
{
	pascalTriangle.reserve(10);
	this->type = Positive;
	this->extensionName = "axp";
	this->formatName = "AuxPascal File";
	this->uniqueIdentifier = "AXP v1.0";
}

std::vector<std::vector<float>> AuxPort::AuxPascal::computePascalTriangle(uint32_t N, const Type& type)
{
	pascalTriangle.resize(N);
	this->type = type;
	for (uint32_t i = 0; i < N; i++)
	{
		std::vector<float> currRow(i + 1);
		currRow[0] = 1;
		currRow[i] = 1;
		for (uint32_t j = 1; j < i; j++)
		{
			currRow[j] = pascalTriangle[i - 1][j - 1] + pascalTriangle[i - 1][j];
		}
		pascalTriangle[i] = currRow;
	}
	if (type == Type::Negative)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			for (uint32_t j = 1; j <= i; j += 2)
			{
				pascalTriangle[i][j] = -pascalTriangle[i][j];
			}
		}
	}
	return pascalTriangle;
}

void AuxPort::AuxPascal::Log()
{
	setColour(AuxPort::ColourType::Green);
	if (pascalTriangle.empty())
	{
		std::cout << "No terms calculated!";
	}
	else
	{
		for (const std::vector<float>& row : pascalTriangle)
		{
			for (const float& value : row)
			{
				std::cout << value << " ";
			}
			std::cout << std::endl;
		}
	}
	setColour(AuxPort::ColourType::White);
}

void AuxPort::AuxPascal::writeToFile(const std::string& fileName)
{
	std::string fileExtension = fileName.substr(fileName.length() - 3);
	AuxAssert(fileExtension == "axp", "File must have .axp extension!");
	open(fileName, AuxPort::File::Mode::Write);

	if (this->type == Type::Positive)
	{
		writeLineToFile("positive");
	}
	else
	{
		writeLineToFile("negative");
	}

	writeLineToFile(std::to_string(pascalTriangle.size()));

	std::string currLine;
	for (const std::vector<float>& row : pascalTriangle)
	{
		currLine = "";
		for (const float& value : row)
		{
			currLine += AuxPort::Casters::toStdString(value);
			currLine += " ";
		}
		currLine.pop_back();	// Removing extra space at end
		writeLineToFile(currLine);
	}
	close();
}

void AuxPort::AuxPascal::readFromFile(const std::string& fileName)
{
	open(fileName, AuxPort::File::Mode::Read);
	AuxAssert(fileExtension == "axp", "Invalid File! File must have .axp extension!");

	try
	{
		std::string currLine;
		readLineFromFile(currLine);
		if (currLine.empty()) { throw std::runtime_error("Invalid File: No type given in first line!"); }
		if (currLine.back() == '\r') currLine.pop_back();
		std::string type = currLine;
		std::transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type == "positive")
		{
			this->type = Positive;
		}
		else if (type == "negative")
		{
			this->type = Negative;
		}
		else
		{
			throw std::runtime_error("Invalid File: Invalid Type given!");
		}

		if (fileReader->eof()) { throw std::runtime_error("Invalid File: Number of Rows not specified!"); }
		readLineFromFile(currLine);
		std::istringstream lineStream(currLine);
		uint32_t N;
		lineStream >> N;

		pascalTriangle.clear();
		pascalTriangle.resize(N);
		for (uint32_t i = 0; i < N; i++)
		{
			if (fileReader->eof())
			{
				throw std::runtime_error("Invalid File: Less than specified number of rows present in the File!");
			}

			readLineFromFile(currLine);
			lineStream.clear();
			lineStream.str(currLine);

			pascalTriangle[i].resize(i + 1);
			for (uint32_t j = 0; j <= i; j++)
			{
				if (!(lineStream >> pascalTriangle[i][j]))
				{
					throw std::runtime_error("Invalid File: Error reading coefficient!");
				}
			}
		}
		AuxPort::Logger::Log("File read successfully!", AuxPort::LogType::Success);
	}
	catch (const std::exception& E)
	{
		pascalTriangle.clear();
		AuxPort::Logger::Log(E.what(), AuxPort::LogType::Error);
	}
	close();
}

void AuxPort::AuxPascal::logFileInfo()
{
	if (fileName.empty())
	{
		AuxPort::Logger::Log("No file opened yet!");
		return;
	}
	TextFile::Log();
	TextFormat::Log();
}

void AuxPort::AuxPascal::read(std::string& line, int props)
{
}

void AuxPort::AuxPascal::write(const std::string& line, int props)
{
}