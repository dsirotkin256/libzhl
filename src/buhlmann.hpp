#pragma once
/*

(A. A. Bühlmann, 1983, p. 14)

P_i(t_N) = P_i(t_0)  + [P_i.in- P_i(t_0)] x [1 - e^(-k x t_N)] or [1 - e^(-0.69315 x t_N/2t)].

- P_i(t_N) is the pressure of the inert gas in the tissue at the end of the exposure,
- P_i(t_0) is the pressure of the inert gas in the tissue at the beginning of the exposure,
- P_i.in is the pressure of the inert gas in inspiration,
- e is the base of natural logarithms, 2.71828 ... ;
- k is the natural logarithm of 2, 0.69315, divided by the half-value time.
*/