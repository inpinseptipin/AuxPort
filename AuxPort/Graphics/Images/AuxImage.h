#ifndef AUXPORT_IMAGE_H
#define AUXPORT_IMAGE_H
#include "../../Core/Env/AuxEnv.h"
#include <vector>
#include "../../Core/Log/AuxLog.h"
namespace AuxPort
{
	class Image : public virtual AuxPort::ILog
	{
	public:
		Image() = default;
		~Image() = default;
		Image(const Image& image) = default;
		virtual void setDimensions(uint32_t x, uint32_t y) = 0;
		virtual void addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber) = 0;
	};

	class GrayScaleImage : public Image
	{
	public:
		GrayScaleImage() = default;
		~GrayScaleImage() = default;
		GrayScaleImage(const GrayScaleImage& grayScaleImage) = default;
	protected:
		void setDimensions(uint32_t x, uint32_t y) override;
		void addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber) override;
		std::vector<std::vector<uint8_t>> imageData;
		uint32_t width;
		uint32_t height;
	};
}
#endif
