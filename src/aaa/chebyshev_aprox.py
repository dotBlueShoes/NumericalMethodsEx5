import math

from newton_cotes import *


class Polymonial:
    coefs: list

    def __init__(self, coefs):
        self.coefs = coefs

    def value(self, x: float):
        ret = self.coefs[0]
        for i in range(1, len(self.coefs)):
            ret = self.coefs[i] + x * ret
        return ret


def chebyshev_polymonials(m: int):
    if m == 1:
        return [Polymonial([1])]
    elif m == 2:
        return [Polymonial([1, 0])]
    else:
        coefs = [[1], [1, 0]]
        ret = [Polymonial([1]), Polymonial([1, 0])]
        for i in range(2, m):
            newc = [a * 2 for a in coefs[i - 1]]
            newc += [0]
            for j in range(1, i):  # Not sure about range xd
                newc[j + 1] -= coefs[i - 2][j - 1]
            ret.append(Polymonial(newc))
            coefs.append(newc)
    return ret


# I hate everything about this
# def chebyshev_aproximation(x: float, a: float, b: float, fun, m: int, int_prec: float = 0.1):
#     x = (2 * x - a - b) / (b - a)
#     ret = 0
#     g = chebyshev_polymonials(m)
#     p = Polymonial([1, 2, 3])
#     p.value(2)
#     print(type(g), type(g[0]), type(g[3]))
#     wg = [lambda xx: 1 / np.sqrt(1 - (xx*0.999)**2) * gi.value(xx) for gi in g]
#     for k in range(0, m):
#         print("coasds", wg[k](1))
#         wfg = lambda xx: wg[k](xx) * fun.value(xx)
#         ck_1 = newton_cotes(a, b, wfg, int_prec)
#         if k == 0:
#             ck_2 = math.pi
#         else:
#             ck_2 = math.pi * 0.5
#         # ck_2 = newton_cotes(-1, 1, lambda xx: wg[k](xx) * g[k](xx), int_prec)
#         print(k, ck_1, ck_2, g[k].value(x))
#         ret += ck_1 / ck_2 * g[k].value(x)
#         print(k, ret)
#     return ret
def chebyshev_aprox(x: float, a: float, b: float, f, m: int, precision=1000):
    ret = 0
    # x = (2 * x - a - b) / (b - a)
    g_list = chebyshev_polymonials(m)
    for k in range(m):
        wfg = lambda val: 1 / math.sqrt(1.00000000001 - (val*val)) * f(val) * g_list[k].value(val)
        ck_1 = newton_cotes_single(-1, 1, wfg, precision)
        if k == 0:
            ck_2 = math.pi
        else:
            ck_2 = math.pi * 0.5

        ret += ck_1 / ck_2 * g_list[k].value(x)

    return ret


def chebyshev_aprox_series(a: float, b: float, N: int, f, m: int, precision=0.001):
    # Get points
    h = (b - a) / (N - 1)
    X = [((a + h * i) - a - b)/(b - a) for i in range(0, N)]

    # Get polymonials
    g_list = chebyshev_polymonials(m)

    # Get współczynniki
    c_list = []
    for k in range(m):
        wfg = lambda val: 1 / math.sqrt(1.0001 - (val*val)) * f(val) * g_list[k].value(val)
        ck_1 = newton_cotes(-1, 1, wfg, precision)
        if k == 0:
            ck_2 = math.pi
        else:
            ck_2 = math.pi * 0.5
        print(".", end="")
        c_list.append(ck_1 / ck_2)
    print("")

    # Scale back X
    # https://www.cce.pk.edu.pl/images/skrypty/Metody_numeryczne_2 (str 9)
    X = [0.5 * ((b - a) * x + (b + a)) for x in X]

    # Calculate values
    Y = []
    for x in X:
        y = 0
        for i in range(len(g_list)):
            y += c_list[i] * g_list[i].value(x)
        Y.append(y)

    # Calculate errors
    err_list = []
    for i in range(int(len(X) / 4), int(3 * len(X) / 4)):
        err_list. append(abs(f(X[i]) - Y[i]))

    avg_err = sum(err_list) / len(err_list)

    return X, Y, avg_err


if __name__ == "__main__":
    f = lambda x: 2 * x + 1
    print(chebyshev_aprox(1, -2, 5, f, 5))
