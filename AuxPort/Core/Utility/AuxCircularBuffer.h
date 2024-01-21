#ifndef AUXPORT_CIRCULAR_BUFFER
#define AUXPORT_CIRCULAR_BUFFER
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2023, Satyarth Arora
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
#include <vector>
#include "../Log/AuxLog.h"
#include "../Env/AuxEnv.h"

namespace AuxPort
{
	template<class sample>
	class CircularBuffer : public AuxPort::ILog
	{
	public:
		CircularBuffer()
			: buffer(64)
			, capacity(64)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}
		CircularBuffer(const size_t& capacity)
			: buffer(capacity)
			, capacity(capacity)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}

		CircularBuffer(const std::vector<sample>& buffer)
			: buffer(buffer)
			, capacity(buffer.size())
			, size(buffer.size())
			, readIndex(0)
			, writeIndex(0)
		{}

		CircularBuffer(const sample* data, const size_t dataSize) 
			: buffer(dataSize)
			, capacity(dataSize)
			, size(dataSize)
			, readIndex(0)
			, writeIndex(0)
		{
			for(int i = 0; i < dataSize; i++)
			{
				buffer[i] = data[i];
			}
		}

		CircularBuffer(const CircularBuffer<sample>& obj) = default;

		virtual ~CircularBuffer() = default;

		void push(const sample& val)
		{
			buffer[writeIndex] = val;
			if (size == capacity)
			{
				incrementIndex(readIndex);
			}
			else
			{
				size++;
			}
			incrementIndex(writeIndex);
		}
	
		sample pop()
		{
			AuxAssert(size != 0, "Empty Circular Buffer");
			sample value = buffer[readIndex];
			size--;
			incrementIndex(readIndex);
			return value;
		}

		// Logging for testing
		void Log() override
		{
			setColour(AuxPort::ColourType::Blue);
			setColour(AuxPort::ColourType::Green);
			std::cout << "Read Index: " << readIndex;
			setColour(AuxPort::ColourType::Purple);
			std::cout <<  " | Write Index: " << writeIndex << '\n';
			for (uint32_t i = 0; i < buffer.size(); i++)
			{
				if (i == writeIndex)
					setColour(AuxPort::ColourType::Purple);
				else if (i == readIndex)
					setColour(AuxPort::ColourType::Green);
				else
					setColour(AuxPort::ColourType::White);
				std::cout << buffer[i] << " ";
			}
			std::cout << "\n";
			setColour(AuxPort::ColourType::White);
		}

		void reset()
		{
			readIndex = writeIndex = size = 0;
		}

		void meanRemoval()
		{
			auto mean = AuxPort::Utility::mean(buffer);
			for (uint32_t i = 0; i < buffer.size(); i++)
				buffer[i] -= mean;
		}
		uint32_t getSize()
		{
			return static_cast<uint32_t>(buffer.size());
		}

		// Resizes the buffer capacity but also resets the current buffer
		void resize(size_t newCapacity)
		{
			reset();
			buffer.resize(newCapacity);
		}

	protected:
		std::vector<sample> buffer;
		size_t capacity;
		size_t size;
		size_t readIndex;
		size_t writeIndex;

		// Increments the given index in a circular manner
		void incrementIndex(size_t &index)
		{
			index++;
			if (index == capacity)
			{
				index = 0;
			}
		}
	};
}
#endif