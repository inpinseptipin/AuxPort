#include "AuxImage.h"

void AuxPort::Graphics::GrayScaleImage::setDimensions(uint32_t x, uint32_t y)
{
	AuxAssert(x < 10000, "Can only accommodate realistic image resolutions");
	AuxAssert(y < 10000, "Can only accomodate realistic image resolutions");
	this->width = x;
	this->height = y;
	imageData.resize(y);
	for (uint32_t i = 0; i < imageData.size(); i++)
		imageData[i].resize(x);
}

void AuxPort::Graphics::GrayScaleImage::addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber,int minRange,int maxRange)
{
	AuxAssert(columnNumber <= width, "ColumnNumber is greater than the width of the image");
	AuxAssert(imageColumn.size() == height,"Image Column size does not match the height of the image");
	auto imageChannel = imageData[columnNumber].data();
	for (uint32_t i = 0;i < imageColumn.size();i++)
		imageChannel[i] = AuxPort::Utility::remap<float>(imageColumn[i], 0.0f, 1.0f, static_cast<float>(minRange), static_cast<float>(maxRange));
}

std::vector<std::vector<float>>* AuxPort::Graphics::GrayScaleImage::getImageData()
{
	return &imageData;
}

float AuxPort::Graphics::GrayScaleImage::getPoint(uint32_t x, uint32_t y) const noexcept
{
	AuxAssert(x < imageData.size(), "Queried Row is greater than number of rows");
	AuxAssert(y < imageData[0].size(), "Queried Column is greater than number of columns");
	return imageData[x][y];
}


size_t AuxPort::Graphics::GrayScaleImage::getRows() const noexcept
{
	return imageData.size();
}

size_t AuxPort::Graphics::GrayScaleImage::getColumns() const noexcept
{
	return imageData[0].size();
}


void AuxPort::Graphics::GrayScaleImage::Log()
{
	setColour(AuxPort::ColourType::Green);
	std::cout <<"Image Type : Gray Scale\n";
	std::cout <<"Size : " + std::to_string(getRows()) + "x" + std::to_string(getColumns()) + "\n";
	setColour(AuxPort::ColourType::White);
}
