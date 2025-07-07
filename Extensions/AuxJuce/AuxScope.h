/*****************************************************************//**
 * \file   AuxScope.h
 * \brief  Scope UI Objects for JUCE
 * 
 * \author Satyarth Arora
 * \date   March 2025
 *********************************************************************/
#ifndef AUXSCOPE_H
#define AUXSCOPE_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>
#include <AuxPort.h>

namespace AuxPort
{
	namespace Extensions
	{
		/**
		 * \brief AuxMultiSelect UI Object.
		 */
		class AuxMultiSelect : public juce::Component
		{
		public:
			AuxMultiSelect();
			~AuxMultiSelect() = default;
			/**
			 * 
			 * \brief Sets the MultiSelect with different options.
			 * \param options
			 * \param maxSelect
			 */
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


		class AuxScope : public juce::Component
		{
		public:
			AuxScope();
			~AuxScope() = default;
			void paint(juce::Graphics& g) override;
			void resized() override;
			/**
			 * \brief Use this function to set the pointer of the audio buffer to the Scope Renderer.
			 * 
			 * \param scopeBufferPointer
			 */
			virtual void attachBuffer(AuxPort::Graphics::ScopeBuffers* scopeBufferPointer);
		protected:
			/**
			 * \brief [Overridable] Use or override this function to draw out your scope.
			 * 
			 * \param g - Juce::Graphics Context
			 * \param scopeBounds - Juce::Rectangle<float> Box 
			 */
			virtual void drawScope(juce::Graphics& g, const juce::Rectangle<float>& scopeBounds);
			/**
			 * \brief [Overridable] Use or override this function to render the background
			 * 
			 * \param g - Juce::Graphics Context
			 * \param backgroundBounds - Juce::Rectangle<float> Background Environment
			 * \param backgroundWidth - Width of the Border
			 */
			virtual void drawBackground(juce::Graphics& g, const juce::Rectangle<float>& backgroundBounds, float backgroundWidth);
			/**
			 * \brief [Overridable] Use or override this function to render the y-labels
			 * 
			 * \param g
			 * \param labelBounds
			 * \param labelInformation
			 */
			virtual void drawLabels(juce::Graphics& g, const juce::Rectangle<float>& labelBounds, const std::vector<float>& labelInformation);
			/**
			 * \brief [Overridable] Use or override this function to render the analytics.
			 * 
			 * \param g - Juce::Graphics Context
			 * \param analyticBounds - Juce::Rectangle<float> Bounds where the Analytic Region is rendered
			 */
			virtual void drawAnalytics(juce::Graphics& g, const juce::Rectangle<float>& analyticBounds);
			juce::ComboBox menu;
			AuxMultiSelect multiSelect;
			AuxPort::Graphics::ScopeBuffers* scopeBufferPointer;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AuxScope)
		};

		/*
			Creates an Oscilloscope component
		*/
		class OscilloScope : public AuxScope
		{
		public:
			OscilloScope();
			~OscilloScope() = default;
			void paint(juce::Graphics& g) override;
			void resized() override;
			void draw();
			/**
			  @brief Use this function to attach a AuxPort::Graphics::ScopeBuffers* 
			  @param scopeBufferPointer
			 */
			void attachBuffer(AuxPort::Graphics::ScopeBuffers* scopeBufferPointer);
		private:
			/**
			  @brief The function draws the oscilloscope analytics 
			  @param g
			  @param analyticBounds
			 */
			void drawAnalytics(juce::Graphics& g, const juce::Rectangle<float>& analyticBounds) override;
			/**
			  @brief The function draws the oscilloscope 
			  @param g
			  @param scopeBounds
			 */
			void drawScope(juce::Graphics& g, const juce::Rectangle<float>& scopeBounds) override;
			std::mutex mutex;
			bool canDraw = false;
			float pixelY0;
			float pixelY1;
			float pixelX0;
			juce::ComboBox menu;
			AuxMultiSelect multiSelect;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilloScope)
		};



	}
}


#endif
