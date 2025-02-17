#include "stoml.h"

#define TRIM_MAX_LENGTH 100
#define NULL_TERM_CHAR 1

typedef struct toml_data {
	char key[MAX_KEY_LENGTH];
	char value[MAX_KEY_LENGTH];
} stoml_data;


static void create_node(char *line, stoml_data **node);
static int create_hash_code(const char *key, const int length);
static void insert_hashtable(stoml_data *data[], const int length, stoml_data *data_item);
static void trim(char *string);


/*
	Public function
*/
int stoml_read(stoml_data *data[], const int length, FILE *stream) {

	if (data == NULL) 
		return STOML_FAILURE;

	if (length <= 0)
		return STOML_FAILURE;

	char c = '\0';

	bool key_line = false;
	bool comment = false;

	char key_line_data[100];
	memset(key_line_data, 0, sizeof(key_line_data));
	short key_line_data_index = 0;
	int line_counter = 0;

	stoml_data *node = NULL;

	c = getc(stream);
	
	if (c == EOF)
		return STOML_FAILURE;

	while (c != EOF && line_counter < length) {
		if (c == '#') {
			comment = true;

		} else if (c == '\n') {
			if (key_line) {
				key_line_data[key_line_data_index] = '\0';
				create_node(key_line_data, &node);

				if (node != NULL) {
					insert_hashtable(data, length, node);
					line_counter++;
				} else {
					return STOML_FAILURE;
				}
			}

			comment = false;
			key_line = false;

			memset(key_line_data, 0, sizeof(key_line_data));
			key_line_data_index = 0;

		} else if (!comment) {
			key_line = true;
		}
	
		if (key_line) {
			if (!comment) {
					key_line_data[key_line_data_index] = c;
				if (key_line_data_index < MAX_KEYLINE_LENGTH)
					key_line_data_index++;
			}
		} 

		c = getc(stream);

	}

	if (line_counter == 0)
		return STOML_FAILURE;


	return STOML_SUCCESS;
}


/*
	Public function
*/
stoml_data *stoml_search(stoml_data *data[], const int length, const char *key) {

	int hashtable_index = create_hash_code(key, length);
	int search_counter = 0;
	
	while (data[hashtable_index] != NULL) {
		if (strncmp(key, &(*(data[hashtable_index])->key), MAX_KEY_LENGTH) == 0) 
			return data[hashtable_index];
		hashtable_index++;
		hashtable_index %= length;

		if (++search_counter >= length)
			break;
	}
		
	return NULL;
}


/*
	Public function
*/
char *get_key(stoml_data *node) {
	return node->key;
}


/*
	Public function
*/
char *get_value(stoml_data *node) {
	return node->value;
}


/*
	Private function

	-- Creates a stoml_data node with the supplied key and value --

	line - keyline read from the TOML data
	node - pointer to node where the data should be stored
	return value: none

*/
static void create_node(char *line, stoml_data **node) {
	char *key = NULL;
	char *value = NULL;

	key = strtok(line, "=");
	value = strtok(NULL, "=");

	if (value == NULL) /* Separator not found */
		return; 

	trim(key);
	trim(value);
	
	*node = (stoml_data *)  malloc(sizeof(stoml_data));
	if (*node != NULL) {
		strncpy((*node)->key, key, MAX_KEY_LENGTH - NULL_TERM_CHAR);
		strncpy((*node)->value, value, MAX_KEY_LENGTH - NULL_TERM_CHAR);
	}
	
}



/*
	Private function

	-- Generates a hash code value based upon the key --

	key - key to be used to generate hash index value
	length - length of the hash table
*/
static int create_hash_code(const char *key, const int length) {
	int index = 0;

	for (int i=0;i<MAX_KEY_LENGTH;i++) {
		if (key[i] == '\0')
			break;
		index += key[i];
	}

	return index % length;
}


/*
	Private function

	-- Inserts a stoml_data node pointer into the hash table --

	data - pointer to hashtable
	length - length of hashtable
	data_item - pointer to item of stoml_data
*/
static void insert_hashtable(stoml_data *data[], const int length,  stoml_data *data_item) {

	int hashtable_index = create_hash_code(data_item->key, length);
	
	while (data[hashtable_index] != NULL && *(data[hashtable_index])->key != '\0') {
		hashtable_index++;

		hashtable_index %= length;
	}

	data[hashtable_index] = data_item;
}


/*
	Private function

	-- Removes space and quotation marks from the string --

	string - null terminated string
*/
static void trim(char *string) {
	short i = 0, z = 0;
	char tmp_string[TRIM_MAX_LENGTH];
	memset(tmp_string, 0, sizeof(tmp_string));

	while (string[i] != 0x00) {
		if (string[i] != 0x20 && string[i] != 0x22) {	/* 0x20 = Space, 0x22 = " */
			tmp_string[z] = string[i];
			z++;
		}
		i++;
	}
	tmp_string[z] = '\0';
	
	strcpy(string, tmp_string);

}

