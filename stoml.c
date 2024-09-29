#include "stoml.h"

static FILE *stoml_file = NULL;

int stoml_open(const char *file_name) 
{
	stoml_file = fopen(file_name, "r");
	if(stoml_file != NULL) {
		return STOML_SUCCESS;
	} else {
		return STOML_FAILURE;
	}
} 


int stoml_count_keys()
{
	ssize_t bytes_read = 0;
	size_t line_length = MAX_STR_VAL_LENGTH;
	char *line = NULL;
	const char *key_identifier = " = ";
	char *key_identifier_location = NULL;
	int number_of_keys_found = 0;
	
	rewind(stoml_file);
	line =	(char *) malloc(sizeof(char ) * MAX_STR_VAL_LENGTH);
	if(line != NULL) {
		if(stoml_file != NULL) {
			while((bytes_read = getline(&line, &line_length, stoml_file)) != -1) {
				if (line[0] == 0xA || line[0] == 0x23)	/* \n or # */
					continue;
				key_identifier_location = strstr(line, key_identifier);
				if(key_identifier_location != NULL)
					number_of_keys_found++;	
			}
			return number_of_keys_found;
		} else {
			return STOML_FAILURE;
		}
	} else {
		return STOML_FAILURE;
	}
}


int stoml_read(struct stoml_data *data[], const int length)
{
	ssize_t bytes_read = 0;
	size_t line_length = MAX_STR_VAL_LENGTH;
	char *line = NULL;
	const char *key_delimiter = "=";
	const char *key_identifier = " = ";
	char *key_identifier_location = NULL;
	char *key = NULL;
	char *value = NULL;
	int data_index = 0;

	rewind(stoml_file);
	line =	(char *) malloc(sizeof(char ) * MAX_STR_VAL_LENGTH);
	if(line != NULL) {
		if(stoml_file != NULL) {
			while((bytes_read = getline(&line, &line_length, stoml_file)) != -1) {
				if (line[0] == 0xA || line[0] == 0x23)	/* \n or # */
					continue;
				key_identifier_location = strstr(line, key_identifier);
				if(key_identifier_location != NULL) {
					data[data_index] = (struct stoml_data *) malloc(sizeof(struct stoml_data));		
					key = strtok(line, key_delimiter);
					if (key != NULL) 
						strcpy(data[data_index]->key, key);

					value = strtok(NULL, key_delimiter);
					if (value != NULL) 
						strcpy(data[data_index]->str_value, value);
					data_index++;
				}		
			}
			return STOML_SUCCESS;
		} else {
			return STOML_FAILURE;
		}
	} else {
		return STOML_FAILURE;
	}
}



int stoml_close()
{
 	return fclose(stoml_file);
}
