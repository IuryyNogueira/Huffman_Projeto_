include_directories (headers source)

add_library(HuffLib headers/hash.h source/hash.c
        headers/heap.h source/heap.c
        headers/func_extras.h source/func_extras.c
        headers/arvore_huffman.h source/arvore_huffman.c
        headers/comprimir.h source/comprimir.c
        headers/descomprimir.h source/descomprimir.c
        headers/opcoes.h source/opcoes.c headers/typedefs.h)

add_executable(Huffman source/main.c)

target_link_libraries(Huffman HuffLib)