#include "AuxPort/AuxPort.h"


int main(int argc, char* argv[])
{

#ifdef AUXPORT_64
	AuxPort::Logger::Log("AuxPort Alpha Build, x64", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
#endif
#ifdef AUXPORT_32
	AuxPort::Logger::Log("AuxPort Alpha Build, x32", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
#endif

}


