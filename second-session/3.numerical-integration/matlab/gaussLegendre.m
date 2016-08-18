% degree n -> n + 1 nodes and n+1 weights
function [ y ] = gaussLegendre(fun, a, b, n)
    syms z
    %zeroes = eval(roots(coeffs(int(diff(legendreP(n+1, z))), 'All')));
    zeroes = vpasolve(legendreP(n+1, z) == 0);

    syms y
    differentiatedLegendre(y) = diff(legendreP(n+1, y));
    
    y = 0;
    for i = 1:length(zeroes)
        w_i = 2 / ( (1-zeroes(i)^2) * (differentiatedLegendre(zeroes(i))^2) );
        f_i = fun( ((a+b)/2) + ((b-a)*zeroes(i)/2) );
        
        y = y + ((b-a)/2 * w_i) * f_i;
    end
end