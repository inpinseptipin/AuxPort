
#ifndef AUXSIMD_H
#define AUXSIMD_H

#include <vector>
#include "../Env/AuxEnv.h"



namespace AuxPort
{
	namespace Simd
	{

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Abstract Class] SIMD Wrapper for Single-precision floating point operations	
		///////////////////////////////////////////////////////////////////////////////////////
		class FloatingPoint
		{
		protected:
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Pure Virtual Function] Adds two vectors using SIMD extensions [Overridable]
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) = 0;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Pure Virtual Function] Multiples two vectors using SIMD extensions [Overridable]
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) = 0;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Pure Virtual Function] Return square root of values in the vector using SIMD extensions [Overridable]
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void sqrt(std::vector<float>& result, const std::vector<float>& vec) = 0;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Pure Virtual Function] Returns result after fused mutltiply-add using SIMD extensions [Overridable]
		/// For example: result[i] will be equal to (vec1[i] * vec2[i]) + vec3[i]
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void fma(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2, const std::vector<float>& vec3) = 0;

		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Class] SIMD Wrapper for 256 bit Single-precision floating point operations	
		///////////////////////////////////////////////////////////////////////////////////////
		class Float256 : public FloatingPoint
		{
		public:
			Float256() = default;
			~Float256() = default;
			Float256(const Float256& float256) = default;
			void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void sqrt(std::vector<float>& result, const std::vector<float>& vec) override;
			void fma(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2, const std::vector<float>& vec3) override;


		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Class]	SIMD Wrapper for 128 bit Single-Precision Floating point operations
		///////////////////////////////////////////////////////////////////////////////////////
		class Float128 : public FloatingPoint
		{
		public:
			Float128() = default;
			~Float128() = default;
			Float128(const Float128& float128) = default;
			void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void sqrt(std::vector<float>& result, const std::vector<float>& vec) override;
			void fma(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2, const std::vector<float>& vec3) override;


		};
	}
	
}


#endif
