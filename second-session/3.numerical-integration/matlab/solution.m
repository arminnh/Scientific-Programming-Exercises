format shortG
area = 68/35

trapeziumN = getCompositeTrapeziumN(@f, -1, 1, 0.1)
compositeTrapAreaLongFormula  = compositeTrap(@(x) f(x), -1, 1, trapeziumN)
compositeTrapAreaShortFormula = eval(compositeTrap2(@(x) f(x), -1, 1, trapeziumN))

trapeziumResultsAndDiff = [compositeTrapAreaLongFormula  abs(area - compositeTrapAreaLongFormula) 
                           compositeTrapAreaShortFormula abs(area - compositeTrapAreaShortFormula)]
                
results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_long_formu = [];
results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_short_form = [];

for n = 19:22
    compositeTrapAreaLongFormula  = compositeTrap(@(x) f(x), -1, 1, n);
    compositeTrapAreaShortFormula = compositeTrap2(@(x) f(x), -1, 1, n);
    
    results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_long_formu  = [ results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_long_formu
        compositeTrapAreaLongFormula abs(area - compositeTrapAreaLongFormula) ];
        
    results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_short_form = [ results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_short_form 
        compositeTrapAreaShortFormula abs(area - compositeTrapAreaShortFormula) ];
end

results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_long_formu
results_and_diff_for_n_19_to_22_wantBrunoHeeftAnders_short_form

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

gaussLegendreResultsN1To7 = [];
for n = 1:7
    gaussLegendreResultsN1To7 = [gaussLegendreResultsN1To7 
        gaussLegendre(@(x) f(x), -1, 1, n)];
end
gaussLegendreResultsN1To7

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

monteCarloResults2DVersion = [];

y_1 = fminbnd(matlabFunction(f(x)), -1, 1);
y_2 = f(fminbnd(matlabFunction(-1 * f(x)), -1, 1));
monteCarloResults3DVersion = [];

for n = [200 500 1000 2000 3500 5000 6500 8000 10000]
    monteCarloArea = monteCarloIntegration(@(x) f(x), -1, 1, n);
    monteCarloResults2DVersion = [monteCarloResults2DVersion
                         n monteCarloArea abs(area - monteCarloArea)];
                     
    monteCarloArea = monteCarloIntegration2(@(x) f(x), -1, 1, y_1, y_2, n);
    monteCarloResults3DVersion = [monteCarloResults3DVersion
                         n monteCarloArea abs(area - monteCarloArea)];
end
monteCarloResults2DVersion
monteCarloResults3DVersion