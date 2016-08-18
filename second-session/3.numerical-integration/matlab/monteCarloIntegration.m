function [ y ] = monteCarloIntegration(fun, x_1, x_2, n)
    % rescale points using formula (oldValue - OldMin) * NewRange / OldRange + NewMin
    x = rand(n, 1) * (x_2 - x_1) + x_1;
    
    sum = 0;
    for i = 1:n
        sum = sum + fun(x(i));
    end
    
    y = (x_2 - x_1) * (sum / n);
end