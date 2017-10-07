/**
 * @file hex_to_dec.c
 * @brief Program to convert from hexadecimal to decimal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

/**
 * Gets the number of digits of the number.
 * @param num Number.
 * @returns Number of digits.
 */
int digits_of_num(int num) {
  if (num == 0)
    return 1;
  
  int cnt = 0;
  while (num != 0) {
    num /= 10;
    cnt++;
  }
  return cnt;
}

/**
 * Converts a hexadecimal value digit into decimal digit.
 * @param hex_digit Hexadecimal digit
 * @returns Decimal value. On error: -1.
 */
int get_dec_digit_from_hex(char hex_digit) {
  switch (hex_digit) {
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  case '3': return 3;
  case '4': return 4;
  case '5': return 5;
  case '6': return 6;
  case '7': return 7;
  case '8': return 8;
  case '9': return 9;
  case 'a': return 10;
  case 'b': return 11;
  case 'c': return 12;
  case 'd': return 13;
  case 'e': return 14;
  case 'f': return 15;
  default: return -1;
  }
}

/**
 * Converts a hexadecimal number to decimal number.
 * @param hex Hexadecimal number. All digits should be in lowercase.
 * @returns If hex is valid then decimal number. On error: NULL.
 * The returned char pointer should be freed if not anymore used.
 */
char* hex_to_dec(char* hex) {
  mpz_t mpz_result;
  mpz_t p_result;
  mpz_inits(mpz_result, p_result, NULL);
  unsigned long long int result = 0;
  int hlen = strlen(hex);
  int index = hlen - 1;
  
  for (int i = 0; i < hlen; i++) {
    char c_digit = hex[i];
    int d_digit = get_dec_digit_from_hex(c_digit);
    if (d_digit == -1)
      return NULL;

    mpz_ui_pow_ui(p_result, 16, index);
    mpz_mul_ui(p_result, p_result, d_digit);
    mpz_add(mpz_result, mpz_result, p_result);
    index--;
  }
  char* result_str = mpz_get_str(NULL, 10, mpz_result);
  mpz_clear(mpz_result);
  mpz_clear(p_result);
  return result_str;
}

void usage(char* app_name) {
  printf("Usage: %s <HEXADECIMAL_NUMBER>\n\n\
Recognized formats: a7b 0xa7b #a7b a7bh\n", app_name);
}

/**
 * Removes the sign that identifies a number as hexadecimal.
 * If no sign it does nothing.
 * The function does not check if it's a hexadecimal number.
 * Recognized formats: 0xa7f #a7f a7fh
 * @param hex Hexadecimal number.
 * @returns Hexadecimal number without sign. On error: NULL.
 * Note: Free number if not anymore used. 
 */
char* rm_hex_sign(char* hex) {
  int hlen = strlen(hex);
  
  if (hex[0] == '#' && hlen > 1) {
    char* nhex = malloc(sizeof(char) * (hlen));
    if (nhex == NULL)
      return NULL;
    for (int i = 0; i < hlen - 1; i++)
      nhex[i] = hex[i + 1];
    return nhex;
  }
  if (hex[0] == '0' && hex[1] == 'x' && hlen > 2) {
    char* nhex = malloc(sizeof(char) * (hlen - 1));
    if (nhex == NULL)
      return NULL;
    for (int i = 0; i < hlen - 1; i++)
      nhex[i] = hex[i + 2];
    return nhex;
  }
  if (hex[hlen - 1] == 'h' && hlen > 1) {
    char* nhex = malloc(sizeof(char) * (hlen));
    if (nhex == NULL)
      return NULL;
    for (int i = 0; i < hlen - 1; i++)
      nhex[i] = hex[i];
    return nhex;
  }
  return hex;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    return 1;
  }
  char* num = rm_hex_sign(argv[1]);
  char* result = hex_to_dec(num);
  if (num != argv[1])
    free(num);

  if (result == NULL) {
    printf("Error while processing number!\n");
    return 1;
  }
  printf("%s\n", result);
  free(result);

  return 0;
}
