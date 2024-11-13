#include "stoml.h"

static FILE *stoml_file = NULL;
static int create_hash_code(const char *key);
static void  insert_tag_hashtable(stoml_data *data[], const int length, stoml_data *data_item);

int stoml_open_file(const char *file_name) 
	{
	stoml_file = fopen(file_name, "r");
	if(stoml_file != NULL) {
		return STOML_SUCCESS;
	} else {
		return STOML_FAILURE;
	}
} 


int stoml_read(stoml_data *data[], const int length, FILE *stream)
{

	bool comment_line = false;
	bool key_line = false;
	
	char c = '\0';

	int return_value = 0;

	c = getc(stream);
	
	while (c != EOF)
	{
		switch(c) {
			
			case '#':
				comment_line = true;
				printf("CL\n");
				break;
			case '\n':
				comment_line = false;
				key_line = false;
				printf("NL");
				break;			
				
			default:
				key_line = true;
				break;	
		}
		
			
		if (comment_line)
			return_value = 0;

		if (key_line)
			return_value = 0;

		printf("%c (0x%X)\n", c, c);
		c = getc(stream);
	}

	stoml_data new_data;

	strcpy (new_data.key,  "servername");
	new_data.value_type = 1;
	strcpy(new_data.str_value, "epks.srvr");
	new_data.int_value = 0;

	stoml_data *hash_table[10];
	memset(hash_table, 0, sizeof(stoml_data *) * 10);
	insert_tag_hashtable(hash_table, 10, &new_data);
	
	if (return_value > 0)
		printf("Hurra!\n");

	return 0;
}




int stoml_close()
{
 	return fclose(stoml_file);
}


/*
	key - stoml_data item to be used to create the hash key
*/
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


/*
	data - pointer to hashtable
	length - length of hashtable
	data_item - pointer to item of stoml_data
*/
static void insert_tag_hashtable(stoml_data *data[], const int length,  stoml_data *data_item)
{
	int hashtable_index = create_hash_code(data_item->key);
	
	while (data[hashtable_index] != NULL && *(data[hashtable_index]->key) != '\0') {
		hashtable_index++;

		hashtable_index %= length;
	}

	data[hashtable_index] = data_item;
}
