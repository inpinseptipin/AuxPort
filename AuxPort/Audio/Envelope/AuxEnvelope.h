#ifndef AUXPORT_ENVELOPE_H
#define AUXPORT_ENVELOPE_H
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

#include "../../AuxPort/AuxPort/Audio/FFT/AuxFFT.h"
#include "../../AuxPort/AuxPort/Audio/Spectral/AuxSpectral.h"

namespace AuxPort
{
	namespace Audio
	{
        class HilbertTransform : protected AuxPort::Audio::Spectral::OverlapSaveProcessor<float>
        {
        public:
            HilbertTransform(size_t overlapSize);
            HilbertTransform(const HilbertTransform& hilbert) = default;
            ~HilbertTransform() = default;

            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief This functions computes hilbert transform of a buffer using Overlap Save Technique
            ///////////////////////////////////////////////////////////////////////////////////////
            void transformBuffer(const std::vector<float>& inputBuffer, std::vector<float>& hilbertTransform);
            
            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief This functions computes hilbert transform of an finite audio signal
            ///////////////////////////////////////////////////////////////////////////////////////
            static void transformSignal(const std::vector<float>& inputSignal, std::vector<float>& hilbertTransform);
        private:
            std::vector<float> _currOverlappedBuffer;
        };
	}
}

#endif