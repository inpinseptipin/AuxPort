#include "AuxScope.h"

AuxPort::Extensions::AuxScope::AuxScope()
{
	addAndMakeVisible(menu);
	addAndMakeVisible(multiSelect);
	menu.onChange = [this]
		{
			repaint();
		};
	numberOfSamples = 0;
	pixelX0 = 0.0f;
	pixelY0 = 0.0f;
	pixelY1 = 0.0f;
}

void AuxPort::Extensions::AuxScope::paint(juce::Graphics& g)
{

	auto scopeBounds = this->getLocalBounds().toFloat();
	auto x = scopeBounds.getWidth() / 10;
	auto y = scopeBounds.getHeight() / 10;
	auto boundaryWidth = 10.0f;

	this->drawAnalytics(g, juce::Rectangle<float>(scopeBounds.getX(), scopeBounds.getY(), 1.9 * x, scopeBounds.getHeight()));
	this->drawScope(g, juce::Rectangle<float>(scopeBounds.getX() + 2 * x, scopeBounds.getY(), 6 * x, scopeBounds.getHeight()));


}

void AuxPort::Extensions::AuxScope::resized()
{
	auto x = this->getLocalBounds().getWidth() / 10;
	auto y = this->getLocalBounds().getHeight() / 10;

	menu.setBounds(0, 9 * y, 1.9 * x, y);
	multiSelect.setBounds(8 * x, 0, 2 * x, 10 * y);
}

void AuxPort::Extensions::AuxScope::draw()
{
	repaint();
}

void AuxPort::Extensions::AuxScope::attachBuffer(AuxPort::Graphics::ScopeBuffers* scopeBufferPointer)
{
	AuxAssert(scopeBufferPointer != nullptr, "Pointer does not point to a valid memory chunk");
	this->scopeBufferPointer = scopeBufferPointer;
	auto ids = scopeBufferPointer->getBufferIDS();
	std::vector<juce::String> juceIds;
	juceIds.resize(ids.size());
	for (uint32_t i = 0; i < ids.size(); i++)
	{
		juceIds[i] = juce::String(ids[i]);
		menu.addItem(juceIds[i], i + 1);
	}
	menu.setSelectedId(1);
	multiSelect.setOptions(juceIds, 2);
	
	canDraw = true;
	
}

void AuxPort::Extensions::AuxScope::drawAnalytics(juce::Graphics& g,const juce::Rectangle<float>& analyticBounds)
{
	auto x = analyticBounds.getWidth() / 10;
	auto y = analyticBounds.getHeight() / 10;
	auto headingBounds = juce::Rectangle<float>(analyticBounds.getX(), analyticBounds.getY(), 10*x, x);

	g.setColour(juce::Colours::white);
	g.drawText("Analytics", headingBounds, juce::Justification::horizontallyCentred, true);

	/*Assignment
	* 1. Calculate RMS or any other Loudness metric and showcase it here
	*/


	
}

void AuxPort::Extensions::AuxScope::drawScope(juce::Graphics& g, const juce::Rectangle<float>& scopeBounds)
{
	auto boundaryWidth = 10.0f;
	g.setColour(juce::Colours::grey);
	g.drawRect(scopeBounds.getX() , scopeBounds.getY(),scopeBounds.getWidth(), scopeBounds.getHeight(), boundaryWidth);
	g.setColour(juce::Colour::fromRGBA(11, 12, 13, 0));
	g.fillRect(scopeBounds);

	auto scopeBackgroundBounds = scopeBounds.reduced(boundaryWidth);
	g.setColour(juce::Colour::fromRGBA(11, 12, 13, 255));
	g.fillRect(scopeBackgroundBounds);

	this->drawLabels(g, scopeBackgroundBounds);
	


	if (canDraw)
	{

		g.setColour(juce::Colours::white);
		auto startX = scopeBounds.getX() + boundaryWidth;
		auto sources = multiSelect.getPointerToSources();
		auto startColor = juce::Colours::white;
		for (uint32_t sourceIndex = 0; sourceIndex < sources->size(); sourceIndex++)
		{
			if (sources->at(sourceIndex).second)
			{
				auto name = sources->at(sourceIndex).first.toStdString();
				auto buffer = scopeBufferPointer->getPointerToBuffer(name);
				auto numberOfSamples = scopeBufferPointer->size(name);
				uint32_t strideLength = numberOfSamples / (scopeBounds.getWidth() - (2 * boundaryWidth));
				pixelX0 = startX;
				pixelY0 = AuxPort::Utility::remap<float>(0, scopeBounds.getHeight() - boundaryWidth, scopeBounds.getY() + boundaryWidth, -1, 1);
				g.setColour(startColor.contrasting(sourceIndex * 0.5));
				for (uint32_t i = 0; i < numberOfSamples; i += strideLength)
				{
					i = i >= numberOfSamples ? numberOfSamples - 1 : i;
					pixelY1 = AuxPort::Utility::remap<float>(buffer[i], scopeBounds.getHeight() - boundaryWidth, scopeBounds.getY() + boundaryWidth, -1, 1);
					g.drawLine(pixelX0, pixelY0, pixelX0 + 1, pixelY1);
					pixelX0++;
					pixelY0 = pixelY1;
				}
			}

			
		}
		
	}


	
}

void AuxPort::Extensions::AuxScope::drawLabels(juce::Graphics& g, const juce::Rectangle<float>& labelBounds)
{
	g.setColour(juce::Colour::fromRGBA(255, 255, 255, 100));
	auto textLength = 20.0f;
	auto h = AuxPort::Utility::remap<float>(1, labelBounds.getHeight(), labelBounds.getY(), -1, 1);
	auto textBounds = juce::Rectangle<float>(labelBounds.getX(), h, textLength, textLength);
	g.drawText("1", textBounds, juce::Justification::horizontallyCentred, true);

	textLength = 20.0f;
	h = AuxPort::Utility::remap<float>(-1, labelBounds.getHeight(), labelBounds.getY(), -1, 1);
	textBounds = juce::Rectangle<float>(labelBounds.getX(), h - textLength, textLength, textLength);
	g.drawText("-1", textBounds, juce::Justification::horizontallyCentred, true);

}

AuxPort::Extensions::AuxMultiSelect::AuxMultiSelect()
{

}

void AuxPort::Extensions::AuxMultiSelect::setOptions(const std::vector<juce::String>& options,uint32_t maxSelect)
{
	AuxAssert(options.size() > 0, "Cannot pass an empty option Vector");
	AuxAssert(options.size() >= maxSelect, "Number of options should be greater then the max select you can make");
	this->options.resize(options.size());
	for (uint32_t i = 0; i < options.size(); i++)
	{
		std::pair<juce::String, bool> pair;
		pair.first = options[i];
		pair.second = false;
		this->options[i] = pair;
		switchImages.push_back(juce::ImageCache::getFromMemory(BinaryData::medtoggleswitch_png, BinaryData::medtoggleswitch_pngSize));
	}
	this->maxSelect = maxSelect;
	
}

void AuxPort::Extensions::AuxMultiSelect::paint(juce::Graphics& g)
{

	auto bounds = this->getLocalBounds().toFloat();
	auto width = bounds.getWidth();
	headingHeight = bounds.getHeight() / 10;
	g.setColour(juce::Colours::white);
	g.drawText("Source", juce::Rectangle<float>(bounds.getX(), bounds.getY(), bounds.getWidth(), headingHeight), juce::Justification::horizontallyCentred, true);

	if (options.size() > 0)
	{
		auto optionsHeight = bounds.getHeight() - 2*headingHeight;
		auto rowHeight = optionsHeight / options.size();
		for (uint32_t i = 0; i < options.size(); i++)
		{
			auto row = AuxPort::Utility::remap<float>(i, headingHeight, optionsHeight, 0, options.size());
			auto rect = juce::Rectangle<float>(bounds.getX(), row, bounds.getWidth(), rowHeight);
			if (switchImages.size() > 0)
			{
				options[i].second == false ? this->drawSwitchImage(g, switchImages[i], rect, false) : this->drawSwitchImage(g, switchImages[i], rect, true);
			}
			else
			{
				g.drawRect(rect, 2);
				options[i].second == false ? g.setColour(juce::Colours::red) : g.setColour(juce::Colours::green);
				g.fillRect(rect);
				g.setColour(juce::Colours::white);
				g.drawText(options[i].first, rect, juce::Justification::horizontallyCentred, true);
			}
			
		}

	}
	else
		g.drawText("No Sources", juce::Rectangle<float>(bounds.getX(), bounds.getY(), bounds.getWidth(),  bounds.getHeight()), juce::Justification::horizontallyCentred, true);

}

void AuxPort::Extensions::AuxMultiSelect::resized()
{
	
}

void AuxPort::Extensions::AuxMultiSelect::mouseDown(const juce::MouseEvent& event)
{
	auto mouseLocation = event.getMouseDownPosition();
	auto bounds = this->getLocalBounds();
	auto location = AuxPort::Utility::remap<float>(mouseLocation.getY(), 0, options.size(), bounds.getY(), bounds.getHeight());
	uint32_t index  = static_cast<uint32_t>(floor(location));
	std::lock_guard lock(mutex);
	options[index].second = !options[index].second;
	repaint();
}

std::vector<std::pair<juce::String, bool>>* AuxPort::Extensions::AuxMultiSelect::getPointerToSources()
{
	return &options;
}

void AuxPort::Extensions::AuxMultiSelect::drawSwitchImage(juce::Graphics& g, juce::Image& switchImage, const juce::Rectangle<float>& bounds,bool state)
{
	uint32_t noOfFrames = switchImage.getHeight() / switchImage.getWidth();
	uint32_t frameID = state ? 1 : 0;
	float radius = bounds.getWidth() / 2;
	float centreX = bounds.getCentreX();
	float centreY = bounds.getHeight();
	float rx = centreX - switchImage.getWidth();
	float ry = centreY - switchImage.getWidth();
	g.drawImage(switchImage, bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), 0, frameID * switchImage.getWidth(), switchImage.getWidth(), switchImage.getWidth(), false);
}


