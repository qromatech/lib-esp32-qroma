#include "qbase64.h"
#include "base64.hpp"

unsigned int q_decode_base64(const unsigned char * input, unsigned int input_length, unsigned char * output) {
  return decode_base64(input, input_length, output);
}


unsigned int q_encode_base64(const unsigned char * input, unsigned int input_length, unsigned char * output) {
  return encode_base64(input, input_length, output);
}
