#ifndef AUXSCOPE_H
#define AUXSCOPE_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>
#include <AuxPort.h>

namespace AuxPort
{
	namespace Extensions
	{

		class AuxMultiSelect : public juce::Component
		{
		public:
			AuxMultiSelect();
			~AuxMultiSelect() = default;
			void setOptions(const std::vector<juce::String>& options, uint32_t maxSelect);
			void paint(juce::Graphics& g) override;
			void resized() override;
			void mouseDown(const juce::MouseEvent& event) override;
			std::vector<std::pair<juce::String, bool>>* getPointerToSources();
		private:
			void drawSwitchImage(juce::Graphics& g, juce::Image& knob, const juce::Rectangle<float>& bounds,bool state);
			std::mutex mutex;
			std::vector<std::pair<juce::String, bool>> options;
			uint32_t maxSelect;
			float headingHeight;
			std::vector<juce::Image> switchImages;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AuxMultiSelect)
		};

#if AUXPORT_EXP		
		class AuxScope : public juce::Component
		{
		public:
			AuxScope();
			~AuxScope() = default;
			void paint(juce::Graphics& g) override;
			void resized() override;
			virtual void attachBuffer(AuxPort::Graphics::ScopeBuffers* scopeBufferPointer);
		protected:
			virtual void drawScope(juce::Graphics& g, const juce::Rectangle<float>* scopeBounds);
			virtual void drawBackground(juce::Graphics& g, const juce::Rectangle<float>& backgroundBounds, float backgroundWidth);
			virtual void drawLabels(juce::Graphics& g, const juce::Rectangle<float>& labelBounds, const std::vector<float>& labelInformation);
			virtual void drawAnalytics(juce::Graphics& g, const juce::Rectangle<float>& analyticBounds);
		};

#endif
		class OscilloScope : public juce::Component
		{
		public:
			OscilloScope();
			~OscilloScope() = default;
			void paint(juce::Graphics& g) override;
			void resized() override;
			void draw();
			void attachBuffer(AuxPort::Graphics::ScopeBuffers* scopeBufferPointer);
		private:
			void drawAnalytics(juce::Graphics& g,const juce::Rectangle<float>& analyticBounds);
			void drawScope(juce::Graphics& g, const juce::Rectangle<float>& scopeBounds);
			void drawLabels(juce::Graphics& g, const juce::Rectangle<float>& labelBounds, const std::vector<float>& labelInformation);
			void drawBackground(juce::Graphics& g, const juce::Rectangle<float>& backgroundBounds,float backgroundWidth);
			std::mutex mutex;
			bool canDraw = false;
			AuxPort::Graphics::ScopeBuffers* scopeBufferPointer;
			float pixelY0;
			float pixelY1;
			float pixelX0;
			uint32_t numberOfSamples;
			juce::ComboBox menu;
			AuxMultiSelect multiSelect;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilloScope)
		};
	}
}


#endif
