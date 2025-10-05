#ifndef AUXPORT_IMAGE_H
#define AUXPORT_IMAGE_H
#include "../../Core/Env/AuxEnv.h"
#include <vector>
#include "../../Core/Log/AuxLog.h"
#include "../../Core/Utility/AuxUtility.h"
namespace AuxPort
{
	class Image : public virtual AuxPort::ILog
	{
	public:
		Image() = default;
		~Image() = default;
		Image(const Image& image) = default;
		virtual void setDimensions(uint32_t x, uint32_t y) = 0;
		virtual void addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber,int minRange = 0,int maxRange = 1) = 0;
		virtual int getRows() = 0;
		virtual int getColumns() = 0;
	};

	class GrayScaleImage : public Image
	{
	public:
		GrayScaleImage() = default;
		~GrayScaleImage() = default;
		GrayScaleImage(const GrayScaleImage& grayScaleImage) = default;
		void setDimensions(uint32_t x, uint32_t y) override;
		void addColumn(const std::vector<float>& imageColumn, uint32_t columnNumber, int minRange = 0, int maxRange = 1) override;
		std::vector<std::vector<uint8_t>>* getImageData();
		int getRows() override;
		int getColumns() override;
	protected:
		std::vector<std::vector<uint8_t>> imageData;
		uint32_t width = 0;
		uint32_t height = 0;
	};
}
#endif
