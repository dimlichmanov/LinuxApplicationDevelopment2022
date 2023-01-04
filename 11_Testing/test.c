#include "unity.h"
#include "buf.h"

/* Functions needed for Unity integration. They are called before and after each test scenario call*/
void setUp(void) {
    return;
}
void tearDown(void) {
    return;
}

void test_InitializationFree(void)
{
    float *a = 0;
    TEST_ASSERT_EQUAL_INT(0, buf_capacity(a)); 
    TEST_ASSERT_EQUAL_INT(0, buf_size(a));
    buf_push(a, 1.3f);
    TEST_ASSERT_EQUAL_INT(1, buf_size(a));
    TEST_ASSERT_EQUAL_FLOAT((float)1.3f, a[0]);
    buf_clear(a);
    TEST_ASSERT_EQUAL_INT(0, buf_size(a));
    TEST_ASSERT_NOT_NULL(a);
    buf_free(a);
    TEST_ASSERT_NULL(a);
}

void test_Null(void)
{   
    float *a = 0;
    TEST_ASSERT_EQUAL_INT(0, buf_capacity(a)); 
    TEST_ASSERT_NULL(a);
}

void test_Push (void)
{
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    TEST_ASSERT_EQUAL_INT64(10000, buf_size(ai));
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    TEST_ASSERT_EQUAL_INT64(10000, match);
    buf_free(ai);
}

void test_Grow(void) {
    /* buf_grow(), buf_trunc() */
    long *ai = 0;
    buf_grow(ai, 1000);
    TEST_ASSERT_EQUAL_INT(1000, buf_capacity(ai));
    TEST_ASSERT_EQUAL_INT(0, buf_size(ai));
    buf_trunc(ai, 100);
    TEST_ASSERT_EQUAL_INT(100, buf_capacity(ai));
    buf_free(ai);
}

void test_Pop(void) {
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);

    TEST_ASSERT_EQUAL_INT(4, buf_size(a));
    TEST_ASSERT_EQUAL_FLOAT((float)1.4f, buf_pop(a));
    buf_trunc(a, 3);
   
    TEST_ASSERT_EQUAL_INT(3, buf_size(a));
    TEST_ASSERT_EQUAL_FLOAT((float)1.3f, buf_pop(a));
    TEST_ASSERT_EQUAL_FLOAT((float)1.2f, buf_pop(a));
    TEST_ASSERT_EQUAL_FLOAT((float)1.1f, buf_pop(a));
    TEST_ASSERT_EQUAL_INT(0, buf_size(a));
    buf_free(a);

}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_InitializationFree);
    RUN_TEST(test_Null);
    RUN_TEST(test_Push);
    RUN_TEST(test_Grow);
    RUN_TEST(test_Pop);
    return UNITY_END();
}