#include "logger.h"
#include "vector.h"

int main() {

    lab_vec_t hello_str;
    lab_vec_init(&hello_str, sizeof(char), 0);

    char hello_world[] = "Hello world!";
    lab_vec_push_back_arr(&hello_str, hello_world, sizeof(hello_world));

    lab_successln("%s", (char*)hello_str.raw_data);

    lab_vec_free(&hello_str);

    return 0;
}