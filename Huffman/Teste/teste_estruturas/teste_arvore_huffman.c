#include "CUnit/Basic.h"
#include "arvore_huffman.h"
#include "heap.h"

void create_node_arvore_test()
{
    TREE *t = create_node_arvore('I', 77, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(t);
    CU_ASSERT_EQUAL(t->c, 'I');
    CU_ASSERT_EQUAL(t->frequency, 77);
    CU_ASSERT_PTR_NULL(t->left);
    CU_ASSERT_PTR_NULL(t->right);

    t->left = create_node_arvore('U', 22, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(t->left);
    CU_ASSERT_EQUAL(t->left->c, 'U');
    CU_ASSERT_EQUAL(t->left->frequency, 22);
    CU_ASSERT_PTR_NULL(t->left->left);
    CU_ASSERT_PTR_NULL(t->left->right);

    t->right = create_node_arvore('R', 55, NULL, NULL);

    CU_ASSERT_PTR_NOT_NULL(t->right);
    CU_ASSERT_EQUAL(t->right->c, 'R');
    CU_ASSERT_EQUAL(t->right->frequency, 55);
    CU_ASSERT_PTR_NULL(t->right->left);
    CU_ASSERT_PTR_NULL(t->right->right);
}


void tree_size_test()
{
    TREE *t = NULL;
    CU_ASSERT_EQUAL(pegar_tamanho_tree(t), 0);

    t = create_node_arvore('*', 77, NULL, NULL);
    t->left = create_node_arvore('A', 22, NULL, NULL);
    t->right = create_node_arvore('B', 55, NULL, NULL);
    CU_ASSERT_EQUAL(pegar_tamanho_tree(t), 3);
}

HEAP* get_aux_heap()
{
    HEAP *h = criar_heap();

    enqueue(h, 6, create_node_arvore('A', 6, NULL, NULL));
    enqueue(h, 5, create_node_arvore('B', 5, NULL, NULL));
    enqueue(h, 4, create_node_arvore('C', 4, NULL, NULL));
    enqueue(h, 3, create_node_arvore('D', 3, NULL, NULL));
    enqueue(h, 2, create_node_arvore('E', 2, NULL, NULL));
    enqueue(h, 1, create_node_arvore('F', 1, NULL, NULL));

    return h;
}

void create_huffman_tree_test()
{
    TREE *t = criar_arvore_huffman(get_aux_heap());

    CU_ASSERT_EQUAL(t->c, '*');
    CU_ASSERT_EQUAL(t->left->c, '*');
    CU_ASSERT_EQUAL(t->left->left->c, 'C');
    CU_ASSERT_EQUAL(t->left->right->c, 'B');

    CU_ASSERT_EQUAL(t->right->c, '*');
    CU_ASSERT_EQUAL(t->right->left->c, '*');
    CU_ASSERT_EQUAL(t->right->left->left->c, 'D');
    CU_ASSERT_EQUAL(t->right->left->right->c, '*');
    CU_ASSERT_EQUAL(t->right->left->right->left->c, 'F');
    CU_ASSERT_EQUAL(t->right->left->right->right->c, 'E');
    CU_ASSERT_EQUAL(t->right->right->c, 'A');
}

void mapear_caminhos_test()
{
    HASH *ht = create_hash();
    char path[20];

    mapear_caminhos(criar_arvore_huffman(get_aux_heap()), ht, path, 0);

    CU_ASSERT_STRING_EQUAL(get(ht, 'A'), "11");
    CU_ASSERT_STRING_EQUAL(get(ht, 'B'), "01");
    CU_ASSERT_STRING_EQUAL(get(ht, 'C'), "00");
    CU_ASSERT_STRING_EQUAL(get(ht, 'D'), "100");
    CU_ASSERT_STRING_EQUAL(get(ht, 'E'), "1011");
    CU_ASSERT_STRING_EQUAL(get(ht, 'F'), "1010");
}

int main (int argc, char** argv)
{
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    if (NULL == CU_add_test(pSuite, "create_node_arvore test", create_node_arvore_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "get_tree_size test", tree_size_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "create_huffman_tree test", create_huffman_tree_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "mapear_caminhos test", mapear_caminhos_test))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}