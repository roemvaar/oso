#include "unity.h"
#include "util.h"

void setUp(void)
{
    // Setup stuff here
    return;
}

void tearDown(void)
{
    // Clean stuff here
    return;
}

void test_hex_char_to_int_valid_lowercase_letters(void)
{
    TEST_ASSERT_EQUAL(10, hex_char_to_int('a'));
    TEST_ASSERT_EQUAL(15, hex_char_to_int('f'));
}

void test_hex_char_to_int_valid_uppercase_letters(void)
{
    TEST_ASSERT_EQUAL(10, hex_char_to_int('A'));
    TEST_ASSERT_EQUAL(15, hex_char_to_int('F'));
}

void test_hex_char_to_int_valid_digits(void)
{
    TEST_ASSERT_EQUAL(0, hex_char_to_int('0'));
    TEST_ASSERT_EQUAL(9, hex_char_to_int('9'));
}

void test_hex_char_to_int_invalid_characters(void)
{
    TEST_ASSERT_EQUAL(-1, hex_char_to_int('g'));
    TEST_ASSERT_EQUAL(-1, hex_char_to_int('Z'));
    TEST_ASSERT_EQUAL(-1, hex_char_to_int('@'));
}

int main(void)
{
    UNITY_BEGIN();

    /* Util */
    RUN_TEST(test_hex_char_to_int_valid_lowercase_letters);
    RUN_TEST(test_hex_char_to_int_valid_uppercase_letters);
    RUN_TEST(test_hex_char_to_int_valid_digits);
    RUN_TEST(test_hex_char_to_int_invalid_characters);

    return UNITY_END();
}
