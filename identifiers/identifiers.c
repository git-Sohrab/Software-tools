# include <stdio.h>
# include <string.h>
# include "identifiers.h"

/* you may wish to remove the following lines */
#pragma GCC diagnostic ignored "-Wpointer-sign"
#pragma GCC diagnostic ignored "-Wdangling-else"
#pragma GCC diagnostic ignored "-Wempty-body"

/* Q1.convert a temperature in F to it in C */
float fahrenheit2celsius(const float f) 
{
  return 5.0/9.0 * (f-32);
}

/* Q2. convert a temperature in C to F */
float celsius2fahrenheit(const float c) 
{
  return (1.8 * c) + 32;
}

/* Q3. reverse the elements in an array of int's in place */
void reverse_elements(int vals[], int count)
{
  int i;
  int tmp;
  for(i=0;i<count/2;i++) {
    tmp = vals[i];
    vals[i] = vals[count-1-i];
    vals[count-1-i] = tmp;
  } 
}

/* Q4. Count the number of '*' in the string given */
int count_stars(const char *s) 
{
  int count = 0;
  int i;
  for(i = 0; s[i]; i++){
    if(s[i] == '*'){
      count++;
    }
  }
  return count;
}
