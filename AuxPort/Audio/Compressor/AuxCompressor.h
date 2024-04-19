#ifndef AUXPORT_AUDIO_COMPRESSOR_H
#define AUXPORT_AUDIO_COMPRESSOR_H
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
#include "../../Core/Utility/AuxUtility.h"
namespace AuxPort
{
	namespace Audio
	{
		template <class sampleType>
		class AttackReleaseEnvelope
		{
		public:
			AttackReleaseEnvelope()
			{
				reset();
			}

			void setAttackTime(uint32 attackTime)
			{
				_attackTime = attackTime;
				_attackCoefficient = calculateCoefficient(_attackTime);
			}

			void setReleaseTime(uint32 releaseTime)
			{
				_releaseTime = releaseTime;
				_releaseCoefficient = calculateCoefficient(_releaseTime);
			}

			void setSampleRate(uint32 sampleRate)
			{
				AuxAssert(sampleRate > 0, "Sample Rate should be greater than zero!");
				_sampleRate = sampleRate;
				_attackCoefficient = calculateCoefficient(_attackTime);
				_releaseCoefficient = calculateCoefficient(_releaseTime);
			}

			void setParameters(uint32 sampleRate, uint32 attackTime, uint32 releaseTime)
			{
				_attackTime = attackTime;
				_releaseTime = releaseTime;
				setSampleRate(sampleRate);
			}

			void reset()
			{
				setSampleRate(44100);
				setAttackTime(0);
				setReleaseTime(0);
				_prevState = 0;
			}

			sampleType process(sampleType inputSample)
			{
				inputSample = abs(inputSample);

				float coefficient;
				if (inputSample > _prevState)
					coefficient = _attackCoefficient;	// Attack
				else
					coefficient = _releaseCoefficient;	// Release

				_prevState = inputSample + coefficient * (_prevState - inputSample);
				return _prevState;
			}

		private:
			uint32 _attackTime;
			uint32 _releaseTime;
			uint32 _sampleRate;

			sampleType _prevState;
			sampleType _attackCoefficient;
			sampleType _releaseCoefficient;
			
			sampleType calculateCoefficient(uint32& time)
			{
				if (time == 0) return 0;
				return exp(-2000 * AuxPort::pi / (_sampleRate * time));
			}
		};

		template <class sampleType>
		class Compressor
		{
		public:
			Compressor()
			{
				reset();
			}
			
			Compressor(uint32 sampleRate, sampleType thresholdDB, float ratio, uint32 attackTime = 0, uint32 releaseTime = 0)
			{
				updateParameters(sampleRate, thresholdDB, ratio, attackTime, releaseTime);
			}
			
			void setThreshold(sampleType thresholdDB)
			{
				_thresholdDB = thresholdDB;
				_threshold = AuxPort::Utility::dBToLinear(_thresholdDB);
				_thresholdInverse = 1 / _threshold;	// To save computation time later while processing audio samples
			}

			void setRatio(float ratio)
			{
				AuxAssert(ratio >= 1, "Compression Ratio should be >= 1 !");
				_ratio = ratio;
				_ratioInverse = 1 / _ratioInverse;	// To save computation time later while processing audio samples
			}

			void setSampleRate(uint32 sampleRate)
			{
				_attackReleaseEnvelope.setSampleRate(sampleRate);
			}

			void setAttackTime(uint32 attackTime)
			{
				_attackReleaseEnvelope.setAttackTime(attackTime);
			}

			void setReleaseTime(uint32 releaseTime)
			{
				_attackReleaseEnvelope.setReleaseTime(releaseTime);
			}

			void setParameters(uint32 sampleRate, sampleType thresholdDB, float ratio, uint32 attackTime = 0, uint32 releaseTime = 0)
			{
				setThreshold(thresholdDB);
				setRatio(ratio);
				_attackReleaseEnvelope.setParameters(sampleRate, attackTime, releaseTime);
			}

			void reset()
			{
				setThreshold(0);
				setRatio(1);
				_attackReleaseEnvelope.reset();
			}

			sampleType process(sampleType inputSample)
			{
				sampleType envelopeOutput = _attackReleaseEnvelope.process(inputSample);
				
				sampleType gain = static_cast<sampleType> (1.0);
				if(envelopeOutput >= _threshold)
					gain = std::pow(envelopeOutput * _thresholdInverse, _ratioInverse - static_cast<sampleType> (1.0));

				return gain * inputSample;
			}

		private:
			sampleType _thresholdDB;
			sampleType _threshold;
			sampleType _thresholdInverse;
			float _ratio;
			float _ratioInverse;
			AttackReleaseEnvelope<sampleType> _attackReleaseEnvelope;
		};
	}
}

#endif