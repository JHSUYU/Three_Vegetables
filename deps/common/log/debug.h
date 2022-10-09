#ifndef DEBUG_H_
#define DEBUG_H_
#include <stdio.h>
#define pr_debug(fmt, ...) printf("[%s]<%d>" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#endif