#include "AuxSVG.h"

AuxPort::Graphics::SVG::SVG()
{
	svgData.clear();
}

bool AuxPort::Graphics::SVG::open(const std::string& fileName, const Mode& mode, bool log)
{
	if (mode == Mode::Read)
	{
		if (log)
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
			this->fileExtension = fileName.substr(dotIndex + 1, fileName.size() - dotIndex);
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
		if (log)
			AuxPort::Logger::Log("Trying to Open " + fileName); //char(28)
		try
		{
			fileWriter.reset(new std::ofstream(fileName, std::ofstream::out));
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
		svgData+="<svg width=\"800\" height=\"300\"  xmlns=\"http://www.w3.org/2000/svg\">";
		return fileWriter->is_open();
	}
	else if (mode == Mode::Update)
	{
		if (log)
			AuxPort::Logger::Log("Trying to Open " + fileName); //char(28)
		try
		{
			fileWriter.reset(new std::ofstream(fileName, std::ofstream::out | std::ofstream::app));
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


void AuxPort::Graphics::SVG::addBackground(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	backgroundData.clear();
	backgroundData += "<rect width=\"100%\" height=\"100%\" fill=\"rgba(" + std::to_string(red) + "," + std::to_string(green) + "," + std::to_string(blue) + ","  + std::to_string(alpha) + ")\"/>";

}

void AuxPort::Graphics::SVG::addText(const std::string& text, float startX, float startY, float fontSize)
{
	textData.push_back("<text x=\"" + std::to_string(startX) + "\" y=\"" + std::to_string(startY) + "\"" + ">" + text + "</text>");
}

void AuxPort::Graphics::SVG::save()
{
	svgData += backgroundData;
	for (uint32_t i = 0;i < textData.size();i++)
		svgData += textData[i];
	svgData += "</svg>";
	writeLineToFile(svgData);
	this->close();
}
