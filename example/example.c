#include <lab/logger.h>
#include <lab/vector.h>

#include <lab/arg_parser.h>

int main(int argc, char* argv[]) {

    lab_arg_parser_t arg_parser;
    lab_arg_parser_init(&arg_parser);

    lab_arg_t arg_help;
    lab_arg_init(&arg_help, "h", "help", "Displays help message", false);
    lab_arg_parser_add_arg(&arg_parser, &arg_help);

    lab_arg_parser_parse(&arg_parser, argc, (const char**)argv);

    lab_arg_parser_free(&arg_parser);

    if(arg_help.found) lab_successln("Help message, I know, very helpful");

    lab_arg_free(&arg_help);

    lab_vec_t vec;
    lab_vec_init(&vec, 1, 8);

    lab_vec_set_grow_fn(&vec, lab_vec_grow_fn_double);

    lab_vec_push_back_arr(&vec, "Hello world!", 13);

    lab_vec_insert(&vec, 5, " cruel", 6);

    lab_vec_remove_arr(&vec, 5, 6);

    lab_vec_t vec2;
    lab_vec_init(&vec2, 1, 8);
    lab_vec_push_back_arr(&vec2, " beautiful", 10);

    lab_vec_insert_vec(&vec, 5, &vec2);

    lab_vec_free(&vec2);

    lab_successln("%s", lab_vec_at(&vec, 0));

    lab_vec_free(&vec);

}