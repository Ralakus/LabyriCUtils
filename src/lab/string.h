#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "vector.h"

typedef lab_vec_t lab_str_t;

/*
    Inits emtpy string
*/
extern bool lab_str_init(lab_str_t* str, size_t size);

/*
    Makes from char*
*/
extern bool lab_str_make      (lab_str_t* str, const char* cstr);
extern bool lab_str_make_sized(lab_str_t* str, const char* cstr, size_t size);

/*
    Free string
*/
extern void lab_str_free(lab_str_t* str);

/*
    Returns length of string, does not inlcude null termination
*/
extern size_t lab_str_len(lab_str_t* str);

/*
    Returns string pointer
*/
extern const char* lab_str_cstr(lab_str_t* str);

/*
    Inserts one string into another
    Returns location to inserted string
*/
extern const char* lab_str_insert     (lab_str_t* dest, lab_str_t*  src, size_t index);
extern const char* lab_str_insert_cstr(lab_str_t* dest, const char* src, size_t index);

/*
    Appends one string to the end of another
*/
extern bool lab_str_append     (lab_str_t* dest, lab_str_t* src);
extern bool lab_str_append_cstr(lab_str_t* dest, const char* src);

/*
    Gets substring, frees dest
*/
extern bool lab_str_substr(const lab_str_t* src, lab_str_t* dest, size_t i1, size_t i2);

/*
    Makes all characters uppercase
*/
extern void lab_str_to_upper(lab_str_t* str);

/*
    Makes all characters lowercase
*/
extern void lab_str_to_lower(lab_str_t* str);

#ifdef __cplusplus
}
#endif