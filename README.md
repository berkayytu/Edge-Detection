# Edge-Detection
İmage Processing 1. Homework

Görüntü İşleme 1. Ödev Raporu
Bilgisayar Mühendisliği
Berkay Hamarat
160110611.Ödev amacı:
Girilen pgm uzantılı resimlerin sobel filtresi uygulanarak edge detection
işlemi yapılması. İşlem sonucunda x, y ve hem x hem y düzlemleri üzerinde 
yapılan işlemin görüntü olarak sonucunun alınması.
2.Yapılan işlemler:
Verilen pgm uzantılı resimlerin okunduktan sonra bir matrix içerisinde 
tutulur. Bu matris üzerinden resme sobel filtresi uygulanır, elde edilen sonuçlar 
min-max normalizasyonu işlemi ile 0-255 aralığındaki değerlere dönüştürelerek 
pgm formatına geri getirilir. Edge detection işlemi uygulanmış yeni resimler 
pgm uzantılı yeni dosyalar olarak oluşturulur.
3.Kullanılan fonksiyonlar ve işlevleri:
1. Main : Main fonksiyonda işlem uygulanacak doyanın adı alınır, 
Read_image_to_matrix fonsiyonuna gönderilir. Okunan dosyadan alınan 
verilere göre allocation işlemleri ile yeni matrixler oluşturulur. X, Y ve 
hem x hem y düzlemlerinde filtreleme için sırayla fonksiyonlar çağırılır.
2. Sobel_filter_x : Main fonksiyondan gelen matrixe padding işlemi yapılır 
sonrasında x düzlemi için sobel filtresi uygulanır, elde edilen sonuç 
Normalization fonksiyonuna gönderilir. Gelen pgm formatına uygun 
matrix doya olarak oluşturulur.
3. Sobel_filter_y : Sobel_filter_x fonskiyonu ile aynı işlemleri y düzlemi için 
uygular.
4. Sobel_filter_final : Sobel_filter_x ve Sobel_filter_y fonksiyonlarının 
sonucu ile resmin edge detection işlemi tamamlanmış halini oluşturur ve 
normalizasyon işleminden geçirerek pgm formatında dosyaya yazar.5. Normalization : Gelen matrixe min-max normalizasyonu işlemini uygular 
ve sonuç matrixini döndürür.
4.Ödevin Sonuçları:
4.1)
Lena.pgm:
_xlena.pgm:_ylena.pgm:
_finallena.pgm:4.2) 
Barbara.pgm:
_xbarbara.pgm:_ybarbara.pgm:
_finalbarbara.pgm:4.3) 
Totem.pgm:
_finaltotem.pgm:
4.4)
Pepper.pgm:_xpepper.pgm:
_finalpepper.pgm:
4.5)
baboon.pgm:_finalbaboon.pgm
