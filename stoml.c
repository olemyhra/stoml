#include "stoml.h"

#define TRIM_MAX_LENGTH 100
#define NULL_TERM_CHAR 1

static void create_node(char *line, stoml_data **node);
static int create_hash_code(const char *key, const int length);
static void insert_hashtable(stoml_data *data[], const int length, stoml_data *data_item);
static void trim(char *string);

int stoml_read(stoml_data *data[], const int length, FILE *stream) {

	char c = '\0';

	bool key_line = false;
	bool comment_line = false;
	
	char key_line_data[100];
	memset(key_line_data, 0, sizeof(key_line_data));
	short key_line_data_index = 0;

	stoml_data *node = NULL;

	c = getc(stream);
	
	while (c != EOF) {

		if (c == '#') {
			comment_line = true;

		} else if (c == '\n') {
			if (key_line) {
				key_line_data[key_line_data_index] = '\0';
				create_node(key_line_data, &node);

				if (node != NULL)
					insert_hashtable(data, length, node);
			}

			comment_line = false;
			key_line = false;

			memset(key_line_data, 0, sizeof(key_line_data));
			key_line_data_index = 0;

		} else if (!comment_line) {
			key_line = true;
		}
		
		if (key_line) {
			key_line_data[key_line_data_index] = c;
			if (key_line_data_index < MAX_KEYLINE_LENGTH)
				key_line_data_index++;
		} 

		c = getc(stream);
	}

	return STOML_SUCCESS;
}


stoml_data *search(stoml_data *data[], const int length, const char *key) {

	int hashtable_index = create_hash_code(key, length);
	
	while (data[hashtable_index] != NULL) {
		if (strncmp(key, &(*(data[hashtable_index])->key), MAX_KEY_LENGTH) == 0) 
			return data[hashtable_index];
		hashtable_index++;
		hashtable_index %= length;
	}
		
	return NULL;
}


static void create_node(char *line, stoml_data **node) {
	char *key = NULL;
	char *value = NULL;

	key = strtok(line, "=");
	value = strtok(NULL, "=");
	trim(key);
	trim(value);
	
	*node = (stoml_data *)  malloc(sizeof(stoml_data));
	if (*node != NULL) {
		strncpy((*node)->key, key, MAX_KEY_LENGTH - NULL_TERM_CHAR);
		strncpy((*node)->value, value, MAX_KEY_LENGTH - NULL_TERM_CHAR);
	}
	
}



/*
	key - stoml_data item to be used to create the hash key
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
