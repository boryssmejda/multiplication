#include "number_multiplication.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    uint32_t length;
    char** ptr;
}multiplied_numbers;

static void inline xor_swap(char* a, char* b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

static void inplace_reverse(char* num)
{
    assert(num);

    char* end = num + strlen(num) - 1;

    while (num < end)
    {
        xor_swap(num, end);
        ++num;
        --end;
    }
}

static char* multiply_by_single_digit(const char* const num, const char digit)
{
    uint32_t number_minimum_size = strlen(num) + 1;
    char* result = calloc((number_minimum_size + 1), sizeof(char));

    uint32_t carry = 0;
    uint32_t insertion_position_in_result = 0;
    for(int i = strlen(num) - 1; i >= 0; --i)
    {
        uint8_t multiplication_result = (num[i] - '0') * (digit - '0') + carry;

        carry = multiplication_result / 10;
        multiplication_result %= 10;

        result[insertion_position_in_result++] = (char)(multiplication_result + '0');
    }

    if (carry)
    {
       result[insertion_position_in_result++] = (char)(carry + '0');
    }

    result[insertion_position_in_result] = '\0';

    inplace_reverse(result);
    return result;
}

static multiplied_numbers allocate_space_for_multiplied_numbers(const uint32_t desired_container_size)
{
    multiplied_numbers numbers = {.length = desired_container_size, .ptr = NULL};
    numbers.ptr = malloc(desired_container_size * sizeof(numbers.ptr));

    assert(numbers.ptr);

    return numbers;
}

static multiplied_numbers multiply_by_every_digit(const char* const num1, const char* const num2)
{
    assert(num1 && num2);

    size_t container_size_after_multiplication = strlen(num2);
    multiplied_numbers numbers = allocate_space_for_multiplied_numbers(container_size_after_multiplication);

    for (int i = strlen(num2) - 1, j = 0; i >= 0; --i, ++j)
    {
        numbers.ptr[j] = multiply_by_single_digit(num1, num2[i]);
    }

    return numbers;
}

static void shift_left_indexes_by(char** num, uint32_t number_of_positions_to_shift)
{
    assert(num);

    uint32_t old_number_size = strlen(*num);
    uint32_t new_number_size = strlen(*num) + number_of_positions_to_shift;

    char* tmp = realloc(*num, new_number_size + 1);
    assert(tmp);
    *num = tmp;

    for (int i = old_number_size; i < new_number_size; ++i)
    {
        num[0][i] = '0';
    }

    num[0][new_number_size] = '\0';
}

static void multiply_by_power_of_ten(multiplied_numbers* const numbers)
{
    for (int i = 1; i < numbers->length; ++i)
    {
        shift_left_indexes_by(&numbers->ptr[i], i);
    }
}

static void add_to_first_number(char* num1, const char* num2)
{
    uint8_t carry = 0;
    for (int i = 0; i < strlen(num1); ++i)
    {
        uint8_t sum = 0;
        if (i < strlen(num1) && i < strlen(num2))
        {
            sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        }
        else
        {
            sum = carry + (num1[i] - '0');
        }

        carry = sum / 10;
        sum %= 10;

        num1[i] = (char)(sum + '0');
    }

    if (carry)
    {
        num1[strlen(num1)] = (char)(carry + '0');
    }
}

static char* add_numbers(const multiplied_numbers* const numbers)
{
    assert(numbers && numbers->length && numbers->ptr);

    uint32_t last_element = numbers->length;
    size_t last_element_length = strlen(numbers->ptr[last_element - 1]);
    // +2, one for \0, one if the buffer needs more space to accomodate
    // the resulting number
    size_t size_to_allocate = last_element_length + 2;
    char* result = calloc(size_to_allocate, sizeof(char));

    inplace_reverse(numbers->ptr[last_element - 1]);
    strcpy(result, numbers->ptr[last_element - 1]);

    for (int i = numbers->length - 2; i >= 0; --i)
    {
        inplace_reverse(numbers->ptr[i]);
        add_to_first_number(result, numbers->ptr[i]);
    }

    inplace_reverse(result);

    return result;
}

static void deallocate_memory_for_multiplied_numbers(multiplied_numbers* numbers)
{
    assert(numbers);
    for(int i = 0; i < numbers->length; ++i)
    {
        free(numbers->ptr[i]);
    }

    free(numbers->ptr);
    numbers->length = 0;
}

bool is_number_correct(const char* num)
{
    for (int i = 0; i < strlen(num); ++i)
    {
        if (!(num[i] >= '0' && num[i] <= '9'))
        {
            return false;
        }
    }

    return true;
}

char * multiply(char *num1, char *num2)
{
    if (!num1 || !num2)
    {
        return NULL;
    }

    if (strlen(num1) == 0 || strlen(num2) == 0)
    {
        return NULL;
    }

    if(!is_number_correct(num1) || !is_number_correct(num2))
    {
        return NULL;
    }

    if (!strcmp(num1, "0") || !strcmp(num2, "0"))
    {
        char* multiplication_result = malloc(2 * sizeof(char));
        strcpy(multiplication_result, "0");
        return multiplication_result;
    }

    multiplied_numbers numbers = multiply_by_every_digit(num1, num2);
    multiply_by_power_of_ten(&numbers);

    char* multiplication_result = add_numbers(&numbers);
    deallocate_memory_for_multiplied_numbers(&numbers);

    return multiplication_result;
}
