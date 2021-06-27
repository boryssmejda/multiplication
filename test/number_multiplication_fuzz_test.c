#include "number_multiplication.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    if (Size < 4)
    {
        return 0;
    }
    char* num1 = malloc(Size * sizeof(uint8_t));
    char* num2 = malloc(Size * sizeof(uint8_t));

    memcpy(num1, Data, Size * sizeof(uint8_t));
    memcpy(num2, Data, Size * sizeof(uint8_t));
    num2[Size - 1] = '\0';
    num1[Size - 1] = '\0';

    char* result = multiply(num1, num2);
    if (result)
    {
        free(result);
    }

    free(num1);
    free(num2);
    return 0;  // Non-zero return values are reserved for future use.
}
