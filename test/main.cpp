#include "src/acutest.h"

extern void test_asdf_c_basic(void);

TEST_LIST = {
   { "c_basic", test_asdf_c_basic },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};