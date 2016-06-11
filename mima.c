/* fuck portability */
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
struct mima_num {
  size_t integ, fract;
  uint64_t sign:1,
           infinity:1,
           nan:1;
  uint64_t num[];
};
typedef struct mima_num* mima_num;

uint64_t mima_prec = 10;
mima_num mima_from_string(const char *);
mima_num mima_from_int8(int8_t);
mima_num mima_from_uint8(uint8_t);
mima_num mima_from_int16(int16_t);
mima_num mima_from_uint16(uint16_t);
mima_num mima_from_int32(int32_t);
mima_num mima_from_uint32(uint32_t);
mima_num mima_from_int64(int64_t);
mima_num mima_from_uint64(uint64_t);
mima_num mima_from_float(float);
mima_num mima_from_double(double);

#define mima_from(x) _Generic((0,x),  \
       char*: mima_from_string,       \
      int8_t: mima_from_int8,         \
     uint8_t: mima_from_uint8,        \
     int16_t: mima_from_int16,        \
    uint16_t: mima_from_uint16,       \
     int32_t: mima_from_int32,        \
    uint32_t: mima_from_uint32,       \
     int64_t: mima_from_int64,        \
    uint64_t: mima_from_uint64,       \
       float: mima_from_float,        \
      double: mima_from_double,       \
     default: mima_err)(x)

mima_num mima_sum(const mima_num, const mima_num);
mima_num mima_sub(const mima_num, const mima_num);
mima_num mima_mul(const mima_num, const mima_num);
mima_num mima_div(const mima_num, const mima_num);

mima_num mima_sum(const mima_num num1, const mima_num num2) {
  if (!num1->sign && num2->sign) {
    num2->sign = 0;
    return mima_sub(num1, num2);
  }
  else if (num1->sign && !num2->sign) {
    num1->sign = 0;
    return mima_sub(num2, num1);
  }
  if (num1->infinity || num1->nan) return num1;
  if (num2->infinity || num2->nan) return num2;

  size_t integ = num1->integ > num2->integ ? num1->integ : num2->integ,
         fract = num1->fract > num2->fract ? num1->fract : num2->fract;
  mima_num sum = malloc(sizeof(struct mima_num) + integ + fract);
  if (!sum) return NULL;
  sum->sign = num1->sign;

  if (num1->fract > num2->fract) memcpy(&sum->num[integ+num2->fract+1], &num1->num[num1->integ+num2->fract+1], num1->fract-num2->fract);
  /*for (size_t i = fract; i > 0; i--) {*/
    /*sum->num[i+integ]*/
  /*}*/

  /*__builtin_uaddll_overflow();*/
  return sum;
}

mima_num mima_div(const mima_num num1, const mima_num num2) {
  (void) num1;
  (void) num2;
  return NULL;
}

mima_num mima_sub(const mima_num num1, const mima_num num2) {
  (void) num1;
  (void) num2;
  return NULL;
}

mima_num mima_mul(const mima_num num1, const mima_num num2) {
  (void) num1;
  (void) num2;
  return NULL;
}
char* mima_to_str(mima_num num) {
  (void) num;
  size_t len;
  (void) len;
  char *str = NULL;
  return str;
}
