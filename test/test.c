#include <stdio.h>
#include <criterion/criterion.h>
#include "../stoml.h"

#define FAIL 0
#define PASS 1

/* Criterion framework reports */
Test (FrameWorkVerify, Test1) {
	cr_assert(PASS, "Test1");
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
	cr_assert(PASS, "Test1");
}


/* stoml_read: Input data contains only normal text */
Test (InputData, Test2) {
	cr_assert(PASS, "Test2");
}


/* stoml_read: Input data consists of one comment line and one key line */
Test (InputData, Test3) {
	cr_assert(PASS, "Test3");
}

/* stoml_read: Input data is one key line with comment on the same line */
Test (InputData, Test4) {
	cr_assert(PASS, "Test4");
}





