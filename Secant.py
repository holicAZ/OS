from numpy import zeros, array, cos
import matplotlib.pyplot as plt

def f(x):
    return 3.0*x-cos(x)-1.0

n=7
xs = zeros(n)
x0 = -2.0
x1 = 3.0
error = zeros(n)
itl = range(0,7)
it = array(itl)

for i in range(n):
    x2 = x1 - f(x1)*((x1-x0)/(f(x1)-f(x0)))
    x0 = x1
    x1 = x2
    xs[i] = x2

for i in range(n-1):
    error[i + 1] = abs(((xs[i + 1] - xs[i]) / xs[i + 1])) * 100

print("%5s %8s %8s" % ('k','x','E'))
for k in range(n):
    print("%5d %9.4f %9.4f" % (k+1,xs[k],error[k]))

plt.plot(it,xs,'k--',label='x')
plt.plot(it,error,'bo-',label='E(%)')
plt.legend()
plt.show()