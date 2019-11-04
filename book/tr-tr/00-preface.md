---
title: Önsöz
type: kitap-tr-tr
order: 0
---

# Önsöz

[TOC]

## Giriş

C++ kullanıcı grubu oldukça büyük. C++98'in ortaya çıkışından C++11'in resmi sonuçlandırılmasına kadar, on yıldan fazla bir süredir birikmiş durumda. C++14/17, C++11 için önemli bir tamamlayıcı ve optimizasyondur ve C++20 bu dili modernleşme kapısına getirmektedir. Tüm bu yeni standartların genişletilmiş özellikleri C++ diline verilmiştir. Yeni canlılık ile aşılanmıştır. 
Halen **Geleneksel C++** kullanan C++ programcıları (bu kitap C++98 ve önceki C++ standartlarını ve geleneksel C++ ile ilgilidir), modern C++ okurken aynı dili kullanmadıklarını düşünerek şaşırabilirler.

**Modern C ++** (bu kitap, C++11/14/17/20'ye atıfta bulunur), geleneksel C++'a birçok özellik katar ve bu da tüm C++'ı modernleştirir. Modern C++, sadece C++ dilinin kullanılabilirliğini arttırmaz ancak `auto` anahtar kelime anlambiliminin değiştirilmesi bize son derece karmaşık şablon türlerini manipüle etmede daha fazla güven veriyor. Aynı zamanda, dil çalışma zamanında birçok geliştirme yapılmıştır. Lambda ifadelerinin ortaya çıkması, C++ 'nın neredeyse modern programlama dillerinde (Python / Swift / ..) bulunan "isimsiz fonksiyonlar" "kapatma" özelliğine sahip olmasını sağlamıştır. Yaygın hale geldi ve değer referanslarının ortaya çıkması, C++ 'ın uzun süredir eleştirildiği geçici nesne verimliliği sorununu çözmüştür.

C++ 17, C++ topluluğu tarafından son üç yılda tanıtılan yöndür. Aynı zamanda, **modern C++** programlamanın önemli bir gelişme yönünü gösterir. Her ne kadar C++11 kadar görünmese de, çok sayıda küçük ve güzel dil ve özellik (yapısal ciltleme gibi) içerir ve bu özelliklerin görünümü bir kez daha C++ 'daki programlama paradigmamızı düzeltir.

Modern C++ aynı zamanda kendi standart kütüphanesine, dilin kendi seviyesindeki `std :: thread` gibi eşzamanlı programlamayı destekleyen ve artık farklı platformlardaki temel sisteme bağlı olmayan birçok araç ve yöntem ekler. API, dil düzeyinde platformlar arası destek uygular; `std :: regex` tam düzenli ifade desteği ve daha fazlasını sağlar. C++ 98'in çok başarılı bir "paradigma" olduğu kanıtlandı ve modern C++ 'ın ortaya çıkışı, bu paradigmayı daha da teşvik ederek C++'ı sistem programlama ve kütüphane geliştirme için daha iyi bir dil haline getirdi. Kavramlar, şablon parametrelerinin derlenme süresi üzerinde doğrulama sağlar ve dilin kullanılabilirliğini daha da artırır.

Sonuç olarak, C ++ 'nın bir savunucusu ve uygulayıcısı olarak, yeni şeyleri kabul etmek için daima açık bir zihnimiz var ve bu eski ve yeni dili daha canlı hale getirerek C ++' ın gelişimini daha hızlı teşvik edebiliriz.

## Hedefler

- Bu kitap, okuyucuların geleneksel C++ (örneğin C++98 veya daha önceki sürümler) ile zaten aşina olduklarını varsayar, en azından geleneksel C++ kodlarını okumakta zorluk çekmezler. Başka bir deyişle, geleneksel C ++ 'da uzun deneyime sahip olanlar ve modern C++' ın özelliklerini kısa bir sürede hızlıca anlamak isteyen insanlar bu kitabı okumak için çok uygundurlar;

- Bu kitap, modern C++ 'nın karanlık büyüsünü bir dereceye kadar tanıtıyor. Ancak, bu büyüler çok sınırlıdır, ileri C++ öğrenmek isteyen okuyucular için uygun değildir. Bu kitabın amacı, modern C++ için hızlı bir başlangıç sunmaktır. Tabii ki, ileri düzeydeki okuyucular bu kitabı modern C++ 'da incelemek ve incelemek için de kullanabilirler.

## Amaç

Bu Kitap "Hak" iddia ediyor. Amacı, modern C++ ile ilgili özelliklere kapsamlı bir giriş sağlamaktır (2020'lerden önce).
Okuyucular öğrenmek ve öğrenmek istediği yeni özellikleri hızlıca tanımak için aşağıdaki içerik tablosuna göre ilginç içerikler seçebilirler.
Okuyucular bu özelliklerin hepsinin gerekli olmadığını bilmelidir. Gerçekten ihtiyacın olduğunda tekrar incelenmeli.

Aynı zamanda, sadece C++ dilbilgisi yerine kitap değil, teknik özelliklerin de olabildiğince basit olmasını ve bu özelliklerin neden ortaya çıktığını anlamak için büyük yardım sağlar.

Ek olarak yazar ve çevirmen, okurların kitaplarını okuduktan sonra kademeli olarak yeni projelerinde modern C++'ı kullanabilmeleri ve eski projelerini modern C++'a geçirmelerini teşvik etmeyi amaçlar.

## Kod

Bu kitabın her bölümünde çok fazla kod var. Kitabın giriş özellikleriyle kendi kodunuzu yazarken sorunlarla karşılaşırsanız, kitaba eklenmiş kaynak kodunu da okuyabilirsiniz. Kitabı [burada](../../ code) bulabilirsiniz. Klasör adı bölüm numarasıdır ve bütün kodlar bölümlere göre düzenlenmiştir.

## Alıştırmalar

Kitabın her bölümünün sonunda az sayıda alıştırma mevcut. Amacı bölümde öğrenilen noktaları kullanıp kullanılamadığını görmektir. Sorunun olası cevabını [buradan] (../../ alıştırmadan) bulabilirsiniz. Klasör adı bölüm numarasıdır.

[Table of Content](./toc.md) | [Next Chapter: Towards Modern C++](./01-intro.md)

## Licenses

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />Bu kitap [Ou Changkun](https://changkun.de) tarfından yazıldı ve Murat CEZAN tarafından **Türkçe** diline çevrildi. Lisansı <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a> altındadır. Bu havuzun kodları [MIT license](../../LICENSE) lisans altında açık kaynaklıdır.
