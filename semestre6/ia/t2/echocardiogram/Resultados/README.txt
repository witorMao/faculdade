Em relação ao pré-processamento ou não dos dados houveram diferenças de aproximadamento +-2% em relação aos resultados da classificação.

Comparando as árvores com e sem poda, quando pré-processamos os dados:

- Com: 

* 95.95% de acertos,  4.05% de erros;

* Sumário
  
  Correctly Classified Instances          71               95.9459 %
  Incorrectly Classified Instances         3                4.0541 %
  Kappa statistic                          0.9044
  Mean absolute error                      0.0282
  Root mean squared error                  0.1493
  Relative absolute error                 12.3745 %
  Root relative squared error             44.9938 %
  Total Number of Instances               74     
  Ignored Class Unknown Instances                 58  

* Confusion Matrix

  a  b  c  d   <-- classified as
 50  0  0  0 |  a = 0
  0  0  0  0 |  b = ?
  3  0 21  0 |  c = 1
  0  0  0  0 |  d = 2

- Sem: 

* 95.95% de acertos,  4.05% de erros;

* Sumário

  Correctly Classified Instances          71               95.9459 %
  Incorrectly Classified Instances         3                4.0541 %
  Kappa statistic                          0.9044
  Mean absolute error                      0.0282
  Root mean squared error                  0.1493
  Relative absolute error                 12.3745 %
  Root relative squared error             44.9938 %
  Total Number of Instances               74     
  Ignored Class Unknown Instances                 58 

* Confusion Matrix

  a  b  c  d   <-- classified as
 50  0  0  0 |  a = 0
  0  0  0  0 |  b = ?
  3  0 21  0 |  c = 1
  0  0  0  0 |  d = 2

Comparando as árvores com e sem poda, quando NÃO pré-processamos os dados:

- Com: 

* 97.3% de acertos, 2.7% de erros;

* Summary

  Correctly Classified Instances          72               97.2973 %
  Incorrectly Classified Instances         2                2.7027 %
  Kappa statistic                          0.937 
  Mean absolute error                      0.0217
  Root mean squared error                  0.1002
  Relative absolute error                  9.5141 %
  Root relative squared error             30.2116 %
  Total Number of Instances               74     
  Ignored Class Unknown Instances                 58 

* Confusion Matrix

    a  b  c  d   <-- classified as
 50  0  0  0 |  a = 0
  0  0  0  0 |  b = ?
  2  0 22  0 |  c = 1
  0  0  0  0 |  d = 2

- Sem:

* 97.3% de acertos, 2.7% de erros;

* Summary

  Correctly Classified Instances          72               97.2973 %
  Incorrectly Classified Instances         2                2.7027 %
  Kappa statistic                          0.937 
  Mean absolute error                      0.0217
  Root mean squared error                  0.1002
  Relative absolute error                  9.5141 %
  Root relative squared error             30.2116 %
  Total Number of Instances               74     
  Ignored Class Unknown Instances                 58 

* Confusion Matrix

    a  b  c  d   <-- classified as
 50  0  0  0 |  a = 0
  0  0  0  0 |  b = ?
  2  0 22  0 |  c = 1
  0  0  0  0 |  d = 2