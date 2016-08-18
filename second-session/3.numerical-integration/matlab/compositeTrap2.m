function [ y ] = compositeTrap2(fun, a, b, n)
    h = (b - a) / n;
    
    temp = 0;
    for i = 1:n-1
        temp = temp + fun(a + i*h);
    end
    
    y = (h / 2) * (fun(a) + 2 * temp + fun(b));
end