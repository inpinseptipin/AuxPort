#ifndef AUXPORT_CIRCULAR_BUFFER
#define AUXPORT_CIRCULAR_BUFFER
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2025, Satyarth Arora
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
#include "../Utility/AuxUtility.h"

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	///	@brief Represents a circular buffer data structure
	///////////////////////////////////////////////////////////////////////////////////////
	template<class sample>
	class CircularBuffer : public AuxPort::ILog
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Default Constructor
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer()
			: buffer(64)
			, capacity(64)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Initializes a CircularBuffer Object with the given capacity
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const size_t& capacity)
			: buffer(capacity)
			, capacity(capacity)
			, size(0)
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Initializes a CircularBuffer Object using contents of a given vector.
		/// @note The CircularBuffer will have same size and capacity as the vector. 
		/// @note First element of the given vector will be the first element of the buffer.
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const std::vector<sample>& buffer)
			: buffer(buffer)
			, capacity(buffer.size())
			, size(buffer.size())
			, readIndex(0)
			, writeIndex(0)
		{}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Initializes a CircularBuffer Object using pointer to an array of elements.
		/// @note The CircularBuffer will have same size and capacity as the number of elements.
		/// @note Initial element of the array will be the first element of the buffer.
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
		///	@brief Default copy constructor
		///////////////////////////////////////////////////////////////////////////////////////
		CircularBuffer(const CircularBuffer<sample>& obj) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Default destructor
		///////////////////////////////////////////////////////////////////////////////////////
		virtual ~CircularBuffer() = default;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Pushes an element onto the circular buffer.
		/// @note If the buffer is already full, then the oldest element is removed and the new element is inserted.
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
		///	@brief Pops an element from the circular buffer. The buffer should not be empty.
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
		///	@brief Logs the details of the circular buffer.
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
		///	@brief Resets the circular buffer. This reduces size to zero.
		///////////////////////////////////////////////////////////////////////////////////////
		void reset()
		{
			readIndex = writeIndex = size = 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Subtracts the mean of the buffer from each element in the buffer.
		///////////////////////////////////////////////////////////////////////////////////////
		void meanRemoval()
		{
			auto mean = AuxPort::Utility::mean(buffer);
			for (uint32_t i = 0; i < buffer.size(); i++)
				buffer[i] -= mean;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns the size of the buffer
		///////////////////////////////////////////////////////////////////////////////////////
		uint32_t getSize()
		{
			return static_cast<uint32_t>(buffer.size());
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Resizes the buffer capacity but also resets the current buffer
		///////////////////////////////////////////////////////////////////////////////////////
		void resize(size_t newCapacity)
		{
			reset();
			capacity = newCapacity;
			buffer.resize(newCapacity);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Return the element at the given shifted index. (Read Head has index 0, and so on...).
		/// @note Make Sure that index is less than the number of elements actively in buffer. Otherwise, old elements might be returned from the buffer.
		/// @note Negative Indexing is also supported.
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
		/// @brief Increments the given index in a circular manner
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



	/**
	 @brief Use this to turn any floating point array into a circular buffer
	 */
	template<class circData>
	class CircularBufferEngine : public virtual ILog
	{
	public:
		CircularBufferEngine()
		{
			readIndex = 0;
			writeIndex = 0;
			buffer = nullptr;
			bufferSize = 0;
			poppedSample = 0;
		}
		~CircularBufferEngine() = default;
		CircularBufferEngine(const CircularBufferEngine& circularBuffer) = default;
		/**
		  @brief Use this function to attach a pointer to a floating-point array
		  @param attachedBuffer
		  @param bufferSize
		  @details
		  Code Implementation
		  \code{.cpp}
				float* buffer = new float[1024];
				CircularBufferEngine cBuffer;
				cBuffer.attachPointer(buffer,1024);
		  \endcode 
		 */
		void attachPointer(circData* attachedBuffer, size_t bufferSize)
		{
			this->buffer = attachedBuffer;
			this->bufferSize = bufferSize;
		}
		/**
		  @brief Push a sample to the circular buffer 
		  @param sample
		 */
		virtual void push(circData sample)
		{
			AuxAssert(buffer != nullptr, "You need to attach a valid floating-point buffer to circular buffer it");
			buffer[writeIndex++] = sample;
			if (writeIndex >= bufferSize)
				writeIndex = 0;
		}
		/**
		  @brief Pop a sample from the circular buffer 
		  @return 
		 */
		/**
		  @brief Pushes an entire floating point buffer to the Circular Buffer 
		  @param buffer
		  @param bufferSize
		 */
		virtual void push(circData* buffer, size_t bufferSize)
		{
			AuxAssert(this->buffer != nullptr, "You need to attach a valid floating-point buffer to the engine, Use the attach pointer to attach a pointer");
			AuxAssert(buffer != nullptr, "The data you want to add has to be stored in a valid floating point buffer");
			for (uint32_t i = 0; i < bufferSize; i++)
			{
				this->buffer[writeIndex++] = buffer[i];
				if (writeIndex >= this->bufferSize)
					writeIndex = 0;
			}
		}
		virtual float pop()
		{
			poppedSample = buffer[readIndex++];
			readIndex %= bufferSize;
			return poppedSample;
		}
		/**
		  @brief Call this function to print out all the contents of the buffer. 
		 */
		void Log() override
		{
			setColour(AuxPort::ColourType::Blue);
			std::cout << "[";
			for (uint32_t i = 0; i < bufferSize; i++)
				i == bufferSize - 1 ? std::cout << buffer[i] : std::cout << buffer[i] << " , ";
			std::cout << "]\n";
			setColour(AuxPort::ColourType::White);
		}
	protected:
		circData* buffer;
		int readIndex;
		int writeIndex;
		circData poppedSample;
		size_t bufferSize;
	};

}
#endif