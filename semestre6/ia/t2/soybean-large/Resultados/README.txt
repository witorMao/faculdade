Em relação ao pré-processamento ou não dos dados houveram diferenças de aproximadamento +-2% em relação aos resultados da classificação.

Comparando as árvores com e sem poda, quando pré-processamos os dados:

- Com: 

* 89.25% de acertos,  10.75% de erros;

* Sumário
  Correctly Classified Instances         274               89.2508 %
  Incorrectly Classified Instances        33               10.7492 %
  Kappa statistic                          0.8823
  Mean absolute error                      0.0127
  Root mean squared error                  0.0973
  Relative absolute error                 13.2107 %
  Root relative squared error             44.3942 %
  Total Number of Instances              307      

* Confusion Matrix

  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s   <-- classified as
  9  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0 |  a = diaporthe-stem-canker
  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  b = charcoal-rot
  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  c = rhizoctonia-root-rot
  0  0  0 40  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  d = phytophthora-rot
  0  0  0  0 20  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  e = brown-stem-rot
  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0 |  f = powdery-mildew
  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0 |  g = downy-mildew
  0  0  0  0  0  0  0 37  0  0  0  0  2  0  1  0  0  0  0 |  h = brown-spot
  0  0  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0 |  i = bacterial-blight
  0  0  0  0  0  0  0  0  1  9  0  0  0  0  0  0  0  0  0 |  j = bacterial-pustule
  0  0  0  0  0  0  0  0  0  0  9  0  0  0  0  1  0  0  0 |  k = purple-seed-stain
  2  0  0  1  0  0  0  0  0  0  0 17  0  0  0  0  0  0  0 |  l = anthracnose
  0  0  0  0  0  0  0  1  0  0  0  0  9  0  0  0  0  0  0 |  m = phyllosticta-leaf-spot
  0  0  0  0  0  0  0  1  0  0  0  0  0 31  8  0  0  0  0 |  n = alternarialeaf-spot
  0  0  0  0  0  0  0  3  0  0  0  0  0 10 27  0  0  0  0 |  o = frog-eye-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0  0 |  p = diaporthe-pod-&-stem-blight
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0 |  q = cyst-nematode
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0 |  r = 2-4-d-injury
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  4 |  s = herbicide-injury


- Sem: 

* 91.21% de acertos,  8.8% de erros;

* Sumário

  Correctly Classified Instances         280               91.2052 %
  Incorrectly Classified Instances        27                8.7948 %
  Kappa statistic                          0.9037
  Mean absolute error                      0.0106
  Root mean squared error                  0.0915
  Relative absolute error                 11.0175 %
  Root relative squared error             41.7495 %
  Total Number of Instances              307     

* Confusion Matrix

  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s   <-- classified as
  9  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0 |  a = diaporthe-stem-canker
  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  b = charcoal-rot
  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  c = rhizoctonia-root-rot
  0  0  0 40  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  d = phytophthora-rot
  0  0  0  0 20  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  e = brown-stem-rot
  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0 |  f = powdery-mildew
  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0 |  g = downy-mildew
  0  0  0  0  0  0  0 37  0  0  0  0  2  0  1  0  0  0  0 |  h = brown-spot
  0  0  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0 |  i = bacterial-blight
  0  0  0  0  0  0  0  0  1  9  0  0  0  0  0  0  0  0  0 |  j = bacterial-pustule
  0  0  0  0  0  0  0  0  0  0  9  0  0  0  0  1  0  0  0 |  k = purple-seed-stain
  2  0  0  1  0  0  0  0  0  0  0 17  0  0  0  0  0  0  0 |  l = anthracnose
  0  0  0  0  0  0  0  1  0  0  0  0  9  0  0  0  0  0  0 |  m = phyllosticta-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0 31  9  0  0  0  0 |  n = alternarialeaf-spot
  0  0  0  0  0  0  0  3  0  0  0  0  0  4 33  0  0  0  0 |  o = frog-eye-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0  0 |  p = diaporthe-pod-&-stem-blight
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0 |  q = cyst-nematode
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0 |  r = 2-4-d-injury
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  4 |  s = herbicide-injury


Comparando as árvores com e sem poda, quando NÃO pré-processamos os dados:

- Com: 

* 84.96% de acertos, 15.31% de erros;

* Summary

  Correctly Classified Instances         260               84.6906 %
  Incorrectly Classified Instances        47               15.3094 %
  Kappa statistic                          0.832 
  Mean absolute error                      0.0185
  Root mean squared error                  0.1151
  Relative absolute error                 19.2219 %
  Root relative squared error             52.4814 %
  Total Number of Instances              307     

* Confusion Matrix

  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s   <-- classified as
 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  a = diaporthe-stem-canker
  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  b = charcoal-rot
  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  c = rhizoctonia-root-rot
  0  0  0 40  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  d = phytophthora-rot
  0  1  0  0 18  0  0  0  0  0  0  0  0  0  0  0  0  0  1 |  e = brown-stem-rot
  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0 |  f = powdery-mildew
  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0 |  g = downy-mildew
  0  0  0  0  0  0  0 37  0  0  0  0  2  0  1  0  0  0  0 |  h = brown-spot
  0  0  0  0  0  0  0  0  9  1  0  0  0  0  0  0  0  0  0 |  i = bacterial-blight
  0  0  0  0  0  0  0  0  1  9  0  0  0  0  0  0  0  0  0 |  j = bacterial-pustule
  0  0  0  0  0  0  0  1  1  0  7  0  0  0  0  1  0  0  0 |  k = purple-seed-stain
  0  0  0  2  1  0  0  0  0  0  1 16  0  0  0  0  0  0  0 |  l = anthracnose
  0  0  0  0  0  0  0  3  0  0  0  0  7  0  0  0  0  0  0 |  m = phyllosticta-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0 31  9  0  0  0  0 |  n = alternarialeaf-spot
  0  0  0  0  0  0  0  5  0  0  0  1  0 10 24  0  0  0  0 |  o = frog-eye-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0  0 |  p = diaporthe-pod-&-stem-blight
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0 |  q = cyst-nematode
  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0 |  r = 2-4-d-injury
  0  0  0  2  0  0  0  0  0  0  0  2  0  0  0  0  0  0  0 |  s = herbicide-injury


- Sem:

* 86.5% de acertos, 13.36% de erros;

* Summary

  Correctly Classified Instances         266               86.645  %
  Incorrectly Classified Instances        41               13.355  %
  Kappa statistic                          0.8535
  Mean absolute error                      0.0158
  Root mean squared error                  0.1099
  Relative absolute error                 16.3793 %
  Root relative squared error             50.1284 %
  Total Number of Instances              307   

* Confusion Matrix

  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s   <-- classified as
 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  a = diaporthe-stem-canker
  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  b = charcoal-rot
  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  c = rhizoctonia-root-rot
  0  0  0 40  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0 |  d = phytophthora-rot
  0  1  0  0 18  0  0  0  0  0  0  0  0  0  0  0  0  0  1 |  e = brown-stem-rot
  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0  0 |  f = powdery-mildew
  0  0  0  0  0  0 10  0  0  0  0  0  0  0  0  0  0  0  0 |  g = downy-mildew
  0  0  0  0  0  0  0 37  0  0  0  0  2  0  1  0  0  0  0 |  h = brown-spot
  0  0  0  0  0  0  0  0  9  1  0  0  0  0  0  0  0  0  0 |  i = bacterial-blight
  0  0  0  0  0  0  0  0  1  9  0  0  0  0  0  0  0  0  0 |  j = bacterial-pustule
  0  0  0  0  0  0  0  1  1  0  7  0  0  0  0  1  0  0  0 |  k = purple-seed-stain
  0  0  0  2  1  0  0  0  0  0  1 16  0  0  0  0  0  0  0 |  l = anthracnose
  0  0  0  0  0  0  0  3  0  0  0  0  7  0  0  0  0  0  0 |  m = phyllosticta-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0 30 10  0  0  0  0 |  n = alternarialeaf-spot
  0  0  0  0  0  0  0  5  0  0  0  1  0  3 31  0  0  0  0 |  o = frog-eye-leaf-spot
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0  0 |  p = diaporthe-pod-&-stem-blight
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0 |  q = cyst-nematode
  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0 |  r = 2-4-d-injury
  0  0  0  2  0  0  0  0  0  0  0  2  0  0  0  0  0  0  0 |  s = herbicide-injury
