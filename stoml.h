/* #Public API for the Simple TOML library */

#ifndef STOML_H
#define STOML_H


#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LENGTH 50
#define MAX_KEYLINE_LENGTH 100
#define STOML_SUCCESS 0
#define STOML_FAILURE 1


typedef struct toml_data stoml_data;



/*
	stream - pointer to input TOML data, file or stdin
	data - array of stoml_data pointers
	length - length of data
	return type - int: 0->success
*/
int stoml_read(stoml_data *data[], const int length, FILE *stream);


/*
	data - array of stoml_data pointers
	length - length of data
	key - null terminated string to search for as key
	return type - stoml_data *: stoml_data node or NULL-> key not found
*/
stoml_data *stoml_search(stoml_data *data[], const int length, const char *key);


/*
	node - pointer to stoml_data structure
	return type - pointer null terminated string
*/
char *get_key(stoml_data *node);


/*
	node - pointer to stoml_data structure
	return type - pointer to null terminated string
*/
char *get_value(stoml_data *node);

#endif
