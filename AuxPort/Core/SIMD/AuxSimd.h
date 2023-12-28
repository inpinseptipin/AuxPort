#ifndef AUXSIMD_H
#define AUXSIMD_H

#include <vector>
#include "../Env/AuxEnv.h"

namespace AuxPort
{
	namespace Simd
	{

		class FloatingPoint
		{
		protected:
			virtual void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) = 0;
			virtual void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) = 0;
		};

		class Float256 : public FloatingPoint
		{
		public:
			Float256() = default;
			~Float256() = default;
			Float256(const Float256& float256) = default;
			void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;

		};


		class Float128 : public FloatingPoint
		{
		public:
			Float128() = default;
			~Float128() = default;
			Float128(const Float128& float128) = default;
			void add(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;
			void multiply(std::vector<float>& result, const std::vector<float>& vec1, const std::vector<float>& vec2) override;


		};
	}
	
}


#endif