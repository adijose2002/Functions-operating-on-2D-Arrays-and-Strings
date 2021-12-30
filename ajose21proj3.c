#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>
#include <time.h>

#include "prog3.h"

//
// Author: Adithya Jose, UIC, Fall 2021
// CS 211: Programming Practicum
// Assignment: Project 3
//

/**
* 
*  Function "stubs" for Assignment 3 exercises.
*
*  See prog3.h for specifications of function behavior.
*
*/

/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char ** alloc_square_mtx(int n) {

  char **mtx = (char ** ) malloc(n * sizeof(char * ));

  for (int i = 0; i < n; ++i) {
    mtx[i] = (char * ) malloc(n * sizeof(int));
  }
  return mtx; // placeholder

}

void free_square_mtx(char **m, int n) {

  for (int i = 0; i < n; ++i) {
    free(m[i]);
  }

  free(m);

}

void pop_mtx_alpha(char **m, int n){

  srand(time(0));
  
  int letters = 26;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = 'a' + rand() % letters;
    }
  }

}

void display_mtx(char **m, int n){

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("%c", m[i][j]);
    }
    printf("\n");
  }

}

void swap_rows(char **m, int n, int r1, int r2){

  char curr;

  if ((r1 >= 0) || (r2 >= 0) || (r1 < n) || (r2 < n)) {
    for (int i = 0; i < n; ++i) {
      curr = m[r1 - 1][i];
      m[r1 - 1][i] = m[r2 - 1][i];
      m[r2 - 1][i] = curr;
    }
  }

}

void swap_cols(char **m, int n, int c1, int c2){

  char curr;

  if ((c1 >= 0) || (c2 >= 0) || (c1 < n) || (c2 < n)) {
    for (int i = 0; i < n; ++i) {
      curr = m[i][c1 - 1];
      m[i][c1 - 1] = m[i][c2 - 1];
      m[i][c2 - 1] = curr;
    }
  }

}


void rotate_right(char **m, int n){

  char curr;
  int r1, r2;

  for (int i = 0; i < (n / 2); ++i) {
    for (int j = i; j < (n - i - 1); ++j) {
      curr = m[i][j];

      r1 = n - j - 1;
      r2 = n - i - 1;

      m[i][j] = m[r1][i];
      m[r1][i] = m[r2][r1];
      m[r2][r1] = m[j][r2];
      m[j][r2] = curr;
    }
  }

}

void floating_boulders(char **m, int n, int nb){

  int t = n * n;

  if (nb < 0) {
    nb = 0;

  } else if (nb > t) {
    nb = t;
  }

  for (int i = 0; i < t; ++i) {
    if (i < nb) {
      m[i / n][i % n] = '#';

    } else {
      m[i / n][i % n] = '.';
    }
  }

  srand(time(0));
  char curr;

  for (int j = 0; j < t; ++j) {
    int a = rand() % t;
    int b = rand() % t;

    if (a != b) {
      curr = m[a / n][a % n];
      m[a / n][a % n] = m[b / n][b % n];
      m[b / n][b % n] = curr;
    }
  }

}

void mountains(char **m, int n){

  for (int i = 0; i < n; ++i) {
    int r = rand() % n;
    for (int j = 0; j < n; ++j) {
      if (j < r) {
        m[j][i] = '.';

      } else {
        m[j][i] = '#';
      }
    }
  }

}

void sink(char **m, int n){
  
  for (int i = n - 1; i > 0; --i) {
    for (int j = 0; j < n; ++j) {
      m[i][j] = m[i - 1][j];
    }
  }

  for (int x = 0; x < n; ++x) {
    m[0][x] = '.';
  }
  
}

void gravity(char **m, int n){

  char t;

  for (int i = 0; i < n; ++i) {
    for (int j = n - 2; j >= 0; --j) {
      for (int x = n - 2; x >= (n - j - 2); --x) {
        if (m[x + 1][i] == '.') {
          t = m[x][i];
          m[x][i] = m[x + 1][i];
          m[x + 1][i] = t;
        }
      }
    }
  }

}

/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {

  int n = strlen(s);
  int sb = 0; // space before
  int sa = 0; // space after

  while ((sb < n) && (s[sb] == ' ')) {
    sb++;
  }

  while ((sa < n) && (s[n - sa - 1] == ' ')) {
    sa++;
  }

  for (int i = sb; i < (n - sa); ++i) {
    s[i - sb] = s[i];
  }
  s[n - sb - sa] = '\0';

}

int str_search(char *s, char *pattern) {

  int i, j;
  int pos = -1;
  int pos2 = strlen(s) - strlen(pattern);

  if (strlen(pattern) > strlen(s)) {
    return -1;
  }

  for (i = 0; i <= pos2; ++i) {
    pos = i;

    for (j = 0; j < strlen(pattern); ++j) {
      if (pattern[j] == s[i]) {
        i++;

      } else {
        break;
      }
    }
    if (j == strlen(pattern)) {
      return pos;
    }
  }

  return -1;  // just a placeholder to make gcc happy for now

}


#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
              // IT DOESN"T CHANGE HOW YOUR PROGRAM
              // WORKS, BUT IT GIVES US A WAY TO CALL
              // YOUR FUNCTIONS FROM OUR CODE FOR
              // TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main() {
  
  int n = 10;
  char ** m = alloc_square_mtx(n);

  int n2 = 5;
  char ** m2 = alloc_square_mtx(n2);

  printf("\n*TEST* pop_mtx_alpha:\n");
  pop_mtx_alpha(m, n);
  display_mtx(m, n);

  printf("\n*TEST* swap_rows\n");
  printf("Swap 1 and 2:\n");
  swap_rows(m, n, 1, 2);
  display_mtx(m, n);

  printf("\n*TEST* swap_cols\n");
  printf("Swap 1 and 2:\n");
  swap_cols(m, n, 1, 2);
  display_mtx(m, n);

  printf("\n*TEST* rotate_right\n");
  rotate_right(m, n);
  display_mtx(m, n);

  printf("\n*TEST* floating_boulders\n");
  printf("Total boulders = %d\n", 15);
  floating_boulders(m, n, 15);
  display_mtx(m, n);
  printf("Total boulders = %d\n", 10);
  floating_boulders(m2, n2, 10);
  display_mtx(m2, n2);

  printf("\n*TEST* mountains\n");
  mountains(m, n);
  display_mtx(m, n);
  printf("------------------------\n");
  mountains(m2, n2);
  display_mtx(m2, n2);

  printf("\n*TEST* sink\n");
  printf("*Before sink*\n");
  display_mtx(m, n);
  printf("*After sink*\n");
  sink(m, n);
  display_mtx(m, n);

  printf("\n*TEST* gravity\n");
  printf("*Before gravity*\n");
  floating_boulders(m, n, 15);
  display_mtx(m, n);
  printf("*After gravity*\n");
  gravity(m, n);
  display_mtx(m, n);

  printf("\n*TEST* str_trim\n");
  char c[] = "   str_ t r im   T es t   ";
  printf("*Before trim:* \"%s\"\n", c);
  str_trim(c);
  printf("*After trim:* \"%s\"\n", c);
  char c1[] = "      str_trim Test      ";
  printf("*Before trim:* \"%s\"\n", c1);
  str_trim(c1);
  printf("*After trim:* \"%s\"\n", c1);

  printf("\n*TEST* str_search\n");
  char s[] = "CS 211: Project 3";
  printf("source string s: %s\n", s);
  printf("Search: \"CS\" \n");
  printf("Found at: %d\n", str_search(s, "CS"));
  printf("Search: \"211\" \n");
  printf("Found at: %d\n", str_search(s, "212"));
  printf("Search: \"x\" \n");
  printf("Found at: %d\n", str_search(s, "ect"));
  printf("Search: \"c\" \n");
  printf("Found at: %d\n", str_search(s, "ect"));

}

#endif        // DO NOT REMOVE THIS LINE!!!