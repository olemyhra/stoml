#include "stoml.h"

static void create_node(char *line, stoml_data *node);
static int create_hash_code(const char *key);
static void insert_hashtable(stoml_data *data[], const int length, stoml_data *data_item);


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
				create_node(key_line_data, node);
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

		printf("%c", c);
		c = getc(stream);
	}

	return STOML_SUCCESS;
}


static void create_node(char *line, stoml_data *node) {


}



/*
	key - stoml_data item to be used to create the hash key
*/
static int create_hash_code(const char *key) {
	int index = 0;

	for (int i=0;i<MAX_KEY_LENGTH;i++) {
		if (key[i] == '\0')
			break;
		index += key[i];
	}

	return index % MAX_KEY_LENGTH;
}


/*
	data - pointer to hashtable
	length - length of hashtable
	data_item - pointer to item of stoml_data
*/
static void insert_hashtable(stoml_data *data[], const int length,  stoml_data *data_item) {
	int hashtable_index = create_hash_code(data_item->key);
	
	while (data[hashtable_index] != NULL && *(data[hashtable_index]->key) != '\0') {
		hashtable_index++;

		hashtable_index %= length;
	}

	data[hashtable_index] = data_item;
}
