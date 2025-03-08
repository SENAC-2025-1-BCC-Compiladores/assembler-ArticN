[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/FLG6_3H5)
Gabriel Reimberg de Paiva

# Assembler para o WNeander

Este projeto é um **assembler** para o computador hipotético **WNeander**. Ele converte código assembly escrito em um formato específico para um arquivo binário que pode ser executado no WNeander.

---

## **Funcionalidades**

- **Leitura de código assembly**: Suporta instruções como `LDA`, `STA`, `ADD`, `HLT`, entre outras.
- **Geração de arquivo binário**: Converte o código assembly em um arquivo `.mem` que pode ser carregado no WNeander.
- **Suporte a seções `.DATA` e `.CODE`**: Permite definir dados na memória e instruções de código.
- **Tratamento de erros**: Verifica erros de sintaxe e instruções inválidas.

---

## **Estrutura do Projeto**

O projeto é composto pelos seguintes arquivos:

1. **`assembler.c`**:
   - Ponto de entrada do programa.
   - Gerencia a leitura do arquivo de entrada e a escrita do arquivo de saída.
   - Inicializa o lexer e o parser.

2. **`lexer.c` e `lexer.h`**:
   - Responsável pela análise léxica do código assembly.
   - Divide o código em tokens (mnemônicos, números, diretivas, etc.).
   - Implementa funções para ler e processar tokens.

3. **`parser.c` e `parser.h`**:
   - Responsável pela análise sintática e geração do código binário.
   - Converte tokens em instruções e dados, armazenando-os na memória.
   - Gera o arquivo de saída no formato esperado pelo WNeander.
---

## **Como Compilar**

### **Pré-requisitos**
- Compilador GCC instalado.
- Sistema operacional Linux ou Windows (com WSL ou MinGW).

### **Passos para Compilar**

1. Clone o repositório ou baixe os arquivos do projeto.
2. Navegue até o diretório do projeto.
3. Rode os comandos "gcc -o assembler Assembler.c lexer.c parser.c -Wall" e "./assembler test_code.txt output.mem"

## Limitações
1. O formato to test_code deve ser mantido
2. Não aceita criação de variáveis
3. A leitura de hexadecimal no arquivo txt não é aceita, escreva em decimal e o código fara a conversão para hexa
4. Ele reescreve o output.mem toda vez, certifique-se de telo ou um arquivo que tenha sido criado previamente pelo wneander antes de passar como parametro para o programa.

