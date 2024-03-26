include_directories(headers source CUNIT teste_estruturas)

add_library(testeLib headers/hash.h source/hash.c
        headers/heap.h source/heap.c
        headers/func_extras.h source/func_extras.c
        headers/arvore_huffman.h source/arvore_huffman.c
        headers/comprimir.h source/comprimir.c
        headers/descomprimir.h source/descomprimir.c
        headers/opcoes.h source/opcoes.c headers/typedefs.h)

add_executable(hash teste_estruturas/teste_hash.c)
add_executable(heap teste_estruturas/teste_heap.c)
add_executable(tree teste_estruturas/teste_arvore_huffman.c)

target_link_libraries(hash testeLib cunit)
target_link_libraries(heap testeLib cunit)
target_link_libraries(tree testeLib cunit)

# Adiciona a flag de ligação para a biblioteca CUnit
target_link_libraries(hash -lcunit)
target_link_libraries(heap -lcunit)
target_link_libraries(tree -lcunit)
