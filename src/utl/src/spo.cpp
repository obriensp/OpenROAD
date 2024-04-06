#include "utl/spo.h"


namespace spo {

static uint32_t sIndentation = 0;
void increaseIndentation()
{
  sIndentation++;
}

void decreaseIndentation()
{
  sIndentation--;
}

uint32_t currentIndentation()
{
  return sIndentation * 2;
}

};