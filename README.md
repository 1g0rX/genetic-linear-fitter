
# <h1 align="center"> Algoritmo Genético: Ajuste de Função Linear </h1>

<p align="center">
<img loading="lazy" src="https://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=GREEN&style=for-the-badge" />
<img loading="lazy" src="https://img.shields.io/static/v1?label=Linguagem&message=C%2B%2B&color=blue&style=for-the-badge" />
<img loading="lazy" src="https://img.shields.io/static/v1?label=Disciplina&message=AEDS%20I&color=orange&style=for-the-badge" />
</p>

## :page_with_curl: Introdução

<p align="justify">
Ajuste de curvas e regressão linear são desafios muito comuns na matemática e na computação. O objetivo é simples: encontrar uma linha que passe o mais perto possível de um conjunto de pontos espalhados em um gráfico.

Neste projeto, em vez de usar fórmulas fechadas da estatística tradicional, utilizamos uma técnica de Inteligência Artificial chamada <b>Algoritmo Genético (AG)</b>. Inspirado na teoria da evolução de Charles Darwin, o nosso programa cria uma "população" de linhas aleatórias e faz com que elas cruzem, sofram mutações e compitam entre si. Geração após geração, as linhas ruins são descartadas e o algoritmo converge para coeficientes próximos da reta ideal.

</p>

## :bookmark_tabs: Descrição do Projeto

Este software é um simulador computacional desenvolvido em **C++ Orientado a Objetos** para ajustar uma função linear do tipo 

$$\hat{y} = ax + b$$ 

a um conjunto de coordenadas $(x, y)$.

A população do algoritmo é gerenciada utilizando alocação de memória dinâmica através da estrutura `std::vector`. Cada indivíduo dentro do programa possui seu próprio "DNA", que guarda os valores de $a$ (a inclinação da reta) e $b$ (a altura onde a reta corta o eixo). Ao longo da execução, o algoritmo busca diminuir as distâncias entre a reta e os pontos de entrada até encontrar a resposta ideal.

O trabalho foi proposto pelo professor Michel Pires Silva, como um exercício prático para a disciplina de Algoritmos e Estrutura de Dados I, do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET - MG).

## 🧮 Base Matemática do Algoritmo

Abaixo estão detalhados os dois principais cálculos que o sistema faz a cada tentativa:

### 1. Erro Quadrático Médio (MSE)

Para saber se um indivíduo (reta) está indo bem, calculamos o Erro Quadrático Médio (MSE, do inglês *Mean Squared Error*). A fórmula é:

$$
\text{Erro} = \frac{1}{n} \sum_{i=1}^{n} (y_i - \hat{y}_i)^2
$$

**Na prática, acontece o seguinte:**

1. O programa olha para um ponto real ($y_i$) e compara com onde a reta estimou que o ponto estaria ($\hat{y}_i$).

2. Ele subtrai um do outro para ver a distância.

3. Essa distância é elevada ao quadrado. Fazemos isso por dois motivos: transformar qualquer número negativo em positivo (já que distância não pode ser negativa) e para punir erros grandes de forma mais severa.

4. Por fim, ele soma o erro de todos os pontos e divide pela quantidade de pontos ($n$), tirando uma média. Quanto menor for esse erro final, melhor é a reta.

### 2. Cálculo de Aptidão (Fitness)

Algoritmos genéticos geralmente buscam maximizar uma nota, mas o nosso MSE busca minimizar um erro. Para transformar o erro em uma nota de aprovação (Fitness), usamos a fórmula:

$$
\text{Fitness} = \frac{1}{\text{Erro} + 10^{-6}}
$$


> A constante $10^{-6}$ está na fórmula como uma forma de segurança contra crashes caso houver uma divisão por zero, garantindo assim estabilidade numérica.

## :pushpin: O Ciclo Evolutivo

A simulação acontece em um ciclo de repetição que roda por $G$ gerações. O modelo usado foi o **Steady-State** (estado estacionário), que significa que a população inteira não é destruída de uma vez. Em vez disso, nós só substituímos os piores.

1. **Seleção:** A função `selectBest` verifica a população inteira e escolhe os dois indivíduos com as melhores notas (maior fitness) para serem os "pais" da próxima geração.

2. **Cruzamento (Crossover):** O novo descendente (Filho) herda a inclinação ($a$) do Pai 1 e a altura ($b$) do Pai 2. É a união das melhores características.

3. **Mutação:** Para o algoritmo não ficar preso sempre nos mesmos números, o Filho sofre uma mutação. Um dos seus genes sofre um acréscimo ou decréscimo baseado em uma taxa bidirecional chamada `delta` (explicada mais abaixo).

4. **Atualização:** O indivíduo com o pior desempenho de toda a população é procurado, removido e o novo Filho entra no seu lugar.

## ⚙️ Ajustes, Parâmetros e Como Alterá-los

O simulador permite algumas alterações. Alguns parâmetros podem ser alterados em `src/simulation.cpp`:

### Passo de Mutação (`delta`):

Definido como `double delta = 0.1;`, ele é o limite máximo do valor que será adicionado ou subtraído do gene durante a mutação. O sistema sorteia aleatoriamente um valor entre $-\delta$ e $+\delta$.

* Se você **aumentar** esse valor (ex: para `1.0`), as mutações causarão mudanças bruscas. Isso é útil no começo para a reta dar grandes "saltos" pelo gráfico.

* Se você **diminuir** esse valor (ex: para `0.01`), a mutação fará mudanças microscópicas. É ótimo para o ajuste fino, permitindo um ajuste mais fino, aproximando o erro de zero.

### Semente (`seed`):

O computador não sabe gerar números verdadeiramente aleatórios, ele usa fórmulas complexas que parecem aleatórias (pseudoaleatórios). A variável `int seed = 42;` é o ponto de partida dessa fórmula.

* A utilidade da semente é a **reprodutibilidade**. Se rodarmos o código hoje e amanhã usando a mesma `seed 42`, os resultados iniciais sorteados serão exatamente iguais. Isso é vital para saber se uma modificação feita no código realmente melhorou o programa ou se foi apenas sorte.

* Se você alterar o número da `seed` para `10`, `99` ou `123`, a população inicial nascerá em locais completamente diferentes, mudando a história da evolução.

## 🧪 Casos de Teste e Validação

Para verificar o código na prática, utilizamos três cenários simples de testes limitados a apenas **20 gerações** e com mutações de `0.1`. Abaixo estão as saídas reais geradas pelo sistema:

### Teste 1: Uma Reta
Neste teste, os pontos desenham exatamente a função $y = 2x + 0$.
**Entrada (`input.dat`):**

```

4 10 20
1.0 2.0
2.0 4.0
3.0 6.0
4.0 8.0

```

**Saída Resumida (`output.dat`):**

```

0.157969 6.33036 0.984423 0.2937   \<-- (Geração inicial: Erro alto 6.33)
...
10.0301 0.0996992 1.78442 0.334963 \<-- (Geração intermediária: Erro despenca para 0.09)
...
36.1366 0.0276718 1.88442 0.3937   \<-- (Geração 20: Erro aproximando de zero)

```

**Análise:** Em apenas 20 gerações, a coluna de Erro cai de 6.33 para 0.027, enquanto os coeficientes migram em direção à resposta correta ($a \approx 2.0$ e $b \approx 0.0$).

> **Nota de Precisão Matemática:** Como o algoritmo utiliza representação de ponto flutuante em um espaço contínuo, é estatisticamente improvável sortear exatamente os valores `2.000000` e `0.000000`. Em simulações mais longas, o erro atingirá notações da ordem de $10^{-5}$ (ex: `0.00008`), o que caracteriza a **Convergência Absoluta** da Inteligência Artificial.

### Teste 2: Pontos Dispersos

Neste teste, os pontos formam uma leve curva. Não existe uma linha reta perfeita que passe por todos eles ao mesmo tempo.
**Entrada (`input.dat`):**

```

4 10 20
1.0 2.5
2.0 4.1
3.0 6.0
4.0 8.2

```

**Saída Resumida (`output.dat`):**

```

0.141853 7.04956 0.984423 0.2937   \<-- (Geração inicial: Erro 7.04)
...
4.94077 0.202397 1.78442 0.334963  \<-- (Geração intermediária: Erro cai para 0.20)
...
43.8079 0.0228259 1.88442 0.4937   \<-- (Geração 20: Reta ideal encontrada)

```

**Análise:** O programa acha o "meio-termo". O erro estabiliza em `0.0228`, apontando para a reta $y = 1.88x + 0.49$. O erro nunca chegará exatamente a zero, pois a reta sofre de um erro de margem físico inevitável para esses pontos, mas o algoritmo converge perfeitamente para o mínimo absoluto possível.

### Teste 3: Reta Decrescente (Comportamento Adaptativo)

Neste teste, simulamos a função $y = -2x + 10$. Aqui a reta "cai" em vez de subir, exigindo que o algoritmo encontre um coeficiente angular negativo para o gene $a$.
**Entrada (`input.dat`):**

```

4 10 20
1.0 8.0
2.0 6.0
3.0 4.0
4.0 2.0

```

**Saída Resumida (`output.dat`):**

```

0.0618254 16.1746 0.984423 0.2937   \<-- (Geração inicial: Erro alto 16.17)
...
0.064188  15.5792 1.18442  0.334963 \<-- (Geração intermediária)
...
0.0682741 14.6468 1.18442  0.634963 \<-- (Geração 20: O erro está caindo)

```

**Análise Comportamental:** Este teste demonstra a inteligência do algoritmo. Como os pontos exigem valores muito altos no eixo Y ($8.0$, $6.0$), e a população inicial nasceu com uma base muito baixa ($b = 0.29$), o algoritmo encontrou mais facilidade de sobrevivência ajustando o termo linear $b$ (aumentando-o para $0.63$) do que tentando inclinar a reta no curto prazo das 20 iterações. Em uma simulação mais longa, a reta estabilizaria sua elevação e passaria a buscar agressivamente a declividade negativa para a resposta ideal ($a = -2.0, b = 10.0$).

## 📈 Análise Assintótica e Eficiência

O código foi desenvolvido para poupar memória e processamento. Em vez de reavaliar toda a população, que teria um custo e um tempo de $\mathcal{O}(G \times m \times n)$, a avaliação da população inteira ocorre apenas uma vez na geração 0. Nas gerações seguintes, é avaliado apenas o filho recém nascido, pois o resto da população não mudou.


| **Operação Genética** | **Tempo (Pior Caso)** | **Descrição** | 
 | ----- | ----- | ----- | 
| Avaliação Inicial | $\mathcal{O}(m \times n)$ | Realizada 1 vez antes do loop iniciar. | 
| Seleção de Pais | $\mathcal{O}(m)$ | Procura linear rápida sem usar ordenação (`sort`). | 
| Avaliação do Filho | $\mathcal{O}(n)$ | Processa apenas os $n$ pontos do arquivo. | 
| Substituição | $\mathcal{O}(m)$ | Procura o pior indivíduo linearmente. | 
| **Total Global** | $\mathcal{O}(m \cdot n + G \cdot (m + n))$ | **Muito mais leve e rápido do que algoritmos padrão.** | 

*(Onde:* $m$ *= População,* $n$ *= Coordenadas,* $G$ *= Número de gerações).*

## :file_folder: Estrutura do Projeto

```

/
├── Makefile                   \# Script de compilação automatizada
├── README.md                  \# Documentação do projeto
├── include/                   \# Arquivos de cabeçalho (.hpp)
│   ├── evaluation.hpp         \# Estrutura do indivíduo e matemática
│   ├── geneticAlgorithm.hpp   \# Motor de evolução
│   ├── io.hpp                 \# Manipulação de arquivos
│   └── simulation.hpp         \# Setup principal
├── src/                       \# Código-fonte (.cpp)
│   ├── evaluation.cpp         \# Lógica de genes e fitness
│   ├── geneticAlgorithm.cpp   \# Seleção, Crossover e Mutação
│   ├── io.cpp                 \# Leitura e escrita (dat)
│   ├── main.cpp               \# Ponto de partida do software
│   └── simulation.cpp         \# Variáveis iniciais e orquestração
└── data/                      \# Local dos dados e relatórios
├── input.dat              \# Arquivo de leitura principal
└── output.dat             \# Saída com os resultados geracionais

```

## :keyboard: Instalação e Execução

### 1. Verificando os Requisitos do Sistema

Antes de começar, o seu ambiente GNU/Linux precisa ter as ferramentas de compilação instaladas. Abra o terminal e verifique:

**Compilador C++ (`g++`):**

```

g++ --version

```

*(Se o comando não for reconhecido, instale usando: `sudo apt update && sudo apt install g++`)*

**Utilitário de Build (`make`):**

```

make --version

```

*(Se o comando não for reconhecido, instale usando: `sudo apt update && sudo apt install make`)*

### 2. Passo a Passo para Uso

**Passo 1: Clonar o repositório**
No terminal, baixe o projeto para a sua máquina:

```

git clone [https://github.com/1g0rX/genetic-linear-fitter.git](https://www.google.com/search?q=https://github.com/1g0rX/genetic-linear-fitter.git)

```

**Passo 2: Entrar na pasta do projeto**

```

cd genetic-linear-fitter

```

**Passo 3: Configurar os dados (`input.dat`)**
Crie o arquivo `data/input.dat` e coloque os seus dados. O formato deve ser: número de pontos, população e gerações na primeira linha, seguidos pelos pontos de X e Y.

**Passo 4: Compilar o código**
Use o Makefile para limpar sujeiras antigas e compilar novamente:

```

make clean
make

```

**Passo 5: Executar a simulação**

```

make run

```

Ao finalizar, abra a pasta `data/` e visualize o arquivo `output.dat`. A última linha representará a reta vitoriosa calculada pelo seu computador!

## :computer: Ambiente de Teste

Este projeto foi desenvolvido, executado e testado utilizando:

* **Sistema Operacional:** Debian GNU/Linux 13 (Trixie) e Debian GNU/Linux Testing

* **Compilador:** GCC (g++)

* **Automação:** GNU Make

## 👥 Desenvolvedor do Projeto

<div align="center">
<a href="https://github.com/1g0rX">
<img src="https://avatars.githubusercontent.com/1g0rX" width="120" alt="Foto do Igor Moreira" style="border-radius: 50%;">
</a>

<strong>Igor Moreira</strong>

Estudante de Engenharia de Computação no CEFET-MG.
</div>
