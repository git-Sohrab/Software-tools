# include <stdio.h>
# include <stdlib.h>

# include "parsedate.h"

# define NUM_TESTS 1000
# define BUFLEN 100

#pragma GCC diagnostic ignored "-Wparentheses"

static void check_test(const char *buf, int test_year, int test_month, int test_day);
static int hash(unsigned const char *str);
static int tests_done = 0, tests_passed = 0;

int main(int argc, char **argv)
{
  int i;
  char buf[BUFLEN];

  if(argc != 2) {
    fprintf(stderr,"%s: usage %s number\n", *argv, *argv);
    exit(1);
  }
  argc--; argv++;

  for(i=0;i<NUM_TESTS;i++) {
    int test_year = (random() % 1000) + 1000;
    int test_month = random() % 13;
    int test_day = random() % 32;

    (void) sprintf(buf, "%d/%d/%d", test_year, test_month, test_day);
    check_test(buf, test_year, test_month, test_day);
  }

  (void) sprintf(buf, "%s%d%d", *argv, tests_passed, tests_done);
 
  (void) printf("%s %s: tests_done %d tests_passed %d hash %d\n", *argv, 
                (tests_done == tests_passed) ? "ok" : "incomplete", tests_done, tests_passed, hash((unsigned char *)buf));
  return(0);
}

static void check_test(const char *buf, int test_year, int test_month, int test_day)
{
  int day = parse_day(buf);
  int month = parse_month(buf);
  int year = parse_year(buf);
  if((day != test_day)||(month != test_month)||(year != test_year))
    (void) fprintf(stderr, "bad output for %s (%d,%d,%d)\n",buf, day, month, year);
  else 
    tests_passed++;
  tests_done++;   
}

static int hash(unsigned const char *str)
{
  unsigned long hash = 5381;
  int c;

  /*NOWARN*/
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return (int) (hash % 1024);
}

  
