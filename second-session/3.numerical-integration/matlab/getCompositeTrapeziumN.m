function [ y ] = getCompositeTrapeziumN(fun, a, b, precision)
    syms x N
    secondDerivative(x)  = diff(fun(x), 2);
    
    maxXSecondDerivative = fminbnd(matlabFunction(-1 * secondDerivative), -1, 1);
    maxSecondDerivative  = max([secondDerivative(maxXSecondDerivative) secondDerivative(-1) secondDerivative(1)]);
    
    error = ((5 * (b - a)^3) / (12 * N^2)) * maxSecondDerivative;
    
    y = max(floor(solve(error < precision, N, 'Real', true)));
end