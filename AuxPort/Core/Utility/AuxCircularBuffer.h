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
	///////////////////////////////////////////////////////////////////////////////////////
	///	[Class] Represents a circular buffer data structure
	///////////////////////////////////////////////////////////////////////////////////////
	template<class sample>
	class CircularBuffer : public AuxPort::ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		///	Default Constructor
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer()
			: buffer(64)
			, capacity(64)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Initializes a CircularBuffer Object with the given capacity
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const size_t& capacity)
			: buffer(capacity)
			, capacity(capacity)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Initializes a CircularBuffer Object using contents of a given vector.
		/// The CircularBuffer will have same size and capacity as the vector. 
		/// First element of the given vector will be the first element of the buffer.
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const std::vector<sample>& buffer)
			: buffer(buffer)
			, capacity(buffer.size())
			, size(buffer.size())
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Initializes a CircularBuffer Object using pointer to an array of elements.
		/// The CircularBuffer will have same size and capacity as the number of elements.
		/// Initial element of the array will be the first element of the buffer.
		///////////////////////////////////////////////////////////////////////////////////////
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

		///////////////////////////////////////////////////////////////////////////////////////
		///	Default copy constructor
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const CircularBuffer<sample>& obj) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		///	Default destructor
		///////////////////////////////////////////////////////////////////////////////////////
		virtual ~CircularBuffer() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		///	Pushes an element onto the circular buffer.
		/// If the buffer is already full, then the oldest element is removed and the new element is inserted.
		///////////////////////////////////////////////////////////////////////////////////////
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
	
		///////////////////////////////////////////////////////////////////////////////////////
		///	Pops an element from the circular buffer. The buffer should not be empty.
		///////////////////////////////////////////////////////////////////////////////////////
		sample pop()
		{
			AuxAssert(size != 0, "Empty Circular Buffer");
			sample value = buffer[readIndex];
			size--;
			incrementIndex(readIndex);
			return value;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Logs the details of the circular buffer.
		///////////////////////////////////////////////////////////////////////////////////////
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

		///////////////////////////////////////////////////////////////////////////////////////
		///	Resets the circular buffer. This reduces size to zero.
		///////////////////////////////////////////////////////////////////////////////////////
		void reset()
		{
			readIndex = writeIndex = size = 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Subtracts the mean of the buffer from each element in the buffer.
		///////////////////////////////////////////////////////////////////////////////////////
		void meanRemoval()
		{
			auto mean = AuxPort::Utility::mean(buffer);
			for (uint32_t i = 0; i < buffer.size(); i++)
				buffer[i] -= mean;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	Returns the size of the buffer
		///////////////////////////////////////////////////////////////////////////////////////
		uint32_t getSize()
		{
			return static_cast<uint32_t>(buffer.size());
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// Resizes the buffer capacity but also resets the current buffer
		///////////////////////////////////////////////////////////////////////////////////////
		void resize(size_t newCapacity)
		{
			reset();
			capacity = newCapacity;
			buffer.resize(newCapacity);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// Return the element at the given shifted index. (Read Head has index 0, and so on...).
		/// Make Sure that index is less than the number of elements actively in buffer. Otherwise, old elements might be returned from the buffer.
		/// Negative Indexing is also supported.
		///////////////////////////////////////////////////////////////////////////////////////
		sample getShiftedElement(int index)
		{
			return buffer[(readIndex + index + capacity) % capacity];
		}

	protected:
		std::vector<sample> buffer;
		size_t capacity;
		size_t size;
		size_t readIndex;
		size_t writeIndex;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Increments the given index in a circular manner
		///////////////////////////////////////////////////////////////////////////////////////
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