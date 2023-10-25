#include "s21_math.h"

#include <float.h>
#include <stdio.h>

s21_bool s21_ldeq(long double a, long double b) {
    return (a < b + s21_EPS_8 && a > b - s21_EPS_8);
}

static long double s21_atan_custom_pos_neg(long double magic, long double res,
                                           int mod, int *sp, long double x) {
    if (!mod && !s21_ldeq(res, 0.0) && !(*sp)) {
        res = magic - res;
    }

    if (*sp) {
        if (s21_fabs(x) > 0) {
            res = s21_M_PI_2;
        } else {
            res = -1.0L * s21_M_PI_2;
        }
    }

    return res;
}

long double s21_atan_cust(double x) {
    long double res = 0.0;

    const long double one_atan = 0.7853981633974480L;

    int modulo_x = (s21_fabs(x) < 1.0);

    long double magic = (s21_M_PI * s21_fabs(x)) / (2.0 * x);

    int flag = 0;

    if (!is_fin(x) && !is_nan(x) && s21_ldeq(x, 0.0)) {
        flag = 1;
    }

    int special = flag;

    if (!is_fin(x) && s21_fabs(x) > 0) {
        return s21_M_PI_2;
    }

    if (s21_ldeq(x, 1.0)) res = one_atan;
    if (s21_ldeq(x, -1.0)) res = -one_atan;

    if (!s21_ldeq(x, 0.0) && !special && !s21_ldeq(s21_fabs(res), one_atan)) {
        for (int i = 0; i < 100000; i++) {
            if (modulo_x) {
                res += (s21_pow(-1.0, i) * s21_pow(x, 1 + 2 * i)) / (1 + 2 * i);
            } else {
                res +=
                    (s21_pow(-1.0, i) * s21_pow(x, (-1 - 2 * i))) / (1 + 2 * i);
            }
        }
    }

    return (is_nan(x))
               ? s21_NAN
               : s21_atan_custom_pos_neg(magic, res, modulo_x, &special, x);
}

/**
 * @brief Computes the factorial of a non-negative integer n.
 * @param n Non-negative integer input.
 * @return Factorial of n.
 */
long double s21_fact(long double n) {
    long double res = 1;
    for (int exp = 1; exp <= n; ++exp) {
        res *= exp;
    }
    return res;
}

/**
 * @brief Computes the rising factorial of x, denoted as x(x+1)(x+2)...(x+n-1).
 * @param x Input value.
 * @param n Number of terms in the rising factorial.
 * @return Rising factorial of x.
 */
long double s21_risingFact(long double x, int n) {
    long double res = 1;
    for (int k = 0; k <= n - 1; ++k) {
        res *= x + k;
    }
    return res;
}

int s21_abs(int x) {
    long long _x = x < 0 ? (long long)-x : (long long)x;
    if (_x > __INT32_MAX__) {
        _x = __INT32_MAX__;
    }
    return (int)_x;
}

long double s21_acos(double x) {
    const long double zero_acos = 1.5707963267948966;
    long double res = 0.0;

    if (s21_ldeq(x, 0.0)) return zero_acos;

    s21_bool mod = (s21_fabs(x) > 1.0);
    s21_bool sign = (x > 0.0);

    /* These inputs DO NOT raise errno (unlike |x| > 1.0) */
    s21_bool invalid = ((is_nan(x) || !is_fin(x)) && !s21_ldeq(x, 0.0));

    if (!sign && !invalid && !s21_ldeq(x, 0.0)) {
        return (s21_M_PI - s21_acos(x * -1.0));
    }

    if (!invalid) {
        mod = (s21_fabs(x) > 1.0);
        if (mod) {
            errno = EDOM;
        } else if (s21_ldeq(x, 1.0)) {
            res = 0.0;
        } else if (s21_ldeq(x, -1.0)) {
            res = s21_M_PI;
        } else if (s21_fabs(x) > 0.0) {
            if (s21_ldeq(x, 0.0))
                res = zero_acos;
            else
                res += s21_atan_cust(s21_sqrt(1 - x * x) / x);
        }
    }

    return (mod || invalid) ? s21_NAN : res;
}

long double s21_asin(double x) {
    long double res = s21_NAN;
    if (x > 1 || x < -1) return res;
    if (x == 1 || x == -1) res = s21_PI / (2 * x);
    if (x > -1 && x < 1) res = s21_PI / 2 - s21_acos(x);
    return res;
}

long double s21_atan(double x) {
    long double res = 0;
    if (x == s21_INF) return s21_PI / 2;
    if (x == -s21_INF) return -s21_PI / 2;
    if (x != x) return x;
    if (x == 1) return 0.785398163;
    if (x == -1) return -0.785398163;
    int is_in_range = (x > -1 && x < 1);
    res = is_in_range ? x : 1.0 / x;
    for (int i = 1; i < 7000; i++) {
        double a = s21_pow(-1, i);
        double b = s21_pow(x, (1 + 2 * i) * (is_in_range ? 1 : -1));
        double c = 1 + 2 * i;
        res += a * b / c;
    }
    if (!is_in_range) res = (s21_PI * s21_fabs(x) / (2 * x)) - res;
    return res;
}

long double s21_ceil(double x) {
    if (is_nan(x) || is_inf(x)) return x;
    int int_part = (int)x;
    int_part += (x > 0 && (x - int_part));
    long double res = int_part;
    if (res == 0 && x < 0) res = -res;
    return res;
}

long double s21_cos(double x) {
    if (is_nan(x) || !is_fin(x)) return s21_NAN;

    int sign = 1;
    x = s21_fmod(x, 2 * s21_M_PI);

    if (x > (s21_M_PI / 2.0) && x <= s21_M_PI) {
        x = s21_M_PI - x;
        sign = -sign;
    } else if (x > s21_M_PI && x <= s21_M_PI * 3.0 / 2.0) {
        x -= s21_M_PI;
        sign = -sign;
    } else if (x > (s21_M_PI * 3.0) / 2.0 && x <= 2.0 * s21_M_PI) {
        x = 2 * s21_M_PI - x;
    }

    long double sum = 1.0;
    long double tailor = 1.0;

    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (-tailor * x * x) / ((2.0 * p - 1) * (2.0 * p));
        sum += tailor;
    }
    return sum * sign;
}

long double s21_exp(double x) {
    if (x == s21_NAN) return s21_NAN;
    if (x == -s21_INF || x < -14) return 0;
    if (x == s21_INF) return s21_INF;

    long double arg = (long double)x;
    long double sum = 1.0;
    long double tailor = 1.0;

    for (int p = 1; s21_fabs(tailor / sum) > 1e-100; p++) {
        tailor = (tailor * arg) / p;
        sum += tailor;
    }
    return sum;
}

long double s21_fabs(double x) {
    return x < 0.0 ? (long double)-x : (long double)x;
}

long double s21_floor(double x) {
    if (x >= LLONG_MAX || x <= LLONG_MIN || x != x) {
        return x;
    }
    long long n = (long long)x;
    double d = (double)n;
    if (d == x || x >= 0)
        return d;
    else
        return d - 1;
}

long double s21_fmod(double x, double y) {
    if (is_nan(x) || is_nan(y) || is_inf(x) || s21_fabs(y) < s21_EPS ||
        (is_inf(x) && is_inf(y)))
        return s21_NAN;
    if (s21_fabs(x) < s21_EPS) return 0;
    if (is_inf(y)) return x;

    long double lx = x;
    long double ly = y;
    long long div = x / y;
    return lx - div * ly;
}

long double s21_log(double x) {
    if (x == s21_INF) return x;
    if (x == 0) return -s21_INF;
    if (x < 0) return s21_NAN;
    long double result = 0, compare = 0;
    int e_repeat = 0;
    for (; x >= s21_EXP; e_repeat++) x /= s21_EXP;
    for (int i = 0; i < 100; i++) {
        compare = result;
        result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
    result += e_repeat;
    return result;
}

long double s21_fast_pow(long double base, long long int exp) {
    long double res;
    if (exp >= 0) {
        res = 1;
        while (exp) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
    } else {
        res = 1 / s21_fast_pow(base, -exp);
    }
    return res;
}

long double s21_pow(double base, double exp) {
    long double res;

    int b_n = is_nan(base);
    int b_f = is_fin(base);
    int e_n = is_nan(exp);
    int e_f = is_fin(exp);
    int e_i = s21_fabs(exp - s21_floor(exp)) <= s21_EPS;

    if (b_f && !b_n && base > 0 && base <= s21_EPS && e_i && ((int)exp) < 0 &&
        ((int)exp) % 2) {
        return s21_INF;
    }

    if (b_f && !b_n && base > 0 && base <= s21_EPS && e_i && ((int)exp) < 0 &&
        ((int)exp) % 2) {
        return -s21_INF;
    }

    if (b_f && !b_n && s21_fabs(base) < s21_EPS && e_f &&
        ((e_i && !(((int)exp) % 2)) || !e_i)) {
        return s21_INF;
    }

    if (b_f && !b_n && s21_fabs(base) < s21_EPS && !e_n && !e_f && exp < 0) {
        return s21_INF;
    }

    if (b_f && !b_n && base > 0 && base <= s21_EPS && e_i && ((int)exp) % 2) {
        return +0;
    }

    if (b_f && !b_n && base < 0 && base >= -s21_EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    if (b_f && !b_n && base < 0 && base >= -s21_EPS && e_i && ((int)exp) % 2) {
        return -0;
    }

    if (b_f && !b_n && s21_fabs(base) < s21_EPS &&
        ((!e_i && s21_fabs(exp) > s21_EPS) || (e_i && !(((int)exp) % 2)))) {
        return +0;
    }

    if (b_f && !b_n && s21_fabs(base + 1) < s21_EPS && !e_f && !e_n) {
        return 1;
    }

    if (b_f && !b_n && s21_fabs(base - 1) < s21_EPS) {
        return 1;
    }

    if (s21_fabs(exp) < s21_EPS) {
        return 1;
    }

    if (b_f && base < -s21_EPS && e_f && !e_i) {
        return s21_NAN;
    }

    if (s21_fabs(base) - 1 < s21_EPS && !e_n && !e_f && exp < 0) {
        return s21_INF;
    }

    if (s21_fabs(base) - 1 > s21_EPS && !e_n && !e_f && exp < 0) {
        return +0;
    }

    if (s21_fabs(base) - 1 < s21_EPS && !e_n && !e_f && exp > 0) {
        return +0;
    }

    if (s21_fabs(base) - 1 > s21_EPS && !e_n && !e_f && exp > 0) {
        return s21_INF;
    }

    if (!b_n && !b_f && base < 0 && e_i && exp < 0 && ((int)exp) % 2) {
        return -0;
    }

    if (!b_n && !b_f && base < 0 &&
        ((!e_i && exp < 0) || (e_i && exp < 0 && !(((int)exp) % 2)))) {
        return +0;
    }

    if (!b_n && !b_f && base < 0 && (e_i && exp > 0 && ((int)exp) & 1)) {
        return -s21_INF;
    }

    if (!b_n && !b_f && base < 0 &&
        ((!e_i && exp > 0) || (e_i && exp > 0 && !(((int)exp) % 2)))) {
        return +s21_INF;
    }

    if (!b_n && !b_f && base > 0 && exp < -s21_EPS) {
        return +0;
    }

    if (!b_n && !b_f && base > 0 && exp > s21_EPS) {
        return +s21_INF;
    }

    if (b_n || e_n) {
        return s21_NAN;
    }

    if (exp > s21_EPS) {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = s21_exp(exp * s21_log(base));
        }
    } else {
        if (e_i) {
            res = s21_fast_pow(base, exp);
        } else {
            res = (long double)1 / s21_exp(-exp * s21_log(base));
        }
    }

    return res;
}

long double s21_sin(double x) {
    long double res = 0, step, exp = 0;
    if (x == s21_NAN || x == -s21_INF || x == s21_INF) {
        res = s21_NAN;
    } else {
        if (x == s21_PI) {
            res = 1e-50;
        } else {
            if (x == -s21_PI) {
                res = -1e-50;
            } else {
                if (x != 0) {
                    while (x < -2 * s21_PI || 2 * s21_PI < x) {
                        if (x > 2 * s21_PI)
                            x -= 2 * s21_PI;
                        else
                            x += 2 * s21_PI;
                    }
                    do {
                        step = s21_pow(-1, exp) * s21_pow(x, 2 * exp + 1) /
                               s21_fact(2 * exp + 1);
                        res += step;
                        ++exp;
                    } while (step > s21_EPS || step < -s21_EPS);
                }
            }
        }
    }
    return res;
}

static long double handle_special_cases(double n, long double root) {
    return is_nan(n) ? s21_NAN : is_fin(n) ? root : s21_INF;
}

long double s21_sqrt(double n) {
    long double x = n;
    long double root = 0.0;

    if (n > s21_EPS && is_norm(x)) {
        while (1) {
            root = 0.5 * (x + (n / x));

            if (s21_fabs(root - x) < 1e-12) break;

            x = root;
        }
    } else {
        errno = EDOM;
    }

    if (n < s21_EPS && n > -s21_EPS) return 0.0;

    return (n > s21_EPS) ? handle_special_cases(n, root) : s21_NAN;
}

long double s21_tan(double x) {
    if (is_nan(x) || !is_fin(x)) return s21_NAN;
    return s21_sin(x) / s21_cos(x);
}
