#include "AuxSimd.h"

void AuxPort::Simd::Float256::add(std::vector<float>& result,const std::vector<float>& vec1, const std::vector<float>& vec2)
{
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 8 == 0, "Vectors should be sizes of 8");

	auto noOfIterations = vec1.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i += 8u)
	{
		auto register1 = _mm256_loadu_ps(vec1.data() + i);
		auto register2 = _mm256_loadu_ps(vec2.data() + i);
		auto sum = _mm256_add_ps(register1, register2);
		_mm256_storeu_ps(result.data() + i, sum);
	}

	
		
}
void AuxPort::Simd::Float256::multiply(std::vector<float>& result,const std::vector<float>& vec1, const std::vector<float>& vec2)
{
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends and the Result Vector have to be the same");
	AuxAssert(vec1.size() % 8 == 0, "Vectors should be sizes of 8");
	
	auto noOfIterations = vec1.size() / 8u;
	for (uint32_t i = 0; i < noOfIterations; i += 8u)
	{
		auto register1 = _mm256_loadu_ps(vec1.data() + i);
		auto register2 = _mm256_loadu_ps(vec2.data() + i);
		auto product = _mm256_mul_ps(register1, register2);
		_mm256_storeu_ps(result.data() + i, product);
	}
	
}


void AuxPort::Simd::Float128::add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2)
{
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i += 4u)
	{
		auto register1 = _mm_load_ps(vec1.data() + i);
		auto register2 = _mm_load_ps(vec2.data() + i);
		auto sum = _mm_add_ps(register1, register2);
		_mm_storeu_ps(result.data() + i, sum);
	}
}

void AuxPort::Simd::Float128::multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2)
{
	AuxAssert(vec1.size() == vec2.size(), "The sizes of the Addends have to be the same");
	AuxAssert(vec1.size() % 4 == 0, "Vectors should be sizes of 4");

	auto noOfIterations = vec1.size() / 4u;
	for (uint32_t i = 0; i < noOfIterations; i += 4u)
	{
		auto register1 = _mm_load_ps(vec1.data() + i);
		auto register2 = _mm_load_ps(vec2.data() + i);
		auto product = _mm_mul_ps(register1, register2);
		_mm_storeu_ps(result.data() + i, product);
	}
}
