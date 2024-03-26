#include "CUnit/Basic.h"
#include "heap.h"

void create_test()
{
    HEAP *h = criar_heap();
    CU_ASSERT_PTR_NOT_NULL(h)

    for (int i = 1; i < HEAP_MAX_SIZE; ++i)
    {
        CU_ASSERT_PTR_NULL(h->data[i])
    }

    CU_ASSERT_EQUAL(h->size, 0)
}

void swap_data_test()
{ 
    HEAP *h = criar_heap();

    h->data[1] = "WELLINTO";
    h->data[2] = "DAVIVIE";

    CU_ASSERT_EQUAL("WELLINTO", h->data[1])
    CU_ASSERT_EQUAL("DAVIVIE", h->data[2])

    void *p1 = h->data[1];
    void *p2 = h->data[2];

    CU_ASSERT_EQUAL("WELLINTO", p1)
    CU_ASSERT_EQUAL("DAVIVIE", p2)

    swap(&h->data[1], &h->data[2]);

    CU_ASSERT_EQUAL("WELLINTO", h->data[2])
    CU_ASSERT_EQUAL("DAVIVIE", h->data[1])

    CU_ASSERT_EQUAL(p2, h->data[1])
    CU_ASSERT_EQUAL(p1, h->data[2])
}

void enqueue_test()
{
    HEAP *h = criar_heap();

    // Adiciona elementos à heap
    enqueue(h, 1, "A");
    enqueue(h, 2, "B");
    enqueue(h, 3, "C");
    enqueue(h, 4, "D");

    // Remove e verifica se os elementos estão na ordem correta
    CU_ASSERT_STRING_EQUAL(dequeue(h), "A");
    CU_ASSERT_STRING_EQUAL(dequeue(h), "B");
    CU_ASSERT_STRING_EQUAL(dequeue(h), "C");
    CU_ASSERT_STRING_EQUAL(dequeue(h), "D");

    // Verifica se a heap está vazia após a remoção de todos os elementos
    CU_ASSERT_PTR_NULL(dequeue(h));
}


int main (int argc, char** argv)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (NULL == CU_add_test(pSuite, "create_heap test", create_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "swap_data test", swap_data_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "enqueue test", enqueue_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}