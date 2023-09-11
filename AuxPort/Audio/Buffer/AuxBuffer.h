#pragma once
#ifndef AUXPORT_AUDIO_BUFFER_H
#define AUXPORT_AUDIO_BUFFER_H
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
#include "../../Core/Log/AuxLog.h"
#include "../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	///	This namespace consist of classes and functions useful for Audio Programming
	///////////////////////////////////////////////////////////////////////////////////////
	namespace Audio
	{

		///////////////////////////////////////////////////////////////////////////////////////
		///	sample : Template Type used for Generic Audio Buffers
		///	[Class] Buffer is a Generic Audio Buffer class that is a container for floating or integer type Audio Buffers.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		class Buffer : public AuxPort::ILog
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Constructor] Initializes the class
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			Buffer() = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Constructor] Initializes Buffer with an array
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			Buffer(const sample* array, const size_t& size)
			{
				this->replace(array, size);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Constructor] Initializes Buffer with an std::vector
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			Buffer(const std::vector<sample>& buffer)
			{
				this->replace(buffer);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Constructor] Initializes Buffer with another Buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			Buffer(const Buffer<sample>& newBuffer)
			{
				this->replace(newBuffer);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Destructor] Safely Deallocates memory and destroys the Buffer | v1.0
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			~Buffer()
			{
				_buffer.clear();
				_size = 0;
				maxAllocated = 0;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Returns a sample value at the provided index on the Buffer.
			/// [Assertion] Thrown when index provided is greater than size of Buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			const sample& get(const size_t& index) const
			{
				assert(index < _size);
				return _buffer[index];
			}

			///////////////////////////////////////////////////////////////////////////////////////
			///	[Overloaded Operator] Returns a sample value at the provided index on the Buffer.
			/// [Assertion] Thrown when index provided is greater than size of Buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			const sample& operator[](const size_t& index) const
			{
				return get(index);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Sets the sample to the specified index
			/// [Assertion] Exception thrown if index > size of the buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void set(const sample& value, const size_t& index)
			{
				assert(index < _size);
				_buffer[index] = value;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Replaces the audio buffer with a buffer pointer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void replace(const sample* buffer, const size_t& size)
			{
				if (size < _size)
				{
					_size = size;
				}
				else if (size > _size)
				{
					if (size > maxAllocated)
					{
						_buffer.resize(size);
						maxAllocated = _buffer.size();
					}
					_size = size;
				}
				for (int32 i = 0; i < _size; i++)
					_buffer[i] = buffer[i];
			}

			///////////////////////////////////////////////////////////////////////////////////////
			///	[Function] Replaces the audio buffer with a std::vector
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void replace(const std::vector<sample>& buffer)
			{
				if (buffer.size() < _size)
				{
					_size = buffer.size();
				}
				else if (buffer.size() > _size)
				{
					if (buffer.size() > maxAllocated)
					{
						_buffer.resize(buffer.size());
						maxAllocated = _buffer.size();
					}
					_size = buffer.size();
				}
				for (int32 i = 0; i < _size; i++)
					_buffer[i] = buffer[i];
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Replaces the audio buffer with a std::vector
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void replace(const AuxPort::Audio::Buffer<sample>& buffer)
			{
				if (buffer.size() < _size)
				{
					_size = buffer.size();
				}
				else if (buffer.size() > _size)
				{
					if (buffer.size() > maxAllocated)
					{
						_buffer.resize(buffer.size());
						maxAllocated = _buffer.size();
					}
					_size = buffer.size();
				}
				for (int32 i = 0; i < _size; i++)
					_buffer[i] = buffer[i];
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Adds a constant to every single value of the Audio Buffer.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void add(const sample& value)
			{
				for (uint32 i = 0; i < _size; i++)
				{
					_buffer[i] += value;
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Adds coefficient to the value in the Audio Buffer at the specified "index".
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void add(const sample& value, size_t index)
			{
				assert(index < _size);
				_buffer[index] += value;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Addition of std::vector to the Audio Buffer
			///[Assertion] size of the std::vector passed should <= size of the audio buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void add(const std::vector<sample>& buffer)
			{
				assert(_size <= buffer.size());
				for (uint32_t i = 0; i < buffer.size(); i++)
					_buffer[i] += buffer[i];
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Addition of values in a C-Style array to the Audio Buffer
			/// [Assertion] Size of the C-Style buffer passed should <= size of the audio buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void add(sample* buffer, const size_t& size)
			{
				assert(_size <= size);
				for (uint32_t i = 0; i < size; i++)
					_buffer[i] += buffer[i];
			}
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Addition of Two Audio Buffers
			/// [Assertion] Size of the Buffer passed should <= Size of the meta buffer 
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void add(const AuxPort::Audio::Buffer<sample>& buffer)
			{
				assert(_size <= buffer.size());
				for (uint32_t i = 0; i < buffer.size(); i++)
					_buffer[i] += buffer.get(i);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Multiplies coefficient to every single value of the Audio Buffer.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void multiply(const sample& value)
			{
				for (uint32 i = 0; i < _size; i++)
				{
					_buffer[i] *= value;
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Multiplies coefficient to the value in the Audio Buffer at the specified "index".
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void multiply(const sample& value, const size_t& index)
			{
				assert(index < _size);
				_buffer[index] *= value;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Divides coefficient from every single value of the Audio Buffer.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void divide(const sample& value)
			{
				assert(value != 0);
				for (uint32 i = 0; i < _size; i++)
					_buffer[i] /= value;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs division between the value in the Audio Buffer at the specified "index" and the "value" passed.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void divide(const sample& value, const size_t& index)
			{
				assert(index < _size);
				assert(value != 0);
				_buffer[index] /= value;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Subtracts coefficient from every single value of the Audio Buffer.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void subtract(const sample& value)
			{
				for (uint32 i = 0; i < _size; i++)
				{
					_buffer[i] -= value;
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs subtraction between the value in the Audio Buffer at the specified "index" and the "value" passed.
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void subtract(const sample& value, size_t index)
			{
				assert(index < _size);
				_buffer[index] -= value;
			}
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Resizes the audio buffer to the size given in the argument
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void resize(const size_t& size)
			{
				if (size > maxAllocated)
				{
					_buffer.resize(size);
				}
				_size = size;

			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Calculates the RMS in Linear/dbFS
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			double getRMS(bool dBFS = true) const
			{
				double sum = 0;
				for (uint32_t i = 0; i < _size; i++)
				{
					sum += pow(_buffer[i], 2);
				}
				sum = sqrt(sum) / _size;
				return dBFS == true ? AuxPort::Utility::linearTodB(sum) : sum;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Returns Size of Buffer
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			size_t size() const
			{
				return _size;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Overloaded ostream operator, u can use std::cout to call AuxPort::Logger::Log()
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			friend std::ostream& operator << (std::ostream& out, const Buffer<sample>& buffer)
			{
				out << "Buffer : ";
				out << "[";
				for (size_t i = 0; i < buffer.size(); i++)
				{
					if (i == buffer.size() - 1)
					{
						out << buffer.get(i);
					}
					else
						out << buffer.get(i) << ",";
					if (i > 8)
					{
						out << ".....";
						break;
					}

				}
				out << "] \n";
				out << "RMS : " << buffer.getRMS() << " dB";
				return out;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Overloaded AuxPort::ILog::Log
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void Log() override
			{
				setColour(AuxPort::ColourType::Blue);
				std::cout << *this << std::endl;
				setColour(AuxPort::ColourType::White);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Overloaded Assignment Operator
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void operator = (const Buffer<sample>& buffer)
			{
				this->replace(buffer);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Overloaded Assignment Operator
			/// [Version] v1.0 | Alpha
			///////////////////////////////////////////////////////////////////////////////////////
			void operator = (const std::vector<sample>& buffer)
			{
				this->replace(buffer);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Checks if two Audio Buffers have equal values
			///////////////////////////////////////////////////////////////////////////////////////
			bool operator == (const Buffer<sample>& buffer) const
			{
				if (_size != buffer.size())
					return false;
				for (uint32 i = 0; i < _size; i++)
				{
					if (_buffer[i] != buffer[i]);
					return false;
				}
				return true;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Zero Pad an Audio Buffer
			///////////////////////////////////////////////////////////////////////////////////////
			void zeroPad(size_t startIndex, size_t endIndex)
			{
				assert(startIndex < endIndex);
				assert(endIndex < _size);
				for (size_t i = startIndex; i < endIndex; i++)
					_buffer[i] = 0;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Extract a Sub Buffer from an Audio Buffer
			///////////////////////////////////////////////////////////////////////////////////////
			void subBuffer(AuxPort::Audio::Buffer<sample>& subBuffer, const size_t& startIndex, const size_t& endIndex)
			{
				if (startIndex >= endIndex || endIndex <= startIndex)
					subBuffer.zeroPad(0, subBuffer.size());
				else
				{
					for (size_t i = startIndex; i < endIndex; i++)
					{
						subBuffer.set(_buffer[i], i - startIndex);
					}
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			///	[Function] Averages the Audio buffer
			///////////////////////////////////////////////////////////////////////////////////////
			double mean()
			{
				return accumulate() / _size;
			}
		private:

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Accumulator
			///////////////////////////////////////////////////////////////////////////////////////
			double accumulate()
			{
				double sum = 0;
				for (uint32_t i = 0; i < _size; i++)
				{
					sum += _buffer[i];
				}
				return sum;
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Adds a value to the end of Buffer.
			///////////////////////////////////////////////////////////////////////////////////////
			void pushBack(const sample& value, const bool& wrapAround = false)
			{
				_buffer[_writeIndex] = value;
				if (!wrapAround)
				{
					assert(_writeIndex < _size);
					_writeIndex++;
				}

				else
					_writeIndex = (_writeIndex + 1) % _size;

			}

			std::vector<sample> _buffer;
			size_t _size = 0;
			size_t maxAllocated = 0;
			size_t _writeIndex = 0;
			size_t _readIndex = 0;
		};


	}
}

#endif