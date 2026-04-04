#include "AuxSimd.h"

void AuxPort::Simd::Float256::add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsAVX(), "CPU doesn't support AVX 256 bit SIMD instructions");
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 8 == 0, "Vectors should be sizes of 8");

	auto noOfIterations = vec1.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm256_loadu_ps(vec1.data() + 8 * i);
		auto register2 = _mm256_loadu_ps(vec2.data() + 8 * i);
		auto sum = _mm256_add_ps(register1, register2);
		_mm256_storeu_ps(result.data() +8*i, sum);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
		
}
void AuxPort::Simd::Float256::multiply(std::vector<float>& result,const std::vector<float>& vec1, const std::vector<float>& vec2)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends and the Result Vector have to be the same");
	AuxAssert(vec1.size() % 8 == 0, "Vectors should be sizes of 8");
	
	auto noOfIterations = vec1.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm256_loadu_ps(vec1.data() + 8 * i);
		auto register2 = _mm256_loadu_ps(vec2.data() + 8 * i);
		auto product = _mm256_mul_ps(register1, register2);
		_mm256_storeu_ps(result.data() + 8 * i, product);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif	
}

void AuxPort::Simd::Float256::sqrt(std::vector<float>& result, const std::vector<float>& vec)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsAVX(), "The current processor does not support AVX and hence 256-bit SIMD instructions cannot be performed.");
	AuxAssert(result.size() == vec.size(), "The sizes of the Input Vector and the Result Vector have to be the same");
	AuxAssert(vec.size() % 8 == 0, "Vectors should be sizes of 8");

	auto noOfIterations = vec.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm256_loadu_ps(vec.data() + 8 * i);
		auto squareRoot = _mm256_sqrt_ps(register1);
		_mm256_storeu_ps(result.data() + 8 * i, squareRoot);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}

void AuxPort::Simd::Float256::fma(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2, const std::vector<float>& vec3)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsAVX(), "The current processor does not support AVX and hence 256-bit SIMD instructions cannot be performed.");
	AuxAssert(vec1.size() == vec2.size() && vec2.size() == vec3.size() && result.size() == vec1.size(), "The sizes of the Input Vectors and the Result Vector have to be the same");
	AuxAssert(vec1.size() % 8 == 0, "Vectors should be sizes of 8");

	auto noOfIterations = vec1.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm256_loadu_ps(vec1.data() + 8 * i);
		auto register2 = _mm256_loadu_ps(vec2.data() + 8 * i);
		auto register3 = _mm256_loadu_ps(vec3.data() + 8 * i);
		auto ans = _mm256_fmadd_ps(register1, register2, register3);
		_mm256_storeu_ps(result.data() + 8 * i, ans);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}




void AuxPort::Simd::Float128::add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(result.size() == vec1.size(), "Result Vector should be the same size as the Addends");
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm_load_ps(vec1.data() + 4 * i);
		auto register2 = _mm_load_ps(vec2.data() + 4 * i);
		auto sum = _mm_add_ps(register1, register2);
		_mm_storeu_ps(result.data() + 4 * i, sum);
	}
#elif AUXSIMD && AUXNEON
	AuxAssert(result.size() == vec1.size(),"Result Vector should be the same size as the Addends");
	AuxAssert(vec1.size() == vec2.size(),"The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0,"Vectors should be sizes of 4");

	auto noOfInterations = vec1.size() /4u;
	for (uint32_t i = 0; i < noOfInterations; i++)
	{
		auto register1 = vld1q_f32(vec1.data() + 4 * i);
		auto register2 = vld1q_f32(vec2.data() + 4 * i);
		auto sum = vaddq_f32(register1,register2);
		vst1q_f32(result.data() + 4 * i, sum);
	}

#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}

void AuxPort::Simd::Float128::multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm_load_ps(vec1.data() + 4 *  i);
		auto register2 = _mm_load_ps(vec2.data() + 4 *  i);
		auto product = _mm_mul_ps(register1, register2);
		_mm_storeu_ps(result.data() + 4 * i, product);
	}
#elif AUXSIMD && AUXNEON
	AuxAssert(result.size() == vec1.size(),"Result Vector should be the same size as the Addends");
	AuxAssert(vec1.size() == vec2.size(),"The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0,"Vectors should be sizes of 4");

	auto noOfInterations = vec1.size() /4u;
	for (uint32_t i = 0; i < noOfInterations; i++)
	{
		auto register1 = vld1q_f32(vec1.data() + 4 * i);
		auto register2 = vld1q_f32(vec2.data() + 4 * i);
		auto sum = vmulq_f32(register1,register2);
		vst1q_f32(result.data() + 4 * i, sum);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}

void AuxPort::Simd::Float128::sqrt(std::vector<float>& result, const std::vector<float>& vec)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsSSE(), "The current processor does not support SSE and hence 128-bit SIMD instructions cannot be performed.");
	AuxAssert(result.size() == vec.size(), "The sizes of the Input Vector and the Result Vector have to be the same");
	AuxAssert(vec.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm_loadu_ps(vec.data() + 4 * i);
		auto squareRoot = _mm_sqrt_ps(register1);
		_mm_storeu_ps(result.data() + 4 * i, squareRoot);
	}
#elif AUXSIMD && AUXNEON
	AuxAssert(AuxPort::Env::supportsNeon(), "The current processor does not support Neon and hence 128-bit SIMD instructions cannot be performed.");
	AuxAssert(result.size() == vec.size(), "The sizes of the Input Vector and the Result Vector have to be the same");
	AuxAssert(vec.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = vld1q_f32(vec.data() + 4 * i);
		auto squareRoot = vsqrtq_f32(register1);
		vst1q_f32(result.data() + 4 * i, squareRoot);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}

void AuxPort::Simd::Float128::fma(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2, const std::vector<float>& vec3)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsSSE(), "The current processor does not support SSE and hence 128-bit SIMD instructions cannot be performed.");
	AuxAssert(vec1.size() == vec2.size() && vec2.size() == vec3.size() && result.size() == vec1.size(), "The sizes of the Input Vectors and the Result Vector have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = _mm_loadu_ps(vec1.data() + 4 * i);
		auto register2 = _mm_loadu_ps(vec2.data() + 4 * i);
		auto register3 = _mm_loadu_ps(vec3.data() + 4 * i);
		auto ans = _mm_fmadd_ps(register1, register2, register3);
		_mm_storeu_ps(result.data() + 4 * i, ans);
	}
#elif AUXSIMD && AUXNEON
	AuxAssert(vec1.size() == vec2.size() && vec2.size() == vec3.size() && result.size() == vec1.size(), "The sizes of the Input Vectors and the Result Vector have to be the same");
	AuxAssert(vec1.size() == vec2.size() && vec2.size() == vec3.size() && result.size() == vec1.size(), "The sizes of the Input Vectors and the Result Vector have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i++)
	{
		auto register1 = vld1q_f32(vec1.data() + 4 * i);
		auto register2 = vld1q_f32(vec2.data() + 4 * i);
		auto register3 = vld1q_f32(vec3.data() + 4 * i);
		auto ans = vfmaq_f32(register1, register2, register3);
		vst1q_f32(result.data() + 4 * i, ans);
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif
}

void AuxPort::Simd::Float128::complexMultiply(std::vector<std::complex<float>>& input, std::vector<std::complex<float>>& output, std::vector<float>& AuxReal, std::vector<float>& AuxImag)
{
#if AUXSIMD && AUX64SIMD
	AuxAssert(AuxPort::Env::supportsSSE(), "The current processor does not support SSE and hence 128-bit SIMD instructions cannot be performed.");
	AuxAssert(input.size() == output.size() && input.size() == AuxReal.size() && output.size() == AuxImag.size(), "The sizes of the Input Vectors and the Result Vector have to be the same");
	AuxAssert(input.size() % 4 == 0, "Vectors should be sizes of 4");
	auto numberOfIterations = input.size() / 4;
	uint32_t firstHalf = 0;
	uint32_t secondHalf = firstHalf + 4;
	uint32_t readIndex = 0;
	uint32_t writeIndex = 0;
	for (uint32_t i = 0;i < numberOfIterations;i++)
	{
		firstHalf = 8 * i;
		secondHalf = firstHalf + 4;
		auto complex1_a = _mm_load_ps(reinterpret_cast<float*>(input.data()) + firstHalf);
		auto complex1_b = _mm_load_ps(reinterpret_cast<float*>(input.data()) + secondHalf);
		auto complex2_a = _mm_load_ps(reinterpret_cast<float*>(output.data()) + firstHalf);
		auto complex2_b = _mm_load_ps(reinterpret_cast<float*>(output.data()) + secondHalf);


		auto realVector1 = _mm_shuffle_ps(complex1_a, complex1_b, _MM_SHUFFLE(2, 0, 2, 0));
		auto imagVector1 = _mm_shuffle_ps(complex1_a, complex1_b, _MM_SHUFFLE(3, 1, 3, 1));

		auto realVector2 = _mm_shuffle_ps(complex2_a, complex2_b, _MM_SHUFFLE(2, 0, 2, 0));
		auto imagVector2 = _mm_shuffle_ps(complex2_a, complex2_b, _MM_SHUFFLE(3, 1, 3, 1));


		auto real12 = _mm_mul_ps(realVector1, realVector2);
		auto imag12 = _mm_mul_ps(imagVector1, imagVector2);
		auto realResult = _mm_sub_ps(real12, imag12);


		auto real1Imag2 = _mm_mul_ps(realVector1, imagVector2);
		auto imag2Real1 = _mm_mul_ps(imagVector1, realVector2);
		auto imagResult = _mm_add_ps(real1Imag2, imag2Real1);




		_mm_storeu_ps(AuxReal.data() + readIndex, realResult);
		_mm_storeu_ps(AuxImag.data() + readIndex, imagResult);

		for (uint32_t j = 0; j < 4; j++)
		{
			output[readIndex] = { AuxReal[readIndex],AuxImag[readIndex] };
			readIndex++;
		}
	
		
	}
#else
	AuxPort::Logger::Log("SIMD Instruction set not available");
#endif

}
