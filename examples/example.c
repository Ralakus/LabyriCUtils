#include <lab/logger.h>
#include <lab/vector.h>
#include <lab/mempool.h>

int main() {

    lab_mempool_t pool;
    lab_mempool_init(&pool, 1, 0);

    lab_mempool_suballoc_t* alloc1 = lab_mempool_suballoc_alloc(&pool, 16);
    lab_mempool_suballoc_t* alloc2 = lab_mempool_suballoc_alloc(&pool, 16);

    lab_mempool_free(&pool);

    lab_vec_t hello_str;
    lab_vec_init(&hello_str, sizeof(char), 0);

    char hello_world[] = "Hello world!";
    lab_vec_push_back_arr(&hello_str, hello_world, sizeof(hello_world));

    char something[] = "cruel ";

    lab_vec_insert(&hello_str, 6, something, sizeof(something) - 1); // -1 to get rid of null termination

    lab_successln("%s", (char*)hello_str.raw_data);

    lab_vec_free(&hello_str);

    return 0;
}