#include "AuxPort/AuxPort.h"

class Job : public AuxPort::TimerWithCallback
{
protected:
    void timerCallback() override
    {
        AuxPort::Logger::Log("Test");
    }
public:
    Job()
    {
        startTimer(1);
    }

    ~Job()
    {
        stopTimer();
    }
    Job(const Job& job) = default;

};

int main(int argc, char* argv[])
{
    Job job;
    std::this_thread::sleep_for(std::chrono::seconds(5));

}


