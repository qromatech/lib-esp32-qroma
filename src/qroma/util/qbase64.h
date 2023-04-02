#ifndef QROMA_BASE64_H
#define QROMA_BASE64_H

unsigned int q_decode_base64(const unsigned char * input, unsigned int input_length, unsigned char * output);
unsigned int q_encode_base64(const unsigned char * input, unsigned int input_length, unsigned char * output);

#endif