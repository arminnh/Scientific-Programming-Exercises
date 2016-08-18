function [ y ] = monteCarloIntegration2(fun, x_1, x_2, y_1, y_2, n)
    % rescale points using formula (oldValue - OldMin) * NewRange / OldRange + NewMin
    x = rand(n, 1) * (x_2 - x_1) + x_1;
    y = rand(n, 1) * (y_2 - y_1) + y_1;
    
    p = 0;
    for i = 1:n
        if y(i) <= fun(x(i))
            p = p + 1;
        end
    end
    
    measureOfA = (y_2 - y_1) * (x_2 - x_1);
    y = measureOfA * (p / n);
end