#include "AuxUtility.h"



AuxPort::FastRandomFloat::FastRandomFloat()
{
    randomSeed = 1;
}

AuxPort::FastRandomFloat::FastRandomFloat(const int& randomSeed)
{
    AuxAssert(randomSeed != 0, "randomSeed should be non-zero!");
    this->randomSeed = randomSeed;
}

float AuxPort::FastRandomFloat::getRandomFloat()
{
    randomSeed *= 16807;
    return (float)randomSeed * 4.6566129e-010f;
}

float AuxPort::FastRandomFloat::getRandomFloat(float start, float end)
{
    AuxAssert(start <= end, "start should be <= end.");
    return start + (end - start) * (getRandomFloat() + 1.0f) / 2.0f;
}

void AuxPort::DataProcessing::DataUtility::convertToFloat(const std::vector<std::vector<std::string>>& inputData, std::vector<std::vector<float>>& outputData)
{
    outputData.resize(inputData.size());
    for (uint32_t i = 0;i < outputData.size();i++)
        outputData[i].resize(inputData[0].size());
    for (uint32_t i = 0;i < inputData.size();i++)
        for (uint32_t j = 0;j < inputData[0].size();j++)
            outputData[i][j] = std::stof(inputData[i][j]);
}

void AuxPort::Utility::convertToVectorChar(const std::string& string, std::vector<char>& vectorChar)
{
    vectorChar.resize(string.size());
    for (uint32_t i = 0; i < vectorChar.size(); i++)
        vectorChar[i] = string[i];
}

void AuxPort::Utility::join(std::string& str, const std::vector<std::string>& tokens, char delimiter)
{
    str = "";
    if (tokens.empty()) return;
    size_t tokensCount = tokens.size();
    for (size_t i = 0; i < tokensCount - 1; i++)
    {
        str += tokens[i] + delimiter;
    }
    str += tokens[tokensCount - 1];
}

std::string AuxPort::Utility::join(const std::vector<std::string>& tokens, char delimiter)
{
    
    if (tokens.empty()) return "";
    std::string string = "";
    size_t tokensCount = tokens.size();
    for (size_t i = 0; i < tokensCount - 1; i++)
    {
        string += tokens[i] + delimiter;
    }
    string += tokens[tokensCount - 1];
    return string;
}





inline std::string AuxPort::Utility::formatFloatForFileNames(float val)
{
    auto data = std::to_string(val);
    data = data.replace(data.find("."), data.find("."), "_");
    return data;
}

inline std::string AuxPort::Utility::toAlphabet(uint32_t indexNumber)
{
    AuxAssert(indexNumber >= 0 && indexNumber <= 25, "English alphabet only consist of 26 letters last I checked");
    std::string letter;
    letter.push_back(static_cast<char>(65 + indexNumber));
    return letter;
}

std::vector<std::string> AuxPort::Utility::splitIntoTokens(std::string string, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        tokens.push_back(token);
        string.erase(0, pos + delimiter.length());
    }
    tokens.push_back(string);
    return tokens;
}

void AuxPort::Utility::splitIntoTokens(std::vector<std::string>& tokens, std::string string, const std::string& delimiter)
{
    tokens.clear();
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        tokens.push_back(token);
        string.erase(0, pos + delimiter.length());
    }
    tokens.push_back(string);
}

void AuxPort::Utility::splitIntoTokens(std::vector<std::string>& tokens, std::string string, char delimiter)
{
    size_t pos = 0;
    tokens.clear();
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        tokens.push_back(token);
        string.erase(0, pos + 1);
    }
    tokens.push_back(string);
}

std::vector<std::string> AuxPort::Utility::splitIntoTokens(std::string string, char delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        tokens.push_back(token);
        string.erase(0, pos + 1);
    }
    tokens.push_back(string);
    return tokens;
}

void AuxPort::About::printAbout()
{
    Env::isArm() ? AuxPort::Logger::Log("Detected Architecture : Arm", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("Detected Architecture : x86_64", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    if (Env::isWindowsOS())
        AuxPort::Logger::Log("Detected OS : Windows", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    else if (Env::isLinuxOS())
        AuxPort::Logger::Log("Detected OS : Linux", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    else if (Env::isMacOS())
        AuxPort::Logger::Log("Detected OS : Mac", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    else
        AuxPort::Logger::Log("Unknown OS", AuxPort::LogType::Warning, AuxPort::ColourType::Red);

#if AUXSIMD
    Env::supportsMMX() == true ? AuxPort::Logger::Log("MMX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("MMX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsAVX() == true ? AuxPort::Logger::Log("AVX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("AVX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsSSE() == true ? AuxPort::Logger::Log("SSE is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsSSE2() == true ? AuxPort::Logger::Log("SSE2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsSSE4_1() == true ? AuxPort::Logger::Log("SSE4.1 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.1 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsSSE4_2() == true ? AuxPort::Logger::Log("SSE4.2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
    Env::supportsNeon() == true ? AuxPort::Logger::Log("Neon is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("Neon is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);

#else
    AuxPort::Logger::Log("SIMD is not enabled", AuxPort::LogType::Warning, AuxPort::ColourType::Yellow);
#endif
}
