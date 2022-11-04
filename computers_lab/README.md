-----------------------------------------------------------
	Autor:

- Pedro Antunes  up201507254

-----------------------------------------------------------
	Ficheiros:
-Client.c		
-Server.c
-README.txt
-Client
-Server	
	
-----------------------------------------------------------
	Requisitos do sistema:
-Compilador C
-Terminal

	Testado em:
OS: Ubuntu 17.04 zesty
Kernel: x86_64 Linux 4.10.0-20-generic
Shell: bash 4.4.5

-----------------------------------------------------------
	Instruções:

0) Compilar


0.1) Compilar o servidor utilizando o comando:
	gcc Server.c -o Server
0.2) Compilar o cliente utilizando o comando:
	gcc Client.c -o Client
0.3) Executar o servidor utilizando o comando:
	./Server
0.4) Executar o cliente noutro terminal utilizando o comando:
	./Client

-----------------------------------------------------------
	Info:

- Adicionalmente o programa Servidor cria 4 ficheiros:
	logins.txt 	Lista de passwords e logins de cada utilizador.
	users.txt	Lista de users.
	topics.txt	Lista de topicos.

-Por cada topico é ainda criado 1 ficheiro:
	messages[topicID].txt 	Lista de mensagens.

-Algumas função estão incompletas:
	-/.Server -> validateUsers()
	-/.Client -> account()
		  -> searchActiveTopics()

