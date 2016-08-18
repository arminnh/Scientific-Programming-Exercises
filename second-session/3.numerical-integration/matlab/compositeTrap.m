function [ y ] = compositeTrap(fun, a, b, n)
    y = 0;
    points = linspace(a, b, n);
    for i = 1:n-1
        y = y + trap(points(i), points(i+1), fun);
    end
end

function [ y ] = trap(x_1, x_2, fun)
    y = (x_2 - x_1)*(fun(x_1) + fun(x_2))/2;
end
