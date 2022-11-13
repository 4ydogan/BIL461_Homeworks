Mustafa Aydoğan
191101002

Odevde bizden istenen klasik Dining Philosophers problemini modellemektir. Ancak ufak bir fark vardır.

Klasik problemdeki HUNGRY-EATING-THINKING dongusu HUNGRY-BUTTERMILK-EATING-THINKING olacak sekilde program yazilmistir.
Problemde bir de surahi vardir. Surahideki ayran bitince philosopherlarin o turda yedigi porsiyon sayisi ekrana basilacaktir ve random sayida bardak ile surahi doldurulacaktir.

Philosopherlarin yeme ve dusunme sureleri 1 ile 5 saniye arasında random olacak sekilde ayarlanmistir.

Bu kapsamda dining_philosophers.c dosyalari hazirlanmistir.

Kullanimi:

1- dining_philosophers.c dosyasini compile edin. Ornek asagida verilmistir.
    (gcc dining_philosophers.c -o dining_philosophers -lpthread)

2- calistirilabilecek dosya olan dining_philosophers dosyasini calistirin. (./dining_philosophers)

3- philosopher sayisini integer olarak girin.

4- programdan cikmak icin Ctrl-C ye basabilirsiniz.

Not: Daha okunakli olmasi icin sleep() kullanilmistir. Program ciktilarini gorebilmek icin bir sure bekleyiniz.
