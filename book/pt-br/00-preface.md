---
title: Prefacio
type: book-pt-br
order: 0
---

# Prefacio

[TOC]

## Introdução

O grupo de usuários de C++ é muito grande.  Desde o advento do C++98 até
a finalização oficial do C++11 passou mais de uma década. O C++14/17 são
importantes complementos e optimizações para o C++11, e o C++20 traz essa
linguagem para a porta da modernização. Os recursos estendidos de todos esses
novos padrões são fornecidos à linguagem C++. Infundido com uma nova
vitalidade.

Os programadores C++ que ainda estão usando o **C++ tradicional** (este livro
se refere a C++98 e seus padrões C++ anteriores como C++ tradicional) podem até
ficar surpresos pelo fato de não estarem usando a mesma linguagem ao ler
o código do C++ moderno.

O **C++ moderno** (este livro se refere a C++11/14/17/20) introduz muitos
recursos ao C++ tradicional, o que faz com que todo o C++ se torne uma
linguagem modernizada. O C++ moderno não apenas melhora a usabilidade da
linguagem C++ em si, mas a modificação da semântica da palavra-chave `auto` nos
dá mais confiança na manipulação de tipos de template extremamente complexos.
Ao mesmo tempo, muitos aprimoramentos foram feitos no tempo de execução da
linguagem. O surgimento de expressões Lambda fez com que C++ tivesse o recurso
de "fechamento" de "funções anônimas", que é quase em linguagens de programação
modernas (como Python/Swift/... Tornou-se comum, e o surgimento de
referências rvalueresolveu o problema da eficiência do objeto temporário que
o C++ há muito vem sendo criticado.

C++17 está na direção que tem sido promovida pela comunidade C++ nos últimos
anos. Ele também aponta uma importante direção de desenvolvimento da
programação C++ moderna. Embora não apareça tanto quanto C++11, ele contém um
grande número de pequenas e belos recursos de linguagens (como vinculação
estruturada), e o aparecimento desses recursos mais uma vez corrige nosso
paradigma de programação em C++.

O C++ moderno também adiciona muitas ferramentas e métodos à sua própria
biblioteca padrão, como `std::thread` no nível da própria linguagem, que
oferece suporte à programação simultânea e não depende mais do sistema
subjacente em diferentes plataformas. A API implementa suporte de plataforma
cruzada no nível de linguagem;`std::regex` fornece suporte completo
a expressões regulares e muito mais. C++98 provou ser um "paradigma" de muito
sucesso, e o surgimento do C++ moderno promove ainda mais esse paradigma,
tornando o C++ uma linguagem melhor para programação de sistemas
e desenvolvimento de bibliotecas. Os conceitos fornecem verificação no tempo de
compilação dos parâmetros do modelo, melhorando ainda mais a usabilidade da
linguagem.

Concluindo, como defensores e praticantes de C++, sempre mantemos a mente
aberta para aceitar coisas novas e podemos promover o desenvolvimento de C++
mais rápido, tornando esta linguagem antiga e inovadora mais vibrante.

## Objetivos

- Este livro assume que os leitores já estão familiarizados com o C++
  tradicional (ou seja, C++98 ou anterior), pelo menos eles não têm nenhuma
  dificuldade em ler o código C++ tradicional. Em outras palavras, aqueles que
  têm longa experiência em C++ tradicional e pessoas que desejam entender
  rapidamente os recursos do C++ moderno em um curto período de tempo estão bem
  preparados para ler o livro;
- Este livro apresenta, até certo ponto, a magia negra do C++ moderno. No
  entanto, essas magias são muito limitadas, não são adequadas para leitores
  que desejam aprender C++ avançado. O objetivo deste livro é oferecer um
  início rápido para o C++ moderno. Obviamente, leitores avançados também podem
  usar este livro para revisar e examinar a si mesmos no C++ moderno.

## Propósito

O livro afirma "On the Fly". Sua intenção é fornecer uma introdução abrangente
aos recursos relevantes relacionados ao C++ moderno (antes de 2020).

Os leitores podem escolher conteúdo interessante de acordo com a tabela de
conteúdo a seguir para aprender e familiarizar-se rapidamente com os novos
recursos que você gostaria de aprender.

Os leitores devem estar cientes de que todos esses recursos não são
necessários. Deve ser aprendido quando você realmente precisar.

Ao mesmo tempo, em vez de apenas gramática, o livro apresenta o contexto
histórico o mais simples possível de seus requisitos técnicos, o que fornece
uma grande ajuda para entender por que esses recursos aparecem.

Além disso, o autor gostaria de encorajar que os leitores sejam capazes de usar
C++ moderno diretamente em seus novos projetos e migrar seus projetos antigos
para C++ moderno gradualmente depois de ler o livro.

## Código

Cada capítulo deste livro contém muitos códigos. Se você encontrar problemas ao
escrever seu próprio código com os recursos introdutórios do livro, você também
pode ler o código-fonte anexado ao livro. Você pode encontrar o livro [aqui](../../code).
Todo o código organizado por capítulo, o nome da pasta é o número do capítulo.

## Exercícios

Existem alguns exercícios no final de cada capítulo do livro.É para testar se
você pode usar os pontos de conhecimento do capítulo atual. Você pode encontrar
a possível resposta para o problema [aqui](../../exercise). O nome da pasta
é o número do capítulo.

[Sumário](./toc.md) | [Próximo Capítulo: Towards Modern C++ ](./01-intro.md)

## Licenças

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">
<img alt="Creative Commons License" style="border-width: 0" src ="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" />
</a><br />
Este trabalho foi escrito por [Ou Changkun](https://changkun.de) e licenciado sob a
<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Licença Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International</a>.
O código deste repositório é de código aberto sob a [licença MIT] (../../LICENSE).
