#include "AuxUtility.h"

AuxPort::Expansions::Expansions()
{
    sum = 0;
    leftAccumulator.reserve(50);
    rightAccumulator.reserve(50);
    terms.reserve(100);
    type = ADAA;
}

void AuxPort::Expansions::setType(const Type& type)
{
    this->type = type;
}


void AuxPort::Expansions::setMaxSize(uint32_t N)
{
    leftAccumulator.reserve(floor((N + 1) / 2));
    rightAccumulator.reserve(floor((N + 1) / 2));
    terms.reserve(N);
}

std::vector<float>& AuxPort::Expansions::compute(const std::vector<float>& xPowers, const std::vector<float>& yPowers, uint32_t N)
{
    if (leftAccumulator.size() != xPowers.size())
    {
        leftAccumulator.resize(xPowers.size());
        rightAccumulator.resize(yPowers.size());
    }
    if (terms.size() != N)
        terms.resize(N);

    for (uint32_t i = 0; i < leftAccumulator.size(); i++)
    {
        leftAccumulator[i] = xPowers[i] * yPowers[i];
    }
    rightAccumulator = leftAccumulator;


    for (uint32_t M = 1; M <= N; M++)
    {
        sum = 0;
        for (uint32_t i = 1; i <= floor((M + 1) / 2); i++)
        {
            leftAccumulator[i - 1] *= yPowers[1];
            rightAccumulator[i - 1] *= xPowers[1];
            sum += leftAccumulator[i - 1];
            sum += rightAccumulator[i - 1];
        }
        if (M % 2 == 0)
            sum += leftAccumulator[(M / 2) - 1];
        terms[M - 1] = sum;
    }
    return terms;

}


AuxPort::Terms::Terms()
{
    termPowers.reserve(10);
}

void AuxPort::Terms::computePowers(float sample, uint32_t powers)
{
    if (termPowers.size() != powers)
        termPowers.resize(powers);
    termPowers[0] = 1;
    for (uint32_t i = 1; i < termPowers.size(); i++)
        termPowers[i] = termPowers[i - 1] * sample;
}

void AuxPort::Terms::computeAdditionalPowers(uint32_t start, uint32_t end)
{
    if (termPowers.size() != end)
        termPowers.resize(end);
    for (uint32_t i = start; i < end; i++)
        termPowers[i] = termPowers[i - 1] * termPowers[1];
}

std::vector<float>& AuxPort::Terms::getInternalVector()
{
    return termPowers;
}

void AuxPort::Terms::swap(Terms& term)
{
    this->termPowers.swap(term.termPowers);
}

