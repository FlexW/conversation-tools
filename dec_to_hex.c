/**
 * @file dec_to_hex.c
 * Program to convert decimal into hexadecimal.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>

/**
 * Converts a decimal value digit into hexadecimal digit.
 * @param hex_digit Decimal digit
 * @returns Hexadecimal value. On error: -1.
 */
char get_hex_digit_from_dec(int dec) {
  switch (dec) {
  case 0: return '0';
  case 1: return '1';
  case 2: return '2';
  case 3: return '3';
  case 4: return '4';
  case 5: return '5';
  case 6: return '6';
  case 7: return '7';
  case 8: return '8';
  case 9: return '9';
  case 10: return 'a';
  case 11: return 'b';
  case 12: return 'c';
  case 13: return 'd';
  case 14: return 'e';
  case 15: return 'f';
  default: return -1;
  }
}

/**
 * Inserts a char into a string. The buffer where the string is stored
 * should be at least one place longer than the current string needs space.
 * String is expected to be 0 terminated.
 * @param pos Position to insert the char.
 * @param ch Char to insert.
 * @param str String where ch gets insert.
 * @param strlen Length of the string.
 */
void insert_char(int pos, char* ch, char* str, int strlen) {
  if (pos > strlen)
    return;
  
  for (int i = strlen; i >= pos; i--) {
    str[i + 1] = str[i];
  }
  str[pos] = *ch;
}

/**
 * Converts a decimal number into hexadecimal number.
 * @param dec Decimal number.
 * @returns Hexadecimal Number. On error: NULL. Don't forget to free.
 */
char* dec_to_hex(char* dec) {
  int pos = 0;
  int output_size = 20;
  int output_len = 0;
  char* output_ptr;
  mpz_t num;
  mpz_t remainder;
  mpz_inits(num, remainder, NULL);
  mpz_set_str(num, dec, 10);

  output_ptr = malloc(sizeof(char) * output_size);
  if (output_ptr == NULL)
    return NULL;
  output_ptr[0] = '\0';
  
  while (mpz_cmp_ui(num, 0)) {
    mpz_fdiv_qr_ui(num, remainder, num, 16);
    char hex_val = get_hex_digit_from_dec(mpz_get_ui(remainder));
    if (hex_val == -1) {
      return NULL;
    }
    pos++;
    if (output_len == output_size - 1) {
      output_size = output_size * 2;
      output_ptr = realloc(output_ptr, sizeof(char) * output_size);
      if (output_ptr == NULL)
	return NULL;
    }
    insert_char(0, &hex_val, output_ptr, output_len);
    output_len++;
  }

  if (output_len == 0) {
    output_ptr[0] = '0';
    output_ptr[1] = '\0';
  }
  return strdup(output_ptr);
}

void usage(char* app_name) {
  printf("Usage: %s <DECIMAL_NUMBER>\n", app_name);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    usage(argv[0]);
    return 1;
  }
  char* result = dec_to_hex(argv[1]);

  if (result == NULL) {
    printf("Error while processing number!\n");
    return 1;
  }
  printf("%s\n", result);
  free(result);

  return 0;
}
