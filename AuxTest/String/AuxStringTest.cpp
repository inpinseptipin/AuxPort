#include "AuxStringTest.h"

void AuxTest::UnitTests::String::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& commands)
{
	uint32 startIndex = testcases.size();
	addConstructorTests(testcases);
	addLengthTests(testcases);
	addFirstCharTestCases(testcases);
	addAssignmentTests(testcases);
	addAdditionTests(testcases);
	addLeftShiftOperatorTests(testcases);
	addReplaceCharacterTests(testcases);
	addPushBackTests(testcases);
	addSubstringTests(testcases);
	addSubtractTests(testcases);
	addStringCastTests(testcases);

	int currentTestID = 100;
	for (uint32 i = startIndex; i < testcases.size(); i++)
	{
		testcases[i].setTestID("AuxUTString" + AuxPort::Casters::toStdString(currentTestID));
		currentTestID++;
	}
}

void AuxTest::UnitTests::String::addConstructorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Empty String Initialization",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str;
			return true;
		}
	);

	addTestCase(testcases,
		"String Initialization using Character",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str('a');
			if (str.toStdString() == "a")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using Integer",
		[](const std::vector<std::string>& commands)
		{
#ifdef AUXPORT_64
			uint64 num = 991;
#else
			uint32 num = 991;
#endif
			AuxPort::String str(num);
			if (str.toStdString() == "991")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using Integer",
		[](const std::vector<std::string>& commands)
		{
#ifdef AUXPORT_64
			uint64 num = 0;
#else
			uint32 num = 0;
#endif
			AuxPort::String str(num);
			if (str.toStdString() == "0")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using C-Style String",
		[](const std::vector<std::string>& commands)
		{
			char* cStyleString = "Test String";
			AuxPort::String str(cStyleString);
			if (str.toStdString() == cStyleString)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using constant C-Style String",
		[](const std::vector<std::string>& commands)
		{
			const char* cStyleString = "Test String";
			AuxPort::String str(cStyleString);
			if (str.toStdString() == cStyleString)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using constant C-Style String",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str("Test String");
			if (str.toStdString() == "Test String")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using constant C-Style String",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str("Test\0 String");
			if (str.toStdString() == "Test")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using constant std::string",
		[](const std::vector<std::string>& commands)
		{
			const std::string sample = "Hello";
			AuxPort::String str(sample);
			if (str.toStdString() == sample)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using std::string",
		[](const std::vector<std::string>& commands)
		{
			std::string sample = "Hello";
			AuxPort::String str(sample);
			if (str.toStdString() == sample)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using constant AuxPort::String",
		[](const std::vector<std::string>& commands)
		{
			const AuxPort::String str1("str1");
			AuxPort::String str2(str1);
			if (str2.toStdString() == "str1")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String Initialization using AuxPort::String",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1("str1");
			AuxPort::String str2(str1);
			if (str2.toStdString() == "str1")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addLengthTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Get String Length",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str("str1");
			if (str.length() == 4)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Get String Length",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str("st\0hello");
			if (str.length() == 2)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Get Empty String Length",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str;
			if (str.length() == 0)
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addFirstCharTestCases(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Getting First Character",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str = "ABC";
			if (str.getFirstCharacter() == 'A')
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addAssignmentTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Assignment Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABC";
			AuxPort::String str2 = str1;
			if (str2.toStdString() == "ABC")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Assignment Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str = "ABC";
			if (str.toStdString() == "ABC")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Assignment Test",
		[](const std::vector<std::string>& commands)
		{
			std::string stdString = "ABC";
			AuxPort::String str = stdString;
			if (str.toStdString() == stdString)
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addAdditionTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"+ Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			AuxPort::String str = str1 + "EFGH";
			if (str.toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+ Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			AuxPort::String res = str1 + 'a';
			if (res.toStdString() == "ABCDa")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+ Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			AuxPort::String str2 = "EFGH";
			if ((str1 + str2).toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+ Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			std::string str2 = "EFGH";
			AuxPort::String res = str1 + str2;
			if (res.toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+= Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			str1 += 'a';
			if (str1.toStdString() == "ABCDa")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+= Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			str1 += "EFGH";
			if (str1.toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+= Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			std::string str2 = "EFGH";
			str1 += str2;
			if (str1.toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"+= Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			AuxPort::String str2 = "EFGH";
			str1 += str2;
			if (str1.toStdString() == "ABCDEFGH")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addLeftShiftOperatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"<< Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCD";
			std::stringstream testStream;
			testStream << str1;

			std::string output;
			testStream >> output;
			if (output == "ABCD")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"<< Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			std::stringstream testStream;
			testStream << str1;

			char* str2 = new char[13];
			testStream.getline(str2, 13);
			std::string output(str2);
			if (output == "Hello World!")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"<< Operator Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			std::stringstream testStream;
			testStream << &str1;

			char* str2 = new char[13];
			testStream.getline(str2, 13);
			std::string output(str2);
			if (output == "Hello World!")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addReplaceCharacterTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Replace Character Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			str1.replaceCharacter('l', 'i');
			if (str1.toStdString() == "Heiio Worid!")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Replace Character Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			str1.replaceCharacter('\0', 'i');
			if (str1.toStdString() == "Hello World!")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addPushBackTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"Push Back Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			str1.pushBack('a');
			if (str1.toStdString() == "Hello World!a")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Push Back Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			str1.pushBack("Bye");
			if (str1.toStdString() == "Hello World!Bye")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Push Back Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			AuxPort::String str2 = "Bye";
			str1.pushBack(str2);
			if (str1.toStdString() == "Hello World!Bye")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"Push Back Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World!";
			std::string str2 = "Bye";
			str1.pushBack(str2);
			if (str1.toStdString() == "Hello World!Bye")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addSubstringTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"SubString Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "Hello World";
			AuxPort::String subStr = str1.substring(0, 4);
			if (subStr.toStdString() == "Hello")
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"SubString Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCDEF";
			AuxPort::String subStr = str1.substring(0, 4);
			if (subStr.toStdString() == "ABCDE")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addSubtractTests(std::vector<AuxPort::Case>& testcases)
{
	//Fails Currently
	/*addTestCase(testcases,
		"String Subtract Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCDEF";
			AuxPort::String str2 = "HIJ";
			AuxPort::String res = AuxPort::String::subtract(str1, str2);
			if (res.toStdString() == "DEF")
				return true;
			else
				return false;
		}
	);*/

	addTestCase(testcases,
		"String Subtract Test",
		[](const std::vector<std::string>& commands)
		{
			std::string str1 = "ABCDEF";
			std::string str2 = "HIJ";
			AuxPort::String res = AuxPort::String::subtract(str1, str2);
			if (res.toStdString() == "DEF")
				return true;
			else
				return false;
		}
	);
}

void AuxTest::UnitTests::String::addStringCastTests(std::vector<AuxPort::Case>& testcases)
{
#ifdef AUXPORT_64
	// String to int64 Tests
	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "123456";
			if (str1.toInt64() == 123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-123456";
			if (str1.toInt64() == -123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0";
			if (str1.toInt64() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-0";
			if (str1.toInt64() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000000000000000000000000000000000000000000000000000000000";
			if (str1.toInt64() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000002";
			if (str1.toInt64() == 2)
				return true;
			else
				return false;
		}
	);

	// String to Uint64 Tests
	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "123456";
			if (str1.toUInt64() == 123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0";
			if (str1.toUInt64() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000000000000000000000000000000000000000000000000000000000";
			if (str1.toUInt64() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000002";
			if (str1.toUInt64() == 2)
				return true;
			else
				return false;
		}
	);
#endif

	// String to int32 Tests
	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "123456";
			if (str1.toInt32() == 123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-123456";
			if (str1.toInt32() == -123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0";
			if (str1.toInt32() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-0";
			if (str1.toInt32() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000000000000000000000000000000000000000000000000000000000";
			if (str1.toInt32() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Int32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000002";
			if (str1.toInt32() == 2)
				return true;
			else
				return false;
		}
	);

	// String to Uint32 Tests
	addTestCase(testcases,
		"String to UInt32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "123456";
			if (str1.toUInt32() == 123456)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt32",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0";
			if (str1.toUInt32() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000000000000000000000000000000000000000000000000000000000";
			if (str1.toUInt32() == 0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to UInt64",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000002";
			if (str1.toUInt32() == 2)
				return true;
			else
				return false;
		}
	);

	// String to double Tests
	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "123456.01";
			if (str1.toDouble() == 123456.01)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-123456.01";
			if (str1.toDouble() == -123456.01)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0";
			if (str1.toDouble() == 0.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0.0";
			if (str1.toDouble() == 0.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "-0.0";
			if (str1.toDouble() == 0.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000002";
			if (str1.toDouble() == 2.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "00000000000000000000000000000000000000";
			if (str1.toDouble() == 0.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0000000000000000000.0000000000000000000";
			if (str1.toDouble() == 0.0)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0.000000000000001";
			if (str1.toDouble() == 0.000000000000001)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0.001111000000000000";
			if (str1.toDouble() == 0.001111)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "0.002111000000000000";
			if (str1.toDouble() == 0.002111)
				return true;
			else
				return false;
		}
	);

	addTestCase(testcases,
		"String to Double",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "000000012318391870.00122111000000000000";
			if (str1.toDouble() == 12318391870.00122111)
				return true;
			else
				return false;
		}
	);

	// String to std::string Tests
	addTestCase(testcases,
		"String to std::string",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1 = "ABCDEF GHIJK";
			std::string str2 = str1.toStdString();
			if (str2 == "ABCDEF GHIJK")
				return true;
			else
				return false;
		}
	);

	// This fails currently
	/*addTestCase(testcases,
		"String to std:string",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str1;
			std::string str2 = str1.toStdString();
				if (str2 == "")
					return true;
				else
					return false;
		}
	);*/
}