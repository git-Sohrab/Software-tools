#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexical.h"
#include "nextInputChar.h"
#include "tokenStack.h"

/*
 * rpnCalc.c - This is my solution to the fourth lab of eecs2030. The objective
 * of this lab was to create an RPN calculator. The below code consists of
 * three functions and a main(). User input is taken as token and added to
 * a stack (tokenStack). Only integers are pushed on the stack and if the user
 * inputs an operator, the top two items are popped off and the operation
 * is applied on those items. result is then pushed back on the stack.
 *
 * Co-Author: Sohrab Oryakhel
 * Student number: 214 302 145
 * Date : 2017/10/05
 *
 */

struct tokenStack *STACK;

static int popInt(struct tokenStack *s)
{
  struct lexToken *token;
  int num;

  token = popTokenStack(s);
  
  if (token -> kind == LEX_TOKEN_NUMBER) {
    num = atoi(token -> symbol);
    freeToken(token);
    return num;
  }
  exit(0);
}

static void pushInt(struct tokenStack *s, int v)
{
  struct lexToken *token;

  token = allocToken();
  token -> kind = LEX_TOKEN_NUMBER;
  sprintf(token -> symbol, "%d", v);  
  pushTokenStack(s, token);
}

static void doOperator(struct tokenStack *s, char *op)
{
  if(!strcmp(op,"quit")) {
    exit(0);
  } else if(!strcmp(op,"print")) {
    struct lexToken *t = popTokenStack(s);
    dumpToken(stdout, t);
    freeToken(t);
  } else {
    fprintf(stderr,"don't know |%s|\n", op);
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  setFile(stdin);

  struct lexToken *token;
  int a, b;

  STACK = createTokenStack();
  while (1) {
    token = nextToken();
    switch (token -> kind) {
      case LEX_TOKEN_EOF:
        exit(0);
      case LEX_TOKEN_IDENTIFIER:
        doOperator(STACK,token -> symbol);
        break;
      case LEX_TOKEN_NUMBER:
        pushInt(STACK, atoi(token -> symbol));
        break;
      case LEX_TOKEN_OPERATOR:
        b = popInt(STACK);
        a = popInt(STACK);
        switch (token -> symbol[0]) {
          case '/':
            pushInt(STACK, a / b);
            break;
          case '*':
            pushInt(STACK, a * b);
            break;
          case '+':
            pushInt(STACK, a + b);
            break;
          case '-':
            pushInt(STACK, a - b); 
            break;
        }
        break;
      }
    }
  return 0;
}
