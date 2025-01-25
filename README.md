# stoml
Simple TOML library

This library is intended to provide the most basic functions to read a TOML file.
The library is based upon the TOML v1.0.0 specification.

Supported specifications:
- Comments
- Bare keys
- Basic strings

# How to build
The project contains the source files for the library, a test directory and a cmake file. In order to build the project
use have to have cmake and gcc installed. I have used CMake 3.31 and you will need the GNU C compiler (GCC). For the compiler I have used
GCC version 11.4.

 Here is the build steps required
1. Either fork or clone the stoml library github repository
2. Navigate to the folder where you have the source files.
3. Make a new directory called build
4. Navigate to the build directory
5. Run "cmake -S .. -B ."
6. This command should complete successfully.
7. From the build directory you then run "cmake --build ."
8. This will then build the library and the test executable

# Dependencies
- The library is using libc and linux-vdso. 
- The test executable is using the Criterion test framwork which needs to be availble in the compiler search path for the
  project to build successfully.

# How to use
 Below is an example of how to use the library. There are also several examples inside the test.c which
forms the code for the test executable.

```
#include <stdio.h>
#include <stoml.h>
#define DATA_LENGTH 10  /* Set the length of the hash table to store the toml elements */

int main(void) {
  stoml_data *keys[DATA_LENGTH];
  int return_value = 0;  /* Used to check the return value from the stoml functions */
  FILE *fp = NULL;
  stoml_data *key = NULL;

  memset(keys, 0, sizeof(stoml_data *) * DATA_LENGTH);

  fp = fopen("input_file.toml", "r");
  if (fp != NULL) 
    return_value = stoml_read(keys, DATA_LENGTH, fp);

    if (return_value != 0)
      exit(1);  /* Something went wrong in reading or during build of the keys data structure so we exit */

    key = stoml_search(keys, DATA_LENGTH, "key_name"); /* key_name to be replaced with a key in your file */

    if (key == NULL)
      exit(1) /* The key we searched for did not exist in the keys data structure */

    printf("Key: %s, value: %s\n", get_key(key), get_value(key));

    return 0;
}

```

# Automated testing
In the test folder there is test.c which contains some tests using the Criterion test framework.
These tests checks that the normal use cases and some boundary cases. I would recommend that
if you choose to modify the code of the library that you run these test cases or even add some more
to ensure the functionlaity of the library.

# Way forward
This is the first library that I have developed so my experience is very limited. I will greatly appreciate any feedback which
can enable me to learn and develop as a developer and also any feedback for improvements to the library.
