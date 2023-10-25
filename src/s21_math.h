#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_PI 3.14159265358979323846264338327950288

#define s21_true 1
#define s21_false 0
#define s21_bool int

#define s21_EPS 1e-6
#define s21_EPS_8 1e-6
#define s21_EXP 2.7182818284590452353602874713526624
#define s21_M_PI 3.14159265358979323846264338327950288
#define s21_M_PI_2 1.57079632679489661923132169163975144
#define s21_LN_2 0.693147180559945309417232

#define TWO52 0x1.0p52 /* 2^52 */

#define s21_INF (__builtin_inff())
#define s21_NAN (__builtin_nanf(""))
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)
#define is_norm(x) __builtin_isnormal(x)

/**
 * @brief Returns the absolute value of an integer.
 * @param x Integer input.
 * @return Absolute value of x.
 */
int s21_abs(int x);

/**
 * @brief Returns the arccosine of x.
 * @param x Input value.
 * @return Arccosine of x in radians.
 */
long double s21_acos(double x);

/**
 * @brief Returns the arcsine of x.
 * @param x Input value.
 * @return Arcsine of x in radians.
 */
long double s21_asin(double x);

/**
 * @brief Returns the arctangent of x.
 * @param x Input value.
 * @return Arctangent of x in radians.
 */
long double s21_atan(double x);

/**
 * @brief Rounds x to the smallest integer not less than x.
 * @param x Input value.
 * @return The smallest integer not less than x.
 */
long double s21_ceil(double x);

/**
 * @brief Returns the cosine of x.
 * @param x Input value.
 * @return Cosine of x.
 */
long double s21_cos(double x);

/**
 * @brief Returns e raised to the power x.
 * @param x Input value.
 * @return e^x (exponential function).
 */
long double s21_exp(double x);

/**
 * @brief Returns the absolute value of x.
 * @param x Input value.
 * @return Absolute value of x.
 */
long double s21_fabs(double x);

/**
 * @brief Rounds x to the largest integer not greater than x.
 * @param x Input value.
 * @return The largest integer not greater than x.
 */
long double s21_floor(double x);

/**
 * @brief Returns the remainder of x divided by y.
 * @param x Dividend.
 * @param y Divisor.
 * @return Remainder of x divided by y.
 */
long double s21_fmod(double x, double y);

/**
 * @brief Returns the natural logarithm of x.
 * @param x Input value.
 * @return Natural logarithm of x.
 */
long double s21_log(double x);

/**
 * @brief Returns base raised to the power exp.
 * @param base Base value.
 * @param exp Exponent value.
 * @return base^exp (base raised to the power exp).
 */
long double s21_pow(double base, double exp);

/**
 * @brief Returns the sine of x.
 * @param x Input value.
 * @return Sine of x.
 */
long double s21_sin(double x);

/**
 * @brief Returns the square root of n.
 * @param n Non-negative input value.
 * @return Square root of n.
 */
long double s21_sqrt(double n);

/**
 * @brief Returns the tangent of x.
 * @param x Input value.
 * @return Tangent of x.
 */
long double s21_tan(double x);

/**
 * @brief Compares two long double values for equality.
 * @param a First value.
 * @param b Second value.
 * @return True if a is approximately equal to b, false otherwise.
 */
s21_bool s21_ldeq(long double a, long double b);

/**
 * @brief Returns the arctangent of x with a custom implementation.
 * @param x Input value.
 * @return Arctangent of x in radians.
 */
long double s21_atan_cust(double x);

#endif  // SRC_S21_MATH_H_
