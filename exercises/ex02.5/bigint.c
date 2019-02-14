/* Example code for Exercises in C.

This program shows a way to represent a BigInt type (arbitrary length integers)
using C strings, with numbers represents as a string of decimal digits in reverse order.

Follow these steps to get this program working:

1) Read through the whole program so you understand the design.

2) Compile and run the program.  It should run three tests, and they should fail.

3) Fill in the body of reverse_string().  When you get it working, the first test should pass.

4) Fill in the body of itoc().  When you get it working, the second test should pass.

5) Fill in the body of add_digits().  When you get it working, the third test should pass.

6) Uncomment the last test in main.  If your three previous tests pass, this one should, too.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* reverse_string: Returns a new string with the characters reversed.

It is the caller's responsibility to free the result.

s: string
returns: string
*/
char *reverse_string(char *s) {

    int i;
    int si = 0;
    char *output =(char*)malloc(sizeof(char)*strlen(s));

    for(i=strlen(s)-1;i>=0;i--){
      //printf("%c\n", s[i]);
      output[i] = s[si];
      si++;
    }

    return output;
}

/* ctoi: Converts a character to integer.

c: one of the characters '0' to '9'
returns: integer 0 to 9
*/
int ctoi(char c) {
    assert(isdigit(c));
    return c - '0';
}

/* itoc: Converts an integer to character.

i: integer 0 to 9
returns: character '0' to '9'
*/
char itoc(int i) {
    char c = '0' + i;
    return c;
}

/* multiply_digits: Multiplies two decimal digits, returns the total and carry.

Stores the result in z.

a: character '0' to '9'
b: character '0' to '9'
c: character '0' to '9'
total: pointer to char
carry: pointer to char
*/
void multiply_digits(char a, char b, char c, char *total, char *carry) {
    int tempTotal;

    tempTotal = (ctoi(a) * ctoi(b)) + ctoi(c);

    if(tempTotal>=10){
      *carry = itoc(tempTotal)[0];
      *total = itoc(tempTotal)[1];
    }else{
      *carry = '0';
      *total = itoc(tempTotal);
    }
}


/* add_digits: Adds two decimal digits, returns the total and carry.

For example, if a='5', b='6', and carry='1', the sum is 12, so
the output value of total should be '2' and carry should be '1'

a: character '0' to '9'
b: character '0' to '9'
c: character '0' to '9'
total: pointer to char
carry: pointer to char

*/
void add_digits(char a, char b, char c, char *total, char *carry) {
    int tempTotal;
    // printf("This is C %c\n", *carry);
    // printf("This is T %c\n", *total);
    if(isdigit(*carry)){
      tempTotal = ctoi(a) + ctoi(b) + ctoi(c) + *carry;
    }else{
      tempTotal = ctoi(a) + ctoi(b) + ctoi(c);
    }
    if(tempTotal>=10){
      *carry = '1';
      *total = itoc(tempTotal-10);
    }else{
      *carry = '0';
      *total = itoc(tempTotal);
    }
}

/* Define a type to represent a BigInt.
   Internally, a BigInt is a string of digits, with the digits in
   reverse order.
*/
typedef char * BigInt;

/* add_bigint: Adds two BigInts

Stores the result in z.

x: BigInt
y: BigInt
carry_in: char
z: empty buffer
*/
void add_bigint(BigInt x, BigInt y, char carry_in, BigInt z) {
    char total, carry_out;
    int dx=1, dy=1, dz=1;
    char a, b;

    if (*x == '\0') {
        a = '0';
        dx = 0;
    }else{
        a = *x;
    }
    if (*y == '\0') {
        b = '0';
        dy = 0;
    }else{
        b = *y;
    }


    add_digits(a, b, carry_in, &total, &carry_out);
    // if total and carry are 0, we're done
    if (total == '0' && carry_out == '0') {
        *z = '\0';
        return;
    }
    // otherwise store the digit we just computed
    *z = total;

    // and make a recursive call to fill in the rest.
    add_bigint(x+dx, y+dy, carry_out, z+dz);
}

/* print_bigint: Prints the digits of BigInt in the normal order.

big: BigInt
*/
void print_bigint(BigInt big) {
    char c = *big;
    if (c == '\0') return;
    print_bigint(big+1);
    printf("%c", c);
}

/* multiply_digit_to_BigInt: Multiplies a BigInt with a single digit

Stores the result in z.

numerator: BigInt
a: character digit
z: empty buffer
*/

void multiply_digit_to_BigInt(BigInt numerator, char a, char carry_in, &total, &carry_out){
  // add to total the value of multipling the numberator to the a digit + carry_in, also set carry_out
  char semitotal, semicarryout;
  int dx =1,dz=1;
  char b, carry_in;

  if(*numerator == '\0'){
    b = '0';
    dx = 0;
  }else{
    b =*x;
  }

  multiply_digits(a, b, carry_in, &semitotal, &semicarryout);

  if (total == '0' && carry_out == '0') {
      *z = '\0';
      return;
  }

  *total = ctoi(semitotal)+ctoi(*carry_out);


  // // otherwise store the digit we just computed
  *z = total;
  //
  // // and make a recursive call to fill in the rest.
  add_bigint(x+dx, a, semicarryout, z+dz);

}

/*  multiply_bigint: Multiplies a BigInt with a BigInt

Stores the result in z.

x: BigInt
y: BigInt
z: empty buffer
*/

void multiply_bigint(BigInt numerator, BigInt y, BigInt z) {
    // Keep track of total and where in the denominator we are
    char total;
    int tensPlace = strlen(y)-1; // Biggest index down to ones place

    int dy=0, dz=1;
    char denom;

    if (*y == '\0') {
        denom = '0';
        dy = 0;
    }else{
        denom = *y;
    }

    multiply_digit_to_BigInt(numerator, denom, carry_in, &total, &carry_out);
    // if total and carry are 0, we're done
    if (total == '0' && carry_out == '0') {
        *z = '\0';
        return;
    }
    // otherwise store the digit we just computed
    *z = total;

    // and make a recursive call to fill in the rest.
    multiply_bigint(x, y+dy, z+dz);

  }

/* make_bigint: Creates and returns a BigInt.

Caller is responsible for freeing.

s: string of digits in the usual order
returns: BigInt
*/
BigInt make_bigint(char *s) {
    char *r = reverse_string(s);
    return (BigInt) r;
}

void test_reverse_string() {
    char *s = "123";
    char *t = reverse_string(s);
    if (strcmp(t, "321") == 0) {
        printf("reverse_string passed\n");
    } else {
        printf("reverse_string failed\n");
    }
}

void test_itoc() {
    char c = itoc(3);
    if (c == '3') {
        printf("itoc passed\n");
    } else {
        printf("itoc failed\n");
    }
}

void test_add_digits() {
    char carry;
    char total;
    char ocarry;
    add_digits('7', '4', '1', &total, &ocarry);
    if (total == '2' && ocarry == '1') {
        printf("add_digits passed\n");
    } else {
        printf("add_digits failed\n");
    }
}

void test_add_bigint() {
    char *s = "1";
    char *t = "99999999999999999999999999999999999999999999";
    char *res = "000000000000000000000000000000000000000000001";

    BigInt big1 = make_bigint(s);
    BigInt big2 = make_bigint(t);
    BigInt big3 = malloc(100);
	  add_bigint(big1, big2, '0', big3);
    //print_bigint(big3);
    if (strcmp(big3, res) == 0) {
        printf("add_bigint passed\n");
    } else {
        printf("add_bigint failed\n");
    }
}

void test_multiply_bigint() {
    char *s = "1200";
    char *t = "1000000000000000000000000000000000000000";
    char *res = "1000000000000000000000000000000000001200";

    BigInt big1 = make_bigint(s);
    BigInt big2 = make_bigint(t);
    BigInt big3 = malloc(100);
	  multiply_bigint(big1, big2, big3);
    //print_bigint(big3);
    if (strcmp(big3, res) == 0) {
        printf("multi_bigint passed\n");
    } else {
        printf("multi_bigint failed\n");
    }
}

int main (int argc, char *argv[])
{
    test_reverse_string();
    test_itoc();
    test_add_digits();
    test_add_bigint();
    //test_multiply_bigint();
    return 0;
}
