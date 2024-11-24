/* #Public API for the Simple TOML library */

#ifndef STOLML_H
#define STOML_H

#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LENGTH 50
#define MAX_KEYLINE_LENGTH 100
#define STOML_SUCCESS 0
#define STOML_FAILURE -1


typedef struct {
	char key[MAX_KEY_LENGTH];
	char value[MAX_KEY_LENGTH];
} stoml_data;



/*
	stream - file pointer to opened TOML file
	stoml_data - pointer to an array of stoml_data, size >= number of keys
	return type - int: number of keys in stoml_data array
*/
int stoml_read(stoml_data *data[], const int length, FILE *stream);



#endif
