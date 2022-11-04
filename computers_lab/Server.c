#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <time.h>
//GRUPO BN

void logout();
void menu();
void login();
int loginCheck(char *line);
void showUsers();
void validateUsers();
void newUser();
void validateUsers();
void showUsers();
void manageUsers();
void newTopic();
void showMessages(int topic);
void showTopics();
void manageTopics();


int main() {
	FILE *f1, *f2;

	if( (f1 = fopen("logins.txt", "r")) == NULL) {
		f1 = fopen("logins.txt", "w");
		fprintf(f1, "%s;%s;a\n", "admin", "admin");
	}

	if( (f2 = fopen("users.txt", "r")) == NULL) {
		f2 = fopen("users.txt", "w");
		fprintf(f2, "%s;%s;%s;%s;%s;%s\n", "admin", "910000000", "admin", "admin", "admin@gmail.com","14/09/1996");
	}

	fclose(f1);
	fclose(f2);
	login();
	return 0;
}

void login() {
	int op, flag;
	char username[50];
	char password[50];
	char *pointer;

	printf("//------------------//\n");
	printf("//  SERVIDOR LOGIN  //\n");
	printf("//------------------//\n\n");

	printf("( 1 ) Login - autenticacao\n");
	printf("( 2 ) Sair\n");	
	scanf("%d", &op);

	if( op==1 ) {
		
		printf("\nUtilizador: ");
		scanf("%s", username);
		pointer = getpass("Password: ");
		strcpy(password,pointer);
		
		char user_pass[100];
		strcpy(user_pass,username);
		strcat(user_pass,";");
		strcat(user_pass,password);
		strcat(user_pass,";a");

		if(flag = loginCheck(user_pass) == 0) {
			printf("\n\n:(   --LOGIN INVALIDO--\n");
			sleep(1);
			system("clear");
			login();
		}
		else if(flag == -1) {
			printf("\n\n:(   --NAO EXISTEM UTILIZADORES--");
			sleep(1);
			exit(0);
		}
	}
	else {
		if( op !=2 )	printf("\n\n:(   --OPCAO INVALIDO--\n");
		exit(0);
	}

	system("clear");
	menu();
}

/**** Verify if login its correct **/
int loginCheck(char *line) {
	FILE *f, *f2;
	char buf[500];
	char aux[500];
	int j, flag = 0;
	if( (f = fopen("logins.txt","r")) == NULL) {
		return (-1);
	}

	f2 = fopen("logins_tmp.txt", "w");

	while(fgets(buf, 500, f) != NULL) {
		j=1;
		if(strstr(buf, line) != NULL) {
			char *token = strtok(buf, ";");
			strcpy(aux,token);

	    	// Keep printing tokens while one of the
	    	// delimiters present in buf[].
	    	while ((token = strtok(NULL, ";")) != NULL) {
	    		//token = strtok(NULL, ";");
	    		if( j == 2 ){
	    			strcat(aux,";a");
	    			time_t rawtime;
  					struct tm * timeinfo;

  					time ( &rawtime );
  					timeinfo = localtime ( &rawtime );
  					strcat(aux,";");
  					strcat(aux, asctime (timeinfo) );
	    		}
	        	else if (j == 3){
	        		/*clear last date*/
	        	}
	        	else{
	        		strcat(aux,";");
        			strcat(aux,token);
        		}
        		j++;
	    	}
	    	fprintf(f2, "%s", aux);
			flag = 1;

		}
		else 	fprintf(f2, "%s", buf);
	}
	fclose(f);
	fclose(f2);

	if(flag == 1){
		j=remove("logins.txt");
		j=rename("logins_tmp.txt","logins.txt");
	}
	else	j = remove("logins_tmp.txt");
	return flag;
}

/**** Create and save one new user **/
void newUser(){
	printf("//-----------------//\n");
	printf("//  NOVO UTILIZADOR  //\n");
	printf("//-----------------//\n\n");
	
	char nome[50];
	char contato[9];
	char username[50];
	char password[50];
	char email[50];
	char dataNascimento[10];
	char *pointer;

	printf("Nome: ");
	scanf("%s", nome);
	printf("Contacto: ");
	scanf("%s", contato);
	printf("Utilizador: ");
	scanf("%s", username);
	pointer = getpass("Password: ");
	strcpy(password,pointer);
	printf("Email: ");
	scanf("%s", email);
	printf("Data de Nascimento: ");
	scanf("%s%*c", dataNascimento);
	printf("%s\n",dataNascimento);
	char user[220];
	strcpy(user, nome);
	strcat(user, ";");
	strcat(user, contato);
	strcat(user, ";");
	strcat(user, username);
	strcat(user, ";");
	strcat(user, password);
	strcat(user, ";");
	strcat(user, email);
	strcat(user, ";");
	strcat(user, dataNascimento);


	FILE *f, *f2, *f3;
	char buf[500];
	f3 = fopen("logins.txt","a");
	f = fopen("users.txt","a");
	f2= fopen("users.txt","r");
	int flag = 0;

	while(fgets(buf,500,f2) != NULL) {
		char *token = strtok(buf,";");
		token = strtok(buf,";");
		token = strtok(buf,";");

		if(strcmp(token, username) == 0)	flag=1;
	}
	fclose(f2);

	if(flag == 1){
		printf(":(    --Username já existe---\n");
		sleep(1);
		system("clear");
		menu();
	}
	else{
		fprintf(f,"%s\n",user);
		fclose(f);

		char isAdmin;
		printf("\n\n --NOVO ADMIN ? (s/n)-- \t");
		scanf("%c",&isAdmin);
		//getchar();

		//debug
		//printf("%s",user);

		if(isAdmin == 's' || isAdmin == 'S') 
			fprintf(f3, "%s;%s;a\n", username,password);
		else 
			fprintf(f3, "%s;%s;u\n", username,password);
		fclose(f3);

		printf("\n\n :)   --Utilizador %s Criado!--  \n",username);
		sleep(1);
		system("clear");
		menu();
	}
}

/**** Show all users and manage users that need validation **/
void validateUsers() {
	int i=0;
	int j,k=0;
	char buf[500];

	system("clear");
	printf("//-----------------//\n");
	printf("//  UTILIZADORES  //\n");
	printf("//-----------------//\n\n");

	FILE *f, *f2, *f3;
	f = fopen("users.txt","r");
	f2 = fopen("users_tmp.txt", "w");		//auxliar
	f3 = fopen("logins.txt","a");

	while( (fgets(buf, 500, f)) != NULL) {
		char user[500];
		char *token = strtok(buf, ";");
		strcpy(user,token);

	  	printf("| UTILIZADOR %d |\n",++i);
	  	j=0;
	  	printf("Nome: %s\n", token);
	    // Keep printing tokens while one of the
	    // delimiters present in str[].
	    while ((token = strtok(NULL, ";")) != NULL) {
	    	switch(j) {
	    		case 0:	printf("Contato: ");
	    			break;
	    		case 1:	printf("Username: ");
	    			break;
	    		case 2:	printf("Password: ");
	    			break;
	    		case 3:	printf("Email: ");
	    			break;
	    		case 4:	printf("Data de Nascimento: ");
	    			break;
	    		default:
	    			break;
	    	}

	        printf("%s\n", token);
	        strcat(user,";");
	        strcat(user,token);
	        j++;
	    }

		
		if(j == 5 && strcmp(token,"tmp")==0) {
			char validate, *username = strtok(user, ";"), *password = strtok(NULL, ";");
			printf("?   ---Pretende validar este utilizador?--- (s/n)\n");
			scanf("%c",&validate);
			if(validate == 's' || validate == 'S') {
				fprintf(f2,"%s",user);
				fprintf(f3,"%s;%s;u\n", username, password);
				printf("\n:)    --Utilizador %s Validado!--", username);
				k++;
			}
			else fprintf(f2,"%s",user);
		}
		else	 fprintf(f2,"%s",user);
	}
	fclose(f);
	fclose(f2);
	fclose(f3);

	if(k!=0){
		if(k==1)   printf("\n\t----- 1 UTILIZADOR VALIDADO-----");
		else       printf("\n\t----- %d UTILIZADORES VALIDADOS-----",k);
		j=remove("users.txt");
		j=rename("users_tmp.txt", "users.txt");
	}
	else {
		printf("\n\t-----NAO EXISTEM UTILIZADORES POR VALIDAR-----");
	}
	fflush(stdout);
	sleep(1);
	menu();
}

/**** Show all users registered **/
void showUsers(){
	FILE * f;
	char buf[500];
	int i=0, j;

	printf("//------------------//\n");
	printf("//   UTILIZADORES   //\n");
	printf("//------------------//\n\n");

	if((f = fopen("users.txt","r")) == NULL) {
		printf("Nao existem utilizadores.\n");
		sleep(1);
		menu();
	}
	else {
		while( (fgets(buf, 500, f)) != NULL) {
			//printf("%s",buf);
			char *token = strtok(buf, ";");
			j=0;
		  	printf("\t| UTILIZADOR %d |\n",++i);

		    // Keep printing tokens while one of the
		    // delimiters present in str[].
		    while (token != NULL) {
		    	switch(j) {
		    		case 0:	printf("\tNome: ");
		    			break;
		    		case 1:	printf("\tContato: ");
		    			break;
		    		case 2:	printf("\tUsername: ");
		    			break;
		    		case 3:	printf("\tPassword: ");
		    			break;
		    		case 4:	printf("\tEmail: ");
		    			break;
		    		case 5:	printf("\tData de Nascimento: ");
		    			break;
		    	}
		    	
		        printf("%s\n", token);
		        token = strtok(NULL, ";");
		        j++;
		    }
		}
	}
	fclose(f);
}

/**** All users can be edited in this function **/
void manageUsers() {
	showUsers();
	int op, us;
	char user[500];
	char isAdmin;

	printf("//  ---OPCOES---  //\n");
	printf("\t( 1 ) Editar\n");
	printf("\t( 2 ) Remover\n");
	printf("\t( 3 ) Voltar\n");
	printf("PS: NAO INSIRA CARACTERES. GRANDES PROBABILIDADES DE BUG\n\n");
	printf("*Escolha a ACAO que pretende realizar* -> ");
	scanf("%d", &op);
	if( op == 3) {
		system("clear");
		menu();
	}
	printf("*Escolha o UTILIZADOR* -> ");
	scanf("%d", &us);

	if (op != 1 && op != 2) {
		printf("\n:(     --OPCAO INVALIDA--\n");
		sleep(1);
		system("clear");
		menu();
	}
	if (op == 1) {
		char nome[50];
		char contato[9];
		char username[50];
		char password[50];
		char email[50];
		char dataNascimento[10];
		char *pointer;

		printf("Nome: ");
		scanf("%s", nome);
		printf("Contacto: ");
		scanf("%s", contato);
		printf("Utilizador: ");
		scanf("%s", username);
		pointer = getpass("Password: ");
		strcpy(password,pointer);
		printf("Email: ");
		scanf("%s", email);
		printf("Data de Nascimento: ");
		scanf("%s%*c", dataNascimento);
		printf("%s\n",dataNascimento);
	
		strcpy(user, nome);
		strcat(user, ";");
		strcat(user, contato);
		strcat(user, ";");
		strcat(user, username);
		strcat(user, ";");
		strcat(user, password);
		strcat(user, ";");
		strcat(user, email);
		strcat(user, ";");
		strcat(user, dataNascimento);
		printf("\n\n --NOVO ADMIN ? (s/n)-- \t");
		scanf("%c",&isAdmin);
		getchar();
	}

	int count=0, j;
	char aux[500];
	char buf[500];

	FILE * f, * f2, * f3, * f4;
	f = fopen("users.txt","r");
	f2 = fopen("users_tmp.txt", "w");		//auxliar
	
	while( (fgets(buf, 500, f)) != NULL) {
		char *token = strtok(buf, ";");
		strcpy(aux,token);

	    // Keep printing tokens while one of the
	    // delimiters present in buf[].
	    while ((token = strtok(NULL, ";")) != NULL) {
	    	//token = strtok(NULL, ";");

	        strcat(aux,";");
        	strcat(aux,token);
	    }
	    //printf("%s\n",aux);
		
		if( op == 1 ){
			if( count == (us-1) )	fprintf(f2, "%s\n", user);
			else    				fprintf(f2,"%s",aux);
		}
		else if (count != (us-1) )
			fprintf(f2,"%s",aux);
		count++;
	}

	fclose(f);
	fclose(f2);

	f3 = fopen("logins.txt", "r");
	f4 = fopen("logins_tmp.txt", "w");
	count=0;

	while( (fgets(buf, 500, f3)) != NULL){
		char *token = strtok(buf, ";");
		strcpy(aux,token);

		// Keep printing tokens while one of the
	    // delimiters present in str[].
	     while ((token = strtok(NULL, ";")) != NULL) {
	        strcat(aux,";");
        	strcat(aux,token);
	    }

	    if( count == (us-1) ) {
	    	if( op == 1 ) {
	    		char *username = strtok(user, ";");
	    		username = strtok(NULL, ";");
	    		username = strtok(NULL, ";");
	    		char *password = strtok(NULL, ";");

	    		char *subs = strtok(aux, ";");
	    		subs = strtok(NULL, ";");
	    		subs = strtok(NULL, ";");
	    		subs = strtok(NULL, ";");

	    		if( isAdmin == 'S' || isAdmin == 's' )
	    			fprintf(f4, "%s;%s;a;%s", username, password, subs);
	    		else 
	    			fprintf(f4, "%s;%s;u;%s", username, password, subs);
	    		printf("\n\n :)   --Utilizador %s Editado!--  \n",username);
	    	}
	    	else
	    		printf("\n\n :)   --Utilizador %s Removido!--  \n",strtok(aux,";"));
		/** state delete user.. nothing to do  **/

	    }
	    else	fprintf(f4, "%s", aux);
	    count++;
	}
	fclose(f3);
	fclose(f4);

	j=remove("users.txt");
	j=rename("users_tmp.txt", "users.txt");
	j=remove("logins.txt");
	j=rename("logins_tmp.txt", "logins.txt");

	sleep(1);
	system("clear");
	menu();
}

/**** Create and save one new topic **/
void newTopic() {
	printf("//-----------------//\n");
	printf("//   NOVO TOPICO   //\n");
	printf("//-----------------//\n\n");

	int id;
	char desc[250];
	int numeroMAX;
	int subs = 0;
	char str[20];

	printf("ID: ");
	scanf("%d", &id);
	printf("Descricao do Topico <250 caracteres> : ");
	scanf("%s", desc);
	printf("Numero MAXIMO de mensagem permitidas: ");
	scanf("%d", &numeroMAX);

	FILE *f1, *f2;
	char buf[500];
	f2 = fopen("topics.txt","r");
	int flag = 0;
	
		if( (f1 = fopen("topics.txt","a")) == NULL ) {
			f1 = fopen("topics.txt", "w");
			printf("ENTREI\n");
			fprintf(f1,"%d;%s;%d;%d\n", id, desc, numeroMAX, subs);
		}
		else {		
			printf("ENTREI\n");
			while(fgets(buf,500,f2) != NULL) {
				printf("ENTREI\n");
				char *token = strtok(buf,";");
				if(atoi(token) == id)	flag =1;
			}
			fclose(f2);
			if(flag == 1){
				printf(":(    ---ID do Topico ja usado---\n");
				sleep(1);
				system("clear");
				menu();
			}
			else
				fprintf(f1,"%d;%s;%d;%d\n",id, desc, numeroMAX, subs);
		}
		sprintf(str, "messages%d.txt", id);
		f2 = fopen(str, "w");	//Create file for trade messages
		fclose(f1);

		printf("\n\n :)   --%do Topico (%s) Criado!--  \n", id, desc);
		sleep(1);
		system("clear");
		menu();
	
}

/**** Show all topics registered **/
void showTopics() {
	FILE * f;
	char buf[500];
	int j;

	printf("//----------------//\n");
	printf("//     TOPICOS    //\n");
	printf("//----------------//\n\n");

	if((f = fopen("topics.txt","r")) == NULL) {
		printf("Nao existem topicos.\n");
		sleep(1);
		system("clear");
		menu();
	}
	else {
		while( (fgets(buf, 500, f)) != NULL) {
			char *token = strtok(buf, ";");
			printf("\t| TOPICO %s |\n", token);
			j=0;
			

		    // Keep printing tokens while one of the
		    // delimiters present in str[].
		    while (token != NULL) {
		    	switch(j) {
		    		case 0: 
		    			break;
		    		case 1:	printf("\tDescricao: %s\n", token);
		    			break;
		    		case 2:	printf("\tMAX de mensagens: %s\n", token);
		    			break;
		    		case 3:	printf("\tSubscricoes: %s\n\n", token);
		    			break;
		    	}
		    	
		        //printf("%s\n", token);
		        token = strtok(NULL, ";");
		        j++;
		    }
		}
	}
	fclose(f);
}

/**** All topics can be edited in this function **/
void manageTopics() {
	showTopics();
	int op, top, id, j;
	char topic[500];
	char isAdmin;

	printf("//  ---OPCOES---  //\n");
	printf("\t( 1 ) Ver Mensagens\n");
	printf("\t( 2 ) Editar\n");
	printf("\t( 3 ) Remover\n");
	printf("\t( 4 ) Voltar\n");
	printf("PS: NAO INSIRA CARACTERES. GRANDES PROBABILIDADES DE BUG\n\n");
	printf("*Escolha a ACAO que pretende realizar* ->");
	scanf("%d", &op);
	if(op == 4){
		system("clear");
		menu();
	}
	if (op != 1 && op != 2 && op != 3) {
		printf("\nOPCAO INVALIDA\n");
		sleep(1);
		system("clear");
		menu();
	}
	printf("*Escolha o TOPICO* ->");
	scanf("%d", &top);

	//verificar topico
	
	if(op == 1) {
		showMessages(top);
		system("clear");
		menu();
	}
	else if (op == 2) {
		char desc[250];
		int numeroMAX;

		printf("Descricao do Topico <250 caracteres> : ");
		scanf("%s", desc);
		printf("Numero MAXIMO de mensagem permitidas: ");
		scanf("%d", &numeroMAX);

		sprintf(topic, "%d;%s;%d", top, desc, numeroMAX);
	}

	char aux[500];
	char buf[500];

	FILE * f, * f2;
	f = fopen("topics.txt","r");
	f2 = fopen("topics_tmp.txt", "w");		//auxliar
	
	while( (fgets(buf, 500, f)) != NULL) {
		char *token = strtok(buf, ";");
		int subs;
		id = atoi(token);
		strcpy(aux,token);

	    // Keep printing tokens while one of the
	    // delimiters present in buf[].
	    while ((token = strtok(NULL, ";")) != NULL) {
	    	//token = strtok(NULL, ";");
	        strcat(aux,";");
        	strcat(aux,token);
        	subs = atoi(token);
	    }

		if( op == 2 ){
			if( id == top ){	
				fprintf(f2, "%s;%d\n", topic,subs);
				printf("\n\n :)   --Topico %d Editado!--  \n",id);
			}
			else    			fprintf(f2,"%s",aux);
		}
		else {
			if (id != top )	fprintf(f2,"%s",aux);
			else printf("\n\n :)   --Topico %d Removido!--  \n",id);
		}
	}
	fclose(f);
	fclose(f2);

	j=remove("topics.txt");
	j=rename("topics_tmp.txt", "topics.txt");

	sleep(1);
	system("clear");
	menu();
}

/**** Show all messages published in topic **/
void showMessages(int topic) {
	FILE *f;
	char file[20];
	char buf[500];
	char aux[500];
	int j=0, mensagens=0;

	sprintf(file, "messages%d.txt",topic);
	if ( (f=fopen(file,"r")) == NULL){
		printf(":(  ---Nao existem mensagens no topico %d---", topic);
		sleep(1);
		system("clear");
		manageTopics();
	}
	else {
		while(fgets(buf,500,f) != NULL){
			char *token = strtok(buf, ";");
			strcpy(aux,token);
			printf("-------------------------------------------------------------------------------\n");
			printf("User: %s\n", aux);

		    // Keep printing tokens while one of the
		    // delimiters present in buf[].
		    while (token != NULL) {
	        	strcpy(aux,token);
	        	if(j == 1) {
	        		j=2;
	        		printf("Likes: %s\n", aux);
	        	} else if (j == 2) {
	        		printf("Data: %s\n", aux);
	        	}   
	        	else {
	        		j=1;
	        		printf("Mensagem: %s\n", aux);
	        	}			
	        	
		        token = strtok(NULL, ";");
		    }
		    mensagens++;
		}

		if(mensagens == 0)	printf("\n:(    --Não existem mensagens para mostrar...--\n");
		else 				printf("NUMERO DE MENSAGENS: %d", mensagens);
	}
	printf("\nEnter para voltar...");
	system("break");
}

/**** Touch of maths **/
void stats() {

}

void menu() {
	int op;
	system("clear");
	printf("//-----------------//\n");
	printf("//       MENU      //\n");
	printf("//-----------------//\n\n");

	printf("( 1 ) Criar novo Utilizador\n");
	printf("( 2 ) Validar pedidos de registo de utilizador\n");
	printf("( 3 ) Gerir utilizadores existentes\n");
	printf("( 4 ) Criar novo Topico\n");
	printf("( 5 ) Gerir Topicos existentes\n");
	printf("( 6 ) Ver Estatisticas\n");
	printf("( 7 ) Logout\n");
	printf("PS: NAO INSIRA CARACTERES. GRANDES PROBABILIDADES DE BUG\n\n");	
	scanf("%d", &op);
	
	switch(op) {
		case 1: newUser();
				break;
		case 2: validateUsers();
				break;
		case 3: manageUsers();
				break;
		case 4: newTopic();
				break;
		case 5: manageTopics();
				break;
		case 6: //stats();
				break;
		case 7:	logout();
				break;
		default: printf("\n\n:(   --OPCAO INVALIDA--\n"); 
				 sleep(1);
				 system("clear");
				 menu();
				 break;
	}
}

/**** Access options of Admin **/
void logout() {
	system("clear");
	login();
}