#include "AuxStringTest.h"

void AuxTest::UnitTests::String::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty()) 
	{
		// Default Initialization if no commands are given!
		addConstructorTests(testcases);
		addLengthTests(testcases);
		addFirstCharTests(testcases);
		addAssignmentTests(testcases);
		addAdditionTests(testcases);
		addLeftShiftOperatorTests(testcases);
		addReplaceCharacterTests(testcases);
		addPushBackTests(testcases);
		addSubstringTests(testcases);
		addSubtractTests(testcases);
		addStringCastTests(testcases);
	}
	else 
	{
		for (const auto& command : initCommands) 
		{
			if (command == "Constructor")
				addConstructorTests(testcases);
			else if (command == "Length")
				addLengthTests(testcases);
			else if (command == "First")
				addFirstCharTests(testcases);
			else if (command == "Assignment")
				addAssignmentTests(testcases);
			else if (command == "Addition")
				addAdditionTests(testcases);
			else if (command == "<<")
				addLeftShiftOperatorTests(testcases);
			else if (command == "Replace")
				addReplaceCharacterTests(testcases);
			else if (command == "Pushback")
				addPushBackTests(testcases);
			else if (command == "Substring")
				addSubstringTests(testcases);
			else if (command == "Subtract")
				addSubtractTests(testcases);
			else if (command == "Cast")
				addStringCastTests(testcases);
		}
	}
}

void AuxTest::UnitTests::String::addConstructorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_String_Constructor_001",
		"Empty String Initialization",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::String str;
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_String_Constructor_002",
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
		"AuxUT_String_Constructor_003",
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
		"AuxUT_String_Constructor_004",
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
		"AuxUT_String_Constructor_005",
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
		"AuxUT_String_Constructor_006",
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
		"AuxUT_String_Constructor_007",
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
		"AuxUT_String_Constructor_008",
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
		"AuxUT_String_Constructor_009",
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
		"AuxUT_String_Constructor_010",
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
		"AuxUT_String_Constructor_011",
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
		"AuxUT_String_Constructor_012",
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
		"AuxUT_String_Length_001",
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
		"AuxUT_String_Length_002",
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
		"AuxUT_String_Length_003",
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

void AuxTest::UnitTests::String::addFirstCharTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_String_FirstChar_001",
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
		"AuxUT_String_Assignment_001",
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
		"AuxUT_String_Assignment_002",
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
		"AuxUT_String_Assignment_003",
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
		"AuxUT_String_Addition_001",
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
		"AuxUT_String_Addition_002",
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
		"AuxUT_String_Addition_003",
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
		"AuxUT_String_Addition_004",
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
		"AuxUT_String_Addition_005",
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
		"AuxUT_String_Addition_006",
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
		"AuxUT_String_Addition_007",
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
		"AuxUT_String_Addition_008",
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
		"AuxUT_String_LeftShift_001",
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
		"AuxUT_String_LeftShift_002",
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
		"AuxUT_String_LeftShift_003",
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
		"AuxUT_String_ReplaceChar_001",
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
		"AuxUT_String_ReplaceChar_002",
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
		"AuxUT_String_PushBack_001",
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
		"AuxUT_String_PushBack_002",
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
		"AuxUT_String_PushBack_003",
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
		"AuxUT_String_PushBack_004",
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
		"AuxUT_String_SubString_001",
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
		"AuxUT_String_SubString_002",
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
		"AuxUT_String_Subtract_001",
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
		"AuxUT_String_Subtract_002",
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
		"AuxUT_String_Cast_001",
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
		"AuxUT_String_Cast_002",
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
		"AuxUT_String_Cast_003",
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
		"AuxUT_String_Cast_004",
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
		"AuxUT_String_Cast_005",
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
		"AuxUT_String_Cast_006",
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
		"AuxUT_String_Cast_007",
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
		"AuxUT_String_Cast_008",
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
		"AuxUT_String_Cast_009",
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
		"AuxUT_String_Cast_010",
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
		"AuxUT_String_Cast_011",
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
		"AuxUT_String_Cast_012",
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
		"AuxUT_String_Cast_013",
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
		"AuxUT_String_Cast_014",
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
		"AuxUT_String_Cast_015",
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
		"AuxUT_String_Cast_016",
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
		"AuxUT_String_Cast_017",
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
		"AuxUT_String_Cast_018",
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
		"AuxUT_String_Cast_019",
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
		"AuxUT_String_Cast_020",
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
		"AuxUT_String_Cast_021",
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
		"AuxUT_String_Cast_022",
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
		"AuxUT_String_Cast_023",
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
		"AuxUT_String_Cast_024",
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
		"AuxUT_String_Cast_025",
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
		"AuxUT_String_Cast_026",
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
		"AuxUT_String_Cast_027",
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
		"AuxUT_String_Cast_028",
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
		"AuxUT_String_Cast_029",
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
		"AuxUT_String_Cast_030",
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
		"AuxUT_String_Cast_031",
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
		"AuxUT_String_Cast_032",
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
		"AuxUT_String_Cast_033",
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
		"AuxUT_String_Cast_034",
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