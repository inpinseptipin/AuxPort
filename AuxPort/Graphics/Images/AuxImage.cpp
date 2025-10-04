#include "AuxImage.h"

void AuxPort::GrayScaleImage::setDimensions(uint32_t x, uint32_t y)
{
	AuxAssert(x < 10000, "Can only accommodate realistic image resolutions");
	AuxAssert(y < 10000, "Can only accomodate realistic image resolutions");
	this->width = x;
	this->height = y;
	imageData.resize(y);
	for (uint32_t i = 0; i < imageData.size(); i++)
		imageData[i].resize(x);
}

void AuxPort::GrayScaleImage::addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber)
{
	AuxAssert(columnNumber <= width, "ColumnNumber is greater than the width of the image");
	AuxAssert(imageColumn.size() == height,"Image Column size does not match the height of the image");
	auto imageChannel = imageData[columnNumber];

}
