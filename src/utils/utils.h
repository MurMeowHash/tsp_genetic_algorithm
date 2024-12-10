#pragma once

#define NODISCARD [[nodiscard]]

typedef unsigned int uint;

NODISCARD uint getNumbersCount(uint number);
NODISCARD uint getFirstNumber(uint number, uint numbersCount);