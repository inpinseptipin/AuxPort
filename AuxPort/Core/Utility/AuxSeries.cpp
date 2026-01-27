/*
			AuxPort Library
			"Generic Modules to facilitate C++ Windows Application development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2026, Satyarth Arora
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

#include "AuxSeries.h"
#include "AuxCaster.h"
#include "AuxUtility.h"
#include "../File/AuxFile.h"
#include <algorithm>

AuxPort::AuxSeries::AuxSeries()
{
	this->terms.reserve(20);
	this->type = Sin;
	this->undefinedType = "";
	this->extensionName = "axs";
	this->formatName = "AuxSeries File";
	this->uniqueIdentifier = "AXS v1.0";
}

std::vector<AuxPort::AuxSeries::TaylorTerms>& AuxPort::AuxSeries::getTerms(uint32_t N, const Type& type)
{
	computeTerms(N, type);
	return terms;
}

void AuxPort::AuxSeries::computeTerms(uint32_t N, const Type& type)
{
	if (N == 0) { return; }
	if (this->type == type && terms.size() == N) { return; }

	terms.resize(N);
	this->type = type;
	AuxPort::AuxSeries::TaylorTerms currTerm;

	switch (type)
	{
	case Sin:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 1.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.coefficient /= ((currTerm.exponent + 1.0f) * (currTerm.exponent + 2.0f));
			currTerm.coefficient = -currTerm.coefficient;
			currTerm.exponent += 2.0f;
			terms[i] = currTerm;
		}
		break;

	case Cos:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 0.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.coefficient /= ((currTerm.exponent + 1.0f) * (currTerm.exponent + 2.0f));
			currTerm.coefficient = -currTerm.coefficient;
			currTerm.exponent += 2.0f;
			terms[i] = currTerm;
		}
		break;

	case Sinh:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 1.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.coefficient /= ((currTerm.exponent + 1.0f) * (currTerm.exponent + 2.0f));
			currTerm.exponent += 2.0f;
			terms[i] = currTerm;
		}
		break;

	case Cosh:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 0.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.coefficient /= ((currTerm.exponent + 1.0f) * (currTerm.exponent + 2.0f));
			currTerm.exponent += 2.0f;
			terms[i] = currTerm;
		}
		break;

	case Tanh:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 1.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.exponent += 2.0f;
			currTerm.coefficient = 0.0f;
			for (uint32_t j = 0; j < i; j++)
			{
				currTerm.coefficient += (terms[j].coefficient * terms[i - 1 - j].coefficient);
			}
			currTerm.coefficient /= currTerm.exponent;
			terms[i] = currTerm;
		}
		for (uint32_t i = 1; i < N; i += 2)
		{
			terms[i].coefficient = -terms[i].coefficient;
		}
		break;

	case E:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 0.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.exponent += 1.0f;
			currTerm.coefficient /= currTerm.exponent;
			terms[i] = currTerm;
		}
		break;

	case ArcTan:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 1.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.exponent += 2.0f;
			currTerm.coefficient = 1.0f / currTerm.exponent;
			if (i % 2) currTerm.coefficient = -currTerm.coefficient;
			terms[i] = currTerm;
		}
		break;

	case NaturalLog:
		currTerm.coefficient = 1.0f;
		currTerm.exponent = 1.0f;
		terms[0] = currTerm;
		for (uint32_t i = 1; i < N; i++)
		{
			currTerm.exponent += 1.0f;
			currTerm.coefficient = 1.0f / currTerm.exponent;
			if (i % 2) currTerm.coefficient = -currTerm.coefficient;
			terms[i] = currTerm;
		}
		break;
	}
}

void AuxPort::AuxSeries::Log()
{
	std::string output = "";
	if (!terms.empty())
	{
		output = getTypeAsString();
		output += "(x) = ";
		output += AuxPort::Casters::toStdString(terms[0].coefficient) + "x^" + AuxPort::Casters::toStdString(terms[0].exponent);
		for (uint32_t i = 1; i < terms.size(); i++)
		{
			output += terms[i].coefficient < 0 ? " - " : " + ";
			output += AuxPort::Casters::toStdString(abs(terms[i].coefficient)) + "x^" + AuxPort::Casters::toStdString(terms[i].exponent);
		}
	}
	else
	{
		output = "No Terms Calculated!";
	}

	setColour(AuxPort::ColourType::Green);
	std::cout << output << "\n";
	setColour(AuxPort::ColourType::White);
}

void AuxPort::AuxSeries::logFileInfo()
{
	if (fileName.empty())
	{
		AuxPort::Logger::Log("No file opened yet!");
		return;
	}
	TextFile::Log();
	TextFormat::Log();
}

void AuxPort::AuxSeries::writeSeriesToFile(const std::string& fileName)
{
	std::string fileExtension = fileName.substr(fileName.length() - 3);
	AuxAssert(fileExtension == "axs", "File must have .axs extension!");
	open(fileName, AuxPort::File::Mode::Write);
	writeLineToFile(getTypeAsString());
	writeLineToFile(std::to_string(terms.size()));
	for (const TaylorTerms& term : terms)
	{
		writeLineToFile(AuxPort::Casters::toStdString(term.coefficient) + " " + AuxPort::Casters::toStdString(term.exponent));
	}
	AuxPort::Logger::Log("File created successfully!", AuxPort::LogType::Success);
	close();
}

void AuxPort::AuxSeries::readSeriesFromFile(const std::string& fileName)
{
	open(fileName, AuxPort::File::Mode::Read);
	AuxAssert(fileExtension == "axs", "Invalid File: File must have .axs extension!");

	try
	{
		std::string currLine;
		readLineFromFile(currLine);
		if (currLine.empty()) { throw std::runtime_error("Invalid File: No type given in first line!"); }
		//While opening File created on Windows on Linux Systems, '\r' character from EOL-Specifier("\r\n") will be left as it is
		if (currLine.back() == '\r') currLine.pop_back();
		std::string type = currLine;
		std::transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type == "sin")
		{
			this->type = Sin;
		}
		else if (type == "cos")
		{
			this->type = Cos;
		}
		else if (type == "sinh")
		{
			this->type = Sinh;
		}
		else if (type == "cosh")
		{
			this->type = Cosh;
		}
		else if (type == "tanh")
		{
			this->type = Tanh;
		}
		else if (type == "arctan")
		{
			this->type = ArcTan;
		}
		else if (type == "e")
		{
			this->type = E;
		}
		else if (type == "ln")
		{
			this->type = NaturalLog;
		}
		else
		{
			this->type = Undefined;
			this->undefinedType = type;
		}

		if (fileReader->eof()) { throw std::runtime_error("Invalid File: Number of terms Not specified!"); }
		readLineFromFile(currLine);
		std::istringstream lineStream(currLine);
		uint32_t N;
		lineStream >> N;

		terms.clear();
		terms.resize(N);
		TaylorTerms currTerm;
		for (uint32_t i = 0; i < N; i++)
		{
			if (fileReader->eof())
			{
				throw std::runtime_error("Invalid File: Less than specified number of terms present in the File!");
			}

			readLineFromFile(currLine);
			lineStream.clear();
			lineStream.str(currLine);

			if (!(lineStream >> currTerm.coefficient >> currTerm.exponent))
			{
				throw std::runtime_error("Invalid File: Error reading coefficient/exponent!");
			}
			terms[i] = currTerm;
		}
		AuxPort::Logger::Log("File read successfully!", AuxPort::LogType::Success);
	}
	catch (const std::runtime_error& E)
	{
		terms.clear();
		AuxPort::Logger::Log(E.what(), AuxPort::LogType::Error);
	}
	close();
}

std::string AuxPort::AuxSeries::getTypeAsString()
{
	switch (this->type)
	{
	case Sin:
		return "sin";
	case Cos:
		return "cos";
	case Tanh:
		return "tanh";
	case Sinh:
		return "sinh";
	case Cosh:
		return "cosh";
	case ArcTan:
		return "arctan";
	case E:
		return "e";
	case NaturalLog:
		return "ln";
	case Undefined:
		return undefinedType;
	default: return undefinedType;
	}
}

void AuxPort::AuxSeries::read(std::string& line, int props)
{
}

void AuxPort::AuxSeries::write(const std::string& line, int props)
{
}

float AuxPort::AuxSeriesEngine::computeFunction(float x)
{
	AuxAssert(!terms.empty(), "No terms calculated for computing the function!");

	// Domain Adjust for Natural Logarithm
	int powerAdjust = 0;
	if (this->type == NaturalLog)
	{
		while (x > 1.5) {
			x /= AuxPort::e;
			powerAdjust++;
		}
		while (x < .5) {
			x *= AuxPort::e;
			powerAdjust--;
		}

		//Since we are using taylor series for log(1 + x). We need to subtract 1 from given value & use that in the series
		x = x - 1;
	}

	float currXPowN = powf(x, terms[0].exponent);
	float exponentDiff;
	float result = currXPowN * terms[0].coefficient;
	for (uint32_t i = 1; i < terms.size(); i++)
	{
		exponentDiff = terms[i].exponent - terms[i - 1].exponent;
		for (int i = 0; i < exponentDiff; i++) currXPowN *= x;
		result += (currXPowN * terms[i].coefficient);
	}
	return result + powerAdjust;
}
