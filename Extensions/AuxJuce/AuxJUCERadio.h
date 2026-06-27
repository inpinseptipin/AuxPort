#ifndef AUXPORT_EXTENSIONS_JUCE_RADIO_H
#define AUXPORT_EXTENSIONS_JUCE_RADIO_H
#include <juce_gui_basics/juce_gui_basics.h>
#include <AuxPort.h>
namespace AuxPort
{
	namespace Extensions
	{
/**
 * UI Extensions for JUCE, Radio Button
 */
		class Radio : public juce::Component
		{
		public:
			Radio();
			~Radio();
			/**
			  @brief Sets radio group with the multiple options 
			  @param optionVector
			  \code{.cpp}
			  
			  \endcode 
			 */
			void setOptions(const std::vector<juce::String>& optionVector);
			void paint(juce::Graphics& g) override;
			std::vector<std::pair<juce::String, bool>>& getRadioOptionVector();
			void resized() override;
			/**
			 * Implement this lambda to handle what should we done, after a radio 
			 */
			std::function<void()> onChange;
		protected:
			void mouseDown(const juce::MouseEvent& mouseEvent) override;
			std::mutex mutex;
			std::vector<std::pair<juce::String, bool>> radioOptions;
			std::vector<int> yPositions;
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Radio)
		};
	}
}


#endif
