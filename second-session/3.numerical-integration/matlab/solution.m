format shortG
area = 68/35

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

trapeziumN = getCompositeTrapeziumN(@f, -1, 1, 0.1)
compositeTrapeziumArea = eval(compositeTrap2(@(x) f(x), -1, 1, trapeziumN));
trapeziumResultAndDifference = [compositeTrapeziumArea  abs(area - compositeTrapeziumArea)]
                
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

gaussLegendreResult = [gaussLegendre(@(x) f(x), -1, 1, 3)]

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

monteCarloResults = [];

for n = [200 500 1000 2000 3500 5000]
    monteCarloArea = monteCarloIntegration(@(x) f(x), -1, 1, n);
    monteCarloResults = [monteCarloResults
                         n monteCarloArea abs(area - monteCarloArea)];
end
monteCarloResults