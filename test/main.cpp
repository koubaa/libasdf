#include "src/acutest.h"

extern void test_asdf_c_open_fail(void);
extern void test_asdf_cxx_open_fail(void);

TEST_LIST = {
   { "c_open_fail", test_asdf_c_open_fail },
   { "cxx_open_fail", test_asdf_cxx_open_fail },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};