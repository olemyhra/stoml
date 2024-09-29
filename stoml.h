/* #Public API for the Simple TOML library */

#ifndef STOLML_H
#define STOML_H

#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 50
#define MAX_STR_VAL_LENGTH 50
#define STOML_SUCCESS 0
#define STOML_FAILURE -1


struct stoml_data {
	char key[MAX_KEY_LENGTH];
	int value_type;
	char str_value[MAX_STR_VAL_LENGTH];
	int int_value;
};

/*
	file_name - name of the TOML file
	return type - int: 0 on success
*/
int stoml_open(const char *file_name);


/*
	return type - int: number of keys found
*/
int stoml_count_keys();


/*
	stream - file pointer to opened TOML file
	stoml_data - pointer to an array of stoml_data, size >= number of keys
	return type - int: number of keys in stoml_data array
*/
int stoml_read(struct stoml_data *data[], const int length);


/*
	stream - file pointer to opened TOML file
	return type - int: 0 on sucess
*/
int stoml_close();


#endif
