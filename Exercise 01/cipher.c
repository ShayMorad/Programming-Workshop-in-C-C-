#include "cipher.h"

#define CYCLE_SIZE 26
#define UPPERCASE_START 'A'
#define UPPERCASE_END 'Z'
#define LOWERCASE_START 'a'
#define LOWERCASE_END 'z'

enum CharType
{
    UPPERCASE,
    LOWERCASE
};

/**
 * This function moves a character to its ASCII value based on a given
 * interval key.
 */
char move_char (char character, enum CharType char_type, int modulo);

/**
 * This function calculates the remainder of the given k value based on
 * CYCLE_SIZE.
 */
int calc_remainder (int k)
{
  int remainder = k % CYCLE_SIZE;
  return remainder;
}

// See full documentation in header file
void encode (char s[], int k)
{
  int remainder = calc_remainder (k);
  int i = 0;
  while (s[i] != '\0')
  {
    if (UPPERCASE_START <= s[i] && s[i] <= UPPERCASE_END)
    {
      enum CharType type = UPPERCASE;
      s[i] = move_char (s[i], type, remainder);
    }
    else if (LOWERCASE_START <= s[i] && s[i] <= LOWERCASE_END)
    {
      enum CharType type = LOWERCASE;
      s[i] = move_char (s[i], type, remainder);
    }
    i++;
  }
}

// See full documentation in header file
void decode (char s[], int k)
{
  int kk = (-1) * k;
  return encode (s, kk);
}

char move_char (char character, enum CharType char_type, int modulo)
{
  while (modulo != 0)
  {
    character = character + (modulo > 0 ? 1 : -1);
    if (char_type == UPPERCASE)
    {
      if (character < UPPERCASE_START)
      {
        character = UPPERCASE_END;
      }
      else if (character > UPPERCASE_END)
      {
        character = UPPERCASE_START;
      }
    }
    if (char_type == LOWERCASE)
    {
      if (character < LOWERCASE_START)
      {
        character = LOWERCASE_END;
      }
      else if (character > LOWERCASE_END)
      {
        character = LOWERCASE_START;
      }
    }
    if (modulo > 0)
    { modulo--; }
    if (modulo < 0)
    { modulo++; }
  }
  return character;
}
