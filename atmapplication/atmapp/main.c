#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//veriable
int islem,islem2,islem3;
int i;
int miktar;
long long int girilentc;
int girilensifre;
int bakiye[100];
long long int tc[100];
int sifre[100];
int kullanicisayisi = 0;
char guvenlikcevap[100][50];
int guvenliksoru[100];
char isim[100][50];
//fonksiyonlar
void giris();
void kayit();
void kullaniciIslemleri(int index);
void sifredegistirme();
void verileriyukle();
void dosyaGuncelle();

int main() {
    printf("  --BANK--\n");
    printf("-HOS GELDINIZ-\n");

    verileriyukle();

    do {
        printf("\n1-GIRIS:\n");
        printf("2-KAYIT:\n");
        printf("3-SIFRE SIFIRLAMA:\n");
        printf("4-CIKIS\n");
        scanf("%d", &islem2);

        switch (islem2) {
            case 1: giris(); break;
            case 2: kayit(); break;
            case 3: sifredegistirme(); break;
        }
    } while (islem2 != 4);

    return 0;
}
//giris
void giris() {
    printf("TC GIRIN: ");
    scanf("%lld", &girilentc);

    int bulundu = 0;
    for (i = 0; i < kullanicisayisi; i++) {
        if (tc[i] == girilentc) {
            bulundu = 1;
            int hak = 3;
            while (hak > 0) {
                printf("SIFRE GIRIN: ");
                scanf("%d", &girilensifre);
                if (sifre[i] == girilensifre) {
                    printf("GIRIS BASARILI!\n");
                    kullaniciIslemleri(i);
                    break;
                } else {
                    hak--;
                    printf("HATALI SIFRE! KALAN DENEME: %d\n", hak);
                }
            }
            break;
        }
    }
    if (!bulundu) printf("TC BULUNAMADI!\n");
}
//kayit
void kayit() {
    int gecerli;
    do {
        gecerli = 1;
        printf("ISMINIZI GIRINIZ: ");
        scanf(" %[^\n]", isim[kullanicisayisi]);
        for (int j = 0; isim[kullanicisayisi][j] != '\0'; j++) {
            if (isim[kullanicisayisi][j] >= '0' && isim[kullanicisayisi][j] <= '9') {
                printf("GECERSIZ ISLEM!\n");
                gecerli = 0;
                break;
            }
        }
    } while (!gecerli);

    do {
        printf("TC GIRINIZ: ");
        scanf("%lld", &tc[kullanicisayisi]);
    } while (tc[kullanicisayisi] < 10000000000 || tc[kullanicisayisi] > 99999999999);

    do {
        printf("4 BASAMAKLI SIFRE GIRINIZ: ");
        scanf("%d", &sifre[kullanicisayisi]);
    } while (sifre[kullanicisayisi] < 1000 || sifre[kullanicisayisi] > 9999);

    printf("GUVENLIK SORUSU SECINIZ:\n1-EN SEVDIGINIZ HAYVAN\n2- TUTTUGUNUZ TAKIM\n3-EN SEVDIGINIZ RENK\n4-ILKOKUL OGRETMENIN ADI\n");
    scanf("%d", &islem3);
    getchar();
    guvenliksoru[kullanicisayisi] = islem3;

    printf("CEVAP: ");
    scanf(" %[^\n]", guvenlikcevap[kullanicisayisi]);

    bakiye[kullanicisayisi] = 0;

    FILE *dosya = fopen("veriler.txt", "a");
    fprintf(dosya, "%s|%lld|%d|%d|%d|%s\n", isim[kullanicisayisi], tc[kullanicisayisi],
            sifre[kullanicisayisi], bakiye[kullanicisayisi], guvenliksoru[kullanicisayisi],
            guvenlikcevap[kullanicisayisi]);
    fclose(dosya);

    printf("KAYIT BASARILI!\n");
    kullanicisayisi++;
}
//kullanici islemleri
void kullaniciIslemleri(int index) {
    do {
        printf("\n1-PARA CEKME\n2-PARA YATIRMA\n3-BAKIYE\n4-CIKIS\n");
        scanf("%d", &islem);
        switch (islem) {
            case 1:
                if (bakiye[index] == 0) printf("BAKIYE YOK!\n");
                else {
                    printf("MIKTAR: ");
                    scanf("%d", &miktar);
                    if (miktar > bakiye[index]) printf("YETERSIZ BAKIYE!\n");
                    else {
                        bakiye[index] -= miktar;
                        printf("YENI BAKIYE: %d\n", bakiye[index]);
                        dosyaGuncelle();
                    }
                }
                break;
            case 2:
                printf("MIKTAR: ");
                scanf("%d", &miktar);
                bakiye[index] += miktar;
                printf("YENI BAKIYE: %d\n", bakiye[index]);
                dosyaGuncelle();
                break;
            case 3:
                printf("BAKIYE: %d\n", bakiye[index]);
                break;
        }
    } while (islem != 4);
}
//sıfre degıstırme
void sifredegistirme() {
    char cevap[50];
    printf("TC GIRIN: ");
    scanf("%lld", &girilentc);
    int bulundu = 0;
    for (i = 0; i < kullanicisayisi; i++) {
        if (tc[i] == girilentc) {
            bulundu = 1;
            int hak = 3;
            while (hak > 0) {
                printf("SIFRE GIRIN: ");
                scanf("%d", &girilensifre);
                if (sifre[i] == girilensifre) {
                    switch (guvenliksoru[i]) {
                        case 1: printf("SORU: EN SEVDIGINIZ HAYVAN?\n"); break;
                        case 2: printf("SORU: TUTTUGUNUZ TAKIM?\n"); break;
                        case 3: printf("SORU: EN SEVDIGINIZ RENK?\n"); break;
                        case 4: printf("SORU: ILKOKUL OGRETMENININ ADI?\n"); break;
                        default: printf("SORU BULUNAMADI!\n");
                    }
                    getchar();
                    printf("CEVAP: ");
                    scanf(" %[^\n]", cevap);
                    if (strcmp(cevap, guvenlikcevap[i]) == 0) {
                        int yenisifre;
                        do {
                            printf("YENI SIFRE: ");
                            scanf("%d", &yenisifre);
                        } while (yenisifre < 1000 || yenisifre > 9999);
                        sifre[i] = yenisifre;
                        dosyaGuncelle();
                        printf("SIFRE DEGISTI!\n");
                        break;
                    } else {
                        hak--;
                        printf("YANLIS! KALAN: %d\n", hak);
                    }
                } else {
                    hak--;
                    printf("YANLIS SIFRE! KALAN: %d\n", hak);
                }
            }
            break;
        }
    }
    if (!bulundu) printf("TC BULUNAMADI!\n");
}
//veri yukleme
void verileriyukle() {
    FILE *dosya = fopen("veriler.txt", "r");
    if (!dosya) return;
    while (fscanf(dosya, "%[^|]|%lld|%d|%d|%d|%[^\n]",
                  isim[kullanicisayisi], &tc[kullanicisayisi], &sifre[kullanicisayisi],
                  &bakiye[kullanicisayisi], &guvenliksoru[kullanicisayisi],
                  guvenlikcevap[kullanicisayisi]) == 6) {
        kullanicisayisi++;
    }
    fclose(dosya);
}
//dosya guncelleme
void dosyaGuncelle() {
    FILE *dosya = fopen("veriler.txt", "w");
    for (int i = 0; i < kullanicisayisi; i++) {
        fprintf(dosya, "%s|%lld|%d|%d|%d|%s\n", isim[i], tc[i], sifre[i], bakiye[i],
                guvenliksoru[i], guvenlikcevap[i]);
    }
    fclose(dosya);
}
