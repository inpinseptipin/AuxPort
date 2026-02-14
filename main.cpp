#include "AuxPort/AuxPort.h"

int main(int argc, char* argv[])
{
    auto buffer = AuxPort::Utility::generateRandomValues<float>(512, -1, 1);
    auto buffer1 = buffer;
    AuxPort::Audio::WalshHadamardTransform wht(512);
    wht.transform(buffer, buffer1);
    wht.inverseTransform(buffer1);
    AuxPort::Error err;
    err.setType(AuxPort::Error::Type::Absolute);
    AuxPort::Logger::Log(err.compute<float>(buffer, buffer1));
    


}
