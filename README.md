# t1-concorrentes
T1 de Concorrentes :)

Como executar? (a partir do makefile criado)
1. Execute o comando 'make' (sem aspas) para compilar o programa.
2. Execute o comando 'make normal' (sem aspas) para rodar a versão sequencial do programa.
3. Execute o comando 'make thread' (sem aspas) para rodar a versão com threads do programa.
4. Execute o comando 'make clean' (sem aspas) para apagar o arquivo executável e de compilação.

Adicional:
- Para rodar a bateria de testes com o script tests.sh basta executar o comando 'make tests' (sem aspas).
1. Para rodar a versão sequencial do programa, altere no arquivo 'tests.sh' na linha 13, coluna 47, de modo a ficar 'make normal' (sem aspas) no lugar.
2. Para rodar a versão com threads do programa, altere no arquivo 'tests.sh' na linha 13, coluna 47, de modo a ficar 'make thread' (sem aspas) no lugar.