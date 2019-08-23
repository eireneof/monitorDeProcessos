# Identificação

* Página do repositório do trabalho ([link GitHub](https://github.com/samurollie/AB2.1)) 

* Discente 1
	* Nome: Bruna Leal Torres Silva
	* Matrícula: 19111149
	* Distribuição da nota (%): 33,33%
* Discente 2
	* Nome: Eirene de Oliveira Fireman
	* Matrícula: 19110980
	* Distribuição da nota (%): 33,33%
* Discente 3
	* Nome: Samuel Lucas Vieira Lins Barbosa
	* Matrícula: 19111333
	* Distribuição da nota (%): 33,33%		
	

# Discussão

Ao se deparar com as especificações do projeto, nossa primeira dificuldade foi utilizar os parâmetros da função ```main```. Ao pesquisar, entendemos que a sigla ```argv``` nos permite passar argumentos do tipo char através do terminal.

Com isso, o nosso programa pôde reconhecer se era pra executar só a cpu ou a cpu em conjunto com a memória através da função ```string_compare()```.

```c
string_compare(0, argv[1], "ucp") == 0;
string_compare(0, argv[1], "ucp_mem") == 0;
```

## Utilização intensa da UCP

A fim de utilizar intensamente a CPU, nossa equipe utilizou o seguinte comando:

```c
for(;;) {}
```

Caracterizado por permitir um loop infinito que só pode ser quebrado ao final do processo, quando o processo pai mata o filho.

```c
strcpy(cmd, "kill ");
strcat(cmd, id);
system(cmd);
```

Para o controle de tempo utilizamos outro ```for``` aliado a uma função:

```c
for(i = 0; i < 10; i++)
{
	system(cmd);
	sleep(1);
}
```

A função ```sleep()``` permite que nosso programa espere 1 segundo sem executar nada. A estruturação desse ```for``` permitiu que nós pudéssemos analisar o programa em tempos menores, como por exemplo, 1 segundo ou 2. Isto fez-se necessário, pois dificilmente os computadores usados rodavam o programa em 10 segundos completos sem travar.

Dessa forma, o que foi relatado até agora mostra o modo escolhido pelo nosso grupo para a execução desse projeto. 

Nós não esperávamos que o rendimento da CPU ultrapassasse 100%, mas obtivemos resultados que provaram o contrário, pois tiveram momentos em que a cpu chegou a até 103% e descobrimos que isso acontece porque o processador pode ter mais de um núcleo, e cada um deles representa 100%.

O gráfico dos resultados esperados:

![CPU TEST](https://i.imgur.com/OSzMHIc.png)

O gráfico dos resultados reais:

![CPU TEST](https://i.imgur.com/yZhBThq.png)


## Utilização intensa da UCP e memória

Da mesma forma que geramos um loop infinito no caso supracitado, foi preciso gerar outro para gerenciar o uso da memória, mas com alterações, afinal, agora iria ser gerenciado além da cpu, também a memoria. Dessa forma, tivemos que fazer uma alocação dinâmica da memória, com o limite de um inteiro, ou seja, 4 bytes.

```c
for(;;)
{ 
	malloc(sizeof(int));
}
```

Tanto no uso exclusivo da cpu, quanto no uso conjunto dela com a memória nosso objetivo era executar os comandos através da função ```system()```. Foi um desafio no começo, mas após pesquisas concluímos que incluindo a biblioteca ```stdlib.h```, essa função realizaria chamadas de funções do sistema. Os comandos utilizados foram:

```c
strcpy(cmd, "ps -e -o pid,pcpu | grep ");
strcat(cmd, id);
strcat(cmd, ";pmap ");
strcat(cmd, id); 
strcat(cmd, " | grep -i Total");
```

1.	```ps```: reporta o estado do processo atual.
2.	```-e -o``` : parâmetros do ps.
3.	```grep```: procurar strings de texto e expressões regulares linha a linha.
4.	```pmap```: serve para realizar o mapeamento completo da memória em um processo.

Por fim, com esses procedimentos, os resultados obtidos foram:

![CPU - MEM TEST](https://i.imgur.com/qJQaw4M.png)

# Conclusão

Neste trabalho, foi mostrado que é possível monitorar o consumo da CPU e da memória através da criação de processos filhos idênticos aos processos pais, alterando apenas o “PID” (Process Identifier) e a posição na memória, com a chamada de sistema ```fork ()```.
