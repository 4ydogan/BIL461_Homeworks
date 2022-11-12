Mustafa Aydoğan
191101002

Odevde bizden istenen istemcilerin sistem cagrilarini kullanarak haberlesmesidir.
Bu kapsamda client.c ve server.c dosyalari hazirlanmistir.

Kullanimi

1- server.c ve client.c dosyalarini compile edin. Ornek asagida verilmistir.
    (gcc client.c -o client -lpthread)
    (gcc server.c -o server -lpthread)

2- calistirilabilecek dosya olan server dosyasini calistirin. (./server)
3- bir istemci baslatin. (./client <id>)
    <id> sizin sistem icindeki kimliginiz olacaktir.

4- mesaj gondermek istediginiz istemci id'sini giriniz.
    (id integer olmak zorundadir)

5- gondermek istediginiz mesaji giriniz.

6- eger size bir mesaj gelirse input olarak ekrana basilacaktir.

7- gonderilen tum mesajlari serverda gorebilirsiniz.

Not: bazen gecikmeler olmaktadir. sebebini bulamadigim icin o sorunu cozemedim. yaptigim testlerde guzel bir sekilde calismaktadir.