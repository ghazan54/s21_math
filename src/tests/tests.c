#include "tests.h"

int main(void) {
  int failed = 0;
  Suite* s21_string_test[] = {
      test_abs(),   test_asin(), test_acos(), test_atan(),
      test_ceil(),  test_cos(),  test_exp(),  test_fabs(),
      test_floor(), test_fmod(), test_log(),  test_pow(),
      test_sin(),   test_sqrt(), test_tan(),  NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner* sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  failed ? printf("\e[31m========= FAILED: %d =========\e[39m\n", failed)
         : printf("\e[32m========= FAILED: %d =========\e[39m\n", failed);

  return failed == 0 ? 0 : 1;
}
