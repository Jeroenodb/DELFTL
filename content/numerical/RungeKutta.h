/**
 * Author: Leon van der Waal
 * Date: 2023-10-10
 * Description: Approximates the state of the differential equation $\frac{\mathrm{d}x}{\mathrm{d}t} = df(t,x)$ at time $t+\varepsilon$, with error margin $O(\varepsilon^4)$.
 */
#pragma once

template<typename T>
T rk4(double t, T x, double dt, T df(double,T)){
    T k1 = dt*df(t,x), k2 = dt*df(t+dt/2, x+k1/2), 
      k3 = dt*df(t+dt/2, x+k2/2), k4 = dt*df(t+dt, x+k3);
    return x + k1/6 + k2/3 + k3/3 + k4/6;
}
