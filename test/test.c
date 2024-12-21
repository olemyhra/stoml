#include <stdio.h>
#include <criterion/criterion.h>
#include "../stoml.h"
#include <strings.h>

#define FAIL 0
#define PASS 1

/* Criterion framework reports */
Test (FrameWorkVerify, Test1) {
	cr_assert(PASS, "Test1");
}


/* Read a normal configuration file and check if the data is in the table */
Test (NormalRead, Test1) {

	int length = 10;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testD.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value++;
	}

	if (return_value == 0) {
		node = stoml_search(data, length, "network_name");
	} else {
		return_value++;
	}
	
	if (node != NULL) {
		return_value = strcmp(get_value(node), "oslo");
	} else {
		return_value++;
	}

	cr_assert(return_value  == 0, "Return value not null!");

}


/* stoml_read: NULL pointer for stoml_data input parameter */
Test (InputParameters, Test1) {
	const int length = 5;
	stoml_data **data = NULL;
	int return_value = 0;

	FILE *fp = fopen("testD.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	}
	
	cr_assert(return_value == 1, "Null pointer");
}


/* stoml_read: Length of stoml_data pointer array is zero */
Test (InputParameters, Test2) {
	const int length = 5;
	stoml_data *data[length];
	int return_value = 0;

	FILE *fp = fopen("testD.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, 0, fp);

	}
	
	cr_assert(return_value == 1, "Test2");

}


/* stoml_read: Input data with only comments */
Test (InputData, Test1) {

	int length = 10;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testB.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value += 10;
	}

	cr_assert(return_value > 0 && return_value < 10, "Only comments");
}


/* stoml_read: Input data contains only normal text */
Test (InputData, Test2) {

	int length = 10;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testC.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value += 10;
	}

	cr_assert(return_value > 0 && return_value < 10, "Only text");
}


/* stoml_read: Input data is one key line with comment on the same line */
Test (InputData, Test4) {
	
	int length = 10;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testE.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value++;
	}

	if (return_value == 0) {
		node = stoml_search(data, length, "server_name");
	} else {
		return_value++;
	}
	
	if (node != NULL) {
		return_value = strcmp(get_value(node), "localhost");
	} else {
		return_value++;
	}

	cr_assert(return_value  == 0, "Key and comment on the same line");
}


/* stoml_read: Read a large amount of data */
Test (InputData, Test5) {

	int length = 11000;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testF.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value++;
	}

	if (return_value == 0) {
		node = stoml_search(data, length, "key8341");
	} else {
		return_value++;
	}
	
	if (node != NULL) {
		return_value = strcmp(get_value(node), "value8341");
	} else {
		return_value++;
	}

	for (int i=0;i<length;i++)
		free(data[i]);

	cr_assert(return_value  == 0, "Large data input");
}


/* stoml_read: Data larger than length of stoml_data array */
/* data array is 5000 while we are trying to find key 8341 */
Test (InputData, Test6) {

	int length = 5000;
	stoml_data *data[length];
	int return_value = 0;
	FILE *fp = NULL;
	stoml_data *node = NULL;

	memset(data, 0, sizeof(stoml_data *) * length);	

	fp = fopen("testF.toml", "r");

	if (fp != NULL) {
		return_value = stoml_read(data, length, fp);
	} else {
		return_value++;
	}

	if (return_value == 0) {
		node = stoml_search(data, length, "key8341");
	} else {
		return_value++;
	}
	
	if (node != NULL) {
		return_value = strcmp(get_value(node), "value8341");
	} else {
		return_value++;
	}

	cr_assert(return_value  == 1, "Data larger than array");
}

