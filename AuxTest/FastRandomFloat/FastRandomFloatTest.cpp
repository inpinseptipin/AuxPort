#include "FastRandomFloatTest.h"

void AuxTest::UnitTests::FastRandomFloat::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addRangeTests(testcases);
		addRandomnessTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "Range")
				addRangeTests(testcases);
			else if (command == "Randomness")
				addRandomnessTests(testcases);
		}
	}
}

void AuxTest::UnitTests::FastRandomFloat::addRangeTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_FastRandomFloat_001",
		"Default Range Test for Fast Random Float",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::FastRandomFloat randomGenrator;
			float randomValue;
			uint32 iterationCount = 1000000;
			for (uint32 i = 0; i < iterationCount; i++)
			{
				randomValue = randomGenrator.getRandomFloat();
				if (randomValue < -1 || randomValue > 1) return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FastRandomFloat_002",
		"Custom Range Test for Fast Random Float",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::FastRandomFloat randomGenrator;
			float start = 4.5;
			float end = 19.3;
			float randomValue;
			uint32 iterationCount = 1000000;
			for (uint32 i = 0; i < iterationCount; i++)
			{
				randomValue = randomGenrator.getRandomFloat(start, end);
				if (randomValue < start || randomValue > end) return false;
			}
			return true;
		}
	);
}

void AuxTest::UnitTests::FastRandomFloat::addRandomnessTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_FastRandomFloat_003",
		"Chi-Square Test for Fast Random Float, Default Range, 100 Buckets",
		[](const std::vector<std::string>& commands)
		{
			return chiSquareTest(1000000, 100, 113.145);
		}
	);

	addTestCase(testcases,
		"AuxUT_FastRandomFloat_004",
		"Chi-Square Test for Fast Random Float, Default Range, 1000 Buckets",
		[](const std::vector<std::string>& commands)
		{
			return chiSquareTest(1000000, 100, 124.342);
		}
	);

	addTestCase(testcases,
		"AuxUT_FastRandomFloat_005",
		"Chi-Square Test for Fast Random Float, Custom Range, 100 Buckets",
		[](const std::vector<std::string>& commands)
		{
			return chiSquareTest(5.0f, 39.6f, 1000000, 100, 113.145);
		}
	);

	addTestCase(testcases,
		"AuxUT_FastRandomFloat_006",
		"Chi-Square Test for Fast Random Float, Custom Range, 1000 Buckets",
		[](const std::vector<std::string>& commands)
		{
			return chiSquareTest(5.0f, 39.6f, 1000000, 100, 124.342);
		}
	);
}

bool AuxTest::UnitTests::FastRandomFloat::chiSquareTest(int interationCount, uint32 bucketCount, float chiSquareCriticalValue)
{
	float start = -1.0f;
	float end = 1.0f;

	std::vector<int> buckets(bucketCount, 0);
	float bucketRange = (end - start) / bucketCount;
	AuxPort::FastRandomFloat randomGenerator;
	for (int i = 0; i < interationCount; i++)
	{
		float randomValue = randomGenerator.getRandomFloat();
		size_t index = (randomValue - start) / bucketRange;
		if (index = bucketCount) index--;
		buckets[index]++;
	}

	size_t expectedBucketCount = interationCount / bucketCount;
	float chiSquared = 0.0f;
	for (float observedCount : buckets)
	{
		chiSquared += (observedCount - expectedBucketCount) * (observedCount - expectedBucketCount) / expectedBucketCount;
	}
	return chiSquared > chiSquareCriticalValue;
}

bool AuxTest::UnitTests::FastRandomFloat::chiSquareTest(float start, float end, int interationCount, uint32 bucketCount, float chiSquareCriticalValue)
{
	std::vector<int> buckets(bucketCount, 0);
	float bucketRange = (end - start) / bucketCount;
	AuxPort::FastRandomFloat randomGenerator;
	for (int i = 0; i < interationCount; i++)
	{
		float randomValue = randomGenerator.getRandomFloat(start, end);
		size_t index = (randomValue - start) / bucketRange;
		if (index = bucketCount) index--;
		buckets[index]++;
	}

	size_t expectedBucketCount = interationCount / bucketCount;
	float chiSquared = 0.0f;
	for (float observedCount : buckets)
	{
		chiSquared += (observedCount - expectedBucketCount) * (observedCount - expectedBucketCount) / expectedBucketCount;
	}
	return chiSquared > chiSquareCriticalValue;
}