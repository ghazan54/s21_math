#include "tests.h"

START_TEST(pow_1) {
  double num = 456.789;
  double ex = 1.1;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  ck_assert_float_eq(our_res, orig_res);
  if ((fabsl(orig_res - our_res) <= 1e-6)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_2) {
  double num = INFINITY;
  double ex = 1.1;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isinf(our_res) && isinf(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_3) {
  double num = NAN;
  double ex = 1.1;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isnan(our_res) && isnan(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_4) {
  double num = NAN;
  double ex = NAN;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isnan(our_res) && isnan(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_5) {
  double num = 0.001;
  double ex = NAN;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isnan(our_res) && isnan(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_6) {
  double num = INFINITY;
  double ex = INFINITY;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isinf(our_res) && isinf(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_7) {
  double num = INFINITY;
  double ex = INFINITY;
  long double orig_res = pow(num, ex), our_res = s21_pow(num, ex);
  int suc = 0;
  if (isinf(our_res) && isinf(orig_res)) suc = 1;
  ck_assert_int_eq(1, suc);
}
END_TEST

START_TEST(pow_8) {
  long double base = -16.161435;
  long double exp = 9.;
  ck_assert_double_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
}
END_TEST

START_TEST(pow_9) {
  long double base = -10.1261;
  long double exp = -0.72;
  ck_assert_double_nan(s21_pow(base, exp));
  ck_assert_double_nan(pow(base, exp));
}
END_TEST

START_TEST(pow_10) {
  long double base = +0;
  long double exp = -0.33;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
  ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

START_TEST(pow_12) {
  long double base = -0;
  long double exp = -0.33;
  ck_assert_ldouble_infinite(s21_pow(base, exp));
  ck_assert_ldouble_infinite(pow(base, exp));
}
END_TEST

// START_TEST(pow_13)
// {
//     long double base = -0;
//     long double exp = s21_INF;
//     ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), s21_EPS);
// }
// END_TEST

// START_TEST(pow_14)
// {
//     long double base = +0;
//     long double exp = 123;
//     ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
// }
// END_TEST

// START_TEST(pow_15)
// {
//     long double base = -0;
//     long double exp = 123;
//     ck_assert_ldouble_eq_tol(s21_pow(base, exp), pow(base, exp), 1e-6);
// }
// END_TEST

Suite* test_pow(void) {
  Suite* s12;
  TCase* tc12;
  s12 = suite_create("s21_pow");
  tc12 = tcase_create("case_pow");

  tcase_add_test(tc12, pow_1);
  tcase_add_test(tc12, pow_2);
  tcase_add_test(tc12, pow_3);
  tcase_add_test(tc12, pow_4);
  tcase_add_test(tc12, pow_5);
  tcase_add_test(tc12, pow_6);
  tcase_add_test(tc12, pow_7);
  tcase_add_test(tc12, pow_8);
  tcase_add_test(tc12, pow_9);
  tcase_add_test(tc12, pow_10);
  tcase_add_test(tc12, pow_12);
  // tcase_add_test(tc12, pow_13);
  // tcase_add_test(tc12, pow_14);
  // tcase_add_test(tc12, pow_15);

  suite_add_tcase(s12, tc12);
  return s12;
}
