#include "modifiedstring.hpp"

char* marishin::modifieldstring(const char* stroka, char targetChar, char replacementChar)
{
  int inputLength = 0;
  while (stroka[inputLength] != '\0')
  {
    ++inputLength;
  }
  char* result = nullptr;
  try
  {
    result = new char[inputLength + 1];
  }
  catch (const std::bad_alloc& ba)
  {
    delete[] result;
    throw ba;
  }
  for (int i = 0; i < inputLength; ++i)
  {
    result[i] = stroka[i];
  }
  result[inputLength] = '\0';

  for (int i = 0; i < inputLength; ++i)
  {
    if (result[i] == targetChar)
    {
      result[i] = replacementChar;
    }
  }
  return result;
}
