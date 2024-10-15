
# Simulador da Arquitetura de Von Neumann e Pipeline MIPS

Este projeto implementa um simulador básico da arquitetura de Von Neumann e do pipeline MIPS em C++. O objetivo é permitir a visualização prática do funcionamento de componentes como a CPU, a memória principal, a memória cache, e o pipeline, além de demonstrar o impacto das instruções executadas em paralelo usando o pipeline MIPS.

## Funcionalidades

1. **CPU**: Simula o comportamento de uma CPU com múltiplos registradores e uma Unidade Lógica Aritmética (ULA).
2. **Memória Principal e Cache**: A memória principal é simulada como um vetor, enquanto a cache é implementada como uma fila (FIFO), com substituição simples.
3. **Pipeline MIPS**: Implementa os cinco estágios do pipeline MIPS:
   - **IF (Instruction Fetch)**: Busca a instrução da memória.
   - **ID (Instruction Decode)**: Decodifica a instrução.
   - **EX (Execute)**: Executa a operação na ULA.
   - **MEM (Memory Access)**: Acessa a memória principal.
   - **WB (Write Back)**: Escreve o resultado no registrador.
   
4. **Simulação de Políticas de Cache**: A cache utiliza a política de substituição FIFO para gerenciar os dados armazenados.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
/Simulador
  ├── src/
  │    ├── main.cpp          # Arquivo principal que inicia o simulador
  │    ├── cpu.cpp           # Implementação das funções da CPU e ULA
  │    ├── memory.cpp        # Implementação das funções de memória e cache
  │    └── pipeline.cpp      # Implementação do pipeline MIPS
  ├── include/
  │    ├── cpu.h             # Declaração das funções da CPU e ULA
  │    ├── memory.h          # Declaração das funções de memória e cache
  │    └── pipeline.h        # Declaração das funções do pipeline MIPS
  └── Makefile               # Arquivo Make para compilar e rodar o projeto
```

### Arquivos:

- `main.cpp`: Responsável por simular uma execução de uma instrução usando o pipeline MIPS e cache.
- `cpu.cpp`/`cpu.h`: Contém a lógica da CPU, incluindo os registradores, Unidade Lógica Aritmética (ULA) e Unidade de Controle.
- `memory.cpp`/`memory.h`: Simula a memória principal e a cache com política de substituição FIFO.
- `pipeline.cpp`/`pipeline.h`: Implementa os cinco estágios do pipeline MIPS.

## Requisitos

- **Compilador C++**: Certifique-se de ter um compilador C++ instalado (como `g++`).
- **Make**: Utilize `make` para compilar o projeto.

## Instruções de Compilação e Execução

### Compilando o Projeto

Para compilar o projeto, basta rodar o comando:

```bash
make
```

Isso irá compilar todos os arquivos `.cpp` e gerar o executável na pasta `bin/`.

### Executando o Simulador

Para rodar o simulador após a compilação, execute:

```bash
make run
```

O simulador irá executar uma instrução `ADD` (soma) e simular os cinco estágios do pipeline MIPS, além de realizar uma leitura de memória com cache. O resultado será mostrado no terminal.

### Limpando os Arquivos Compilados

Para remover os arquivos compilados (objetos e binários), execute:

```bash
make clean
```

## Explicação do Funcionamento

### CPU e Registradores

A CPU é modelada com 32 registradores e uma ULA (Unidade Lógica Aritmética), que executa operações como soma (`+`) e subtração (`-`). A Unidade de Controle decodifica as instruções recebidas e envia sinais de controle para a ULA, permitindo a execução da operação correspondente.

### Memória e Cache

A memória principal é um vetor de 1024 posições, e a cache é uma fila de tamanho fixo (4 posições), utilizando uma política de substituição FIFO. Quando a cache está cheia, o bloco mais antigo é removido para abrir espaço para novos blocos.

### Pipeline MIPS

O pipeline MIPS simula a execução paralela de instruções em cinco estágios:

- **Instruction Fetch (IF)**: Busca a instrução da memória.
- **Instruction Decode (ID)**: Decodifica a instrução e prepara os operandos.
- **Execute (EX)**: A ULA executa a operação (por exemplo, soma ou subtração).
- **Memory Access (MEM)**: Lê ou escreve na memória.
- **Write Back (WB)**: Escreve o resultado de volta nos registradores.

### Exemplo de Execução

O simulador executa uma operação de soma entre dois registradores (`registradores[0]` e `registradores[1]`), passando por todos os estágios do pipeline. Em seguida, realiza uma leitura de memória com a cache, mostrando um exemplo de *cache miss* e *cache hit*.

## Contribuindo

Se desejar contribuir para o projeto, você pode:

1. Fazer um *fork* deste repositório.
2. Criar uma *branch* com a sua feature (`git checkout -b minha-feature`).
3. Fazer o *commit* das suas alterações (`git commit -m 'Minha nova feature'`).
4. Fazer o *push* para a *branch* (`git push origin minha-feature`).
5. Abrir um *pull request*.

## Licença

Este projeto é apenas para fins educacionais, sem uma licença formal.
