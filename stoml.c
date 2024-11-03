#include "stoml.h"

static FILE *stoml_file = NULL;
static int create_hash_code(const char *key);
static void  insert_tag_hashtable(const struct stoml_data *data[], const int length, const struct stoml_data *data_item);

int stoml_open_file(const char *file_name) 
	{
	stoml_file = fopen(file_name, "r");
	if(stoml_file != NULL) {
		return STOML_SUCCESS;
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

					if(++data_index >= length)
						break;
				}
			}
			return STOML_SUCCESS;
		} else {
			free(line);
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


static int create_hash_code(const char *key)
{
	int index = 0;

	for (int i=0;i<MAX_KEY_LENGTH;i++) {
		if (key[i] == '\0')
			break;
		index += key[i];
	}

	return index % MAX_KEY_LENGTH;
}



static void insert_tag_hashtable(const struct stoml_data *data[],const int length,  const struct stoml_data *data_item)
{
	int hashtable_index = create_hash_code(data_item->key);
	
	while (data[hashtable_index] != NULL && *(data[hashtable_index]->key) != '\0') {
		hashtable_index++;

		hashtable_index %= length;
	}
	data[hashtable_index] = data_item;
}
