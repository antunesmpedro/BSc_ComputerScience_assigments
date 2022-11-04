#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

char userLogged[20];
int admin = 0;

void menu();
void login();
int loginCheck(char *line);
void showTopics();
void showMessagesOfTopic(int topicID);
int topicCheck(int topicID);
int subscribeCheck(int topicID);
void searchActiveTopics();
void feed();
void account();
void newSubscribe();
void post();
void logout();

int main() {
	FILE *f;
	f = fopen("logins.txt","r");
	if ( !f ){
		printf("ERRO\n");
		exit(0);
	}
	fclose(f);
	login();
	return 0;
}



void login() {
	int op, flag1, flag2;
	char username[50];
	char password[50];
	char *pointer;

	printf("//-----------------//\n");
	printf("//  CLIENTE LOGIN  //\n");
	printf("//-----------------//\n\n");

	printf("1) Login - autenticacao\n");
	printf("2) Registo - Criar novo utilizador\n");
	printf("3) Sair\n");	
	scanf("%d", &op);

	if( op==3 )	exit(0);
	else if( op==1 ) {
		

		printf("\nUtilizador: ");
		scanf("%s", username);
		pointer = getpass("Password: ");
		strcpy(password,pointer);
		
		char user_pass1[100];
		char user_pass2[100];
		strcpy(user_pass1,username);
		strcat(user_pass1,";");
		strcat(user_pass1,password);
		strcat(user_pass1,";");
		strcpy(user_pass2,user_pass1);
		strcat(user_pass1,"u");
		strcat(user_pass2,"a");


		if( (flag1 = loginCheck(user_pass1) == 0) && (flag2 = loginCheck(user_pass2) == 0) ) {
			printf("\n\n:(   --LOGIN INVALIDO--\n");
			strcpy(userLogged,"");
			sleep(1);
			system("clear");
			login();
		}
		else if(flag1 == -1 || flag2 == -1) {
			printf("\n\n:(   --NAO EXISTEM UTILIZADORES--");
			strcpy(userLogged,"");
			sleep(2);
			exit(0);
		}else{
			strcpy(userLogged,username);
			system("clear");
			menu();
		}
	}
	else if( op==2) {
		char nome[50];
		char contato[9];
		char email[50];
		char dataNascimento[10];
		strcpy(userLogged,"");

		printf("\n\n :) --NOVO UTILIZADOR--\n");
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
		scanf("%s", dataNascimento);

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
		strcat(user, ";tmp");

		FILE *f;

		f = fopen("users.txt", "a");
		fprintf(f, "%s\n", user);
		fclose(f);

		printf("\n\n:)   --Registo a espera de ser aceite!--");
		sleep(2);
		exit(0);
	}else {
		if(op!=3)		printf("\n\n:(   --OPCAO INVALIDA--\n");
		exit(0);
	}
}

int loginCheck(char *line) {
	FILE *f, *f2;
	char buf[500];
	char aux[500];
	int flag=0,j=1;

		f = fopen("logins.txt","r");
		f2 = fopen("logins_tmp.txt", "w");

		while(fgets(buf, 500, f) != NULL) {
			if(strstr(buf, line) != NULL) {
				j=1;
				char *token = strtok(buf, ";");
				strcpy(aux,token);

		    	// Keep printing tokens while one of the
		    	// delimiters present in buf[].
		    	while ((token = strtok(NULL, ";")) != NULL) {
		    		//token = strtok(NULL, ";");
		    		if ( j == 2 ) {
		    			if ( (strcmp(token,"a") == 0) || (strcmp(token,"a\n") == 0)) {	
		    				admin = 1;
		    				strcat(aux,";a");
		    			}
		    			else  {		
		    				admin = 0;
		    				strcat(aux,";u");
		    			}
		    		
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
			return 1;
		}
		else	{
			j = remove("logins_tmp.txt");
			return 0;
		}
}

void menu() {
	int op;
	int id;

	printf("//-----------------//\n");
	printf("//      MENU       //\n");
	printf("//-----------------//\n\n");

	if(admin == 1){
		printf("   | ADMIN |\n\n");
	}
	printf("( 1 ) Gestao da conta de Utilizador\n");
	printf("( 2 ) Ver Feed\n");
	printf("( 3 ) Ver Mensagens de um Topico\n");
	printf("( 4 ) Procurar Topicos mais ativos\n");
	printf("( 5 ) Subscrever Topico\n");
	printf("( 6 ) Publicar num Topico\n");
	printf("( 7 ) Gerir Lista de Subscricoes\n");
	printf("( 8 ) Ver Estatisticas\n");
	printf("( 9 ) Logout\n");	
	scanf("%d", &op);

	switch(op) {
		case 1: account();
				break;
		case 2: feed();
				break;
		case 3: showTopics();
				printf("Numero de Topico a mostrar: ");
				scanf("%d", &id);
				showMessagesOfTopic(id);
				menu();
				break;
		case 4: searchActiveTopics();
				break;
		case 5: newSubscribe();
				break;
		case 6: post();
				break;
		case 7: //subsList();
				break;
		case 8: //stats();
				break;
		case 9: logout();
				break;
		default: printf("\n\n:(   --OPCAO INVALIDA--"); 
				 sleep(1);
				 system("clear");
				 menu();
				 break;
	}
}

//1
void account() {
	FILE *f;
	char buf[500];
	int i=0, j=0, op;

	f = fopen("users.txt","r"); 
	while(fgets(buf, 500, f) != NULL) {
		char *token = strtok(buf, ";");
		i++;

		if(strcmp(token, userLogged) == 0) {
			j=0;
		  	printf("\t| UTILIZADOR %d |\n",i);
		  	printf("\tNome: %s\n", token);
		    // Keep printing tokens while one of the
		    // delimiters present in str[].
		    while ( (token = strtok(NULL, ";")) != NULL) {
		    	switch(j) {
		    		case 0:	printf("\tContato: ");
		    			break;
		    		case 1: printf("\tUsername: ");
		    			break;
		    		case 2:	printf("\tPassword: ");
		    			break;
		    		case 3:	printf("\tEmail: ");
		    			break;
		    		case 4:	printf("\tData de Nascimento: ");
		    			break;
		    	}
		        printf("%s\n", token);
		        j++;
		    }
		}
	}
	fclose(f);
	printf("|-----------------------------------------------------\n");
	printf(" ? info - ALTERAR SENHA ( 1 ) - ALTERAR EMAIL ( 2 ) - APAGAR CONTA ( 3 ) ---?\n");
	printf("   BACK - ( 4 )\n");  //erro nos ficheiro em alterar dados *checkar
	scanf("%d", &op);	

	if(op == 1 || op == 2 || op == 3) {
		FILE *f1, *f2, *f3, *f4;
		char aux[500];
		char *pointer;

		f1 = fopen("users.txt", "r");
		f2 = fopen("users_tmp.txt", "w");

		while (fgets(buf, 500, f1) != NULL){
			char *token = strtok(buf, ";");

			if(strcmp(token, userLogged) == 0) {
				j=0;
				strcpy(aux, token);

				if(op != 3) {
			    	// Keep printing tokens while one of the
			    	// delimiters present in buf[].
			    	while ( (token = strtok(NULL, ";")) != NULL) {
			    		j++;

			    		if(op == 1 && j == 3){
			    			printf("\n");
							pointer = getpass("Nova senha : ");
							strcat(aux,";");
							strcat(aux, pointer);
							printf(":)     --Nova senha guardada--\n");
			    		} else if( op == 2 && j == 4){
			    			char email[20];
			    			printf("Novo email: ");
			    			scanf("%s", email);
			    			strcat(aux,";");
			    			strcat(aux, email);
			    			printf(":)     --Novo email guardado--\n");
			    		} else {
			    			strcat(aux,";");
			    			strcat(aux,token);
			    		}
			    	}
			    	//printf("USER: \n");
			    	//printf("%s",aux);
			    	fprintf(f2,"%s",aux);
			    }
			    else	printf(":)     ---Conta APAGADA !!---\n");
			}
			else{
				printf("%s",buf);
				fprintf(f2,"%s",buf);
			}				
		}
		fclose(f1);
		fclose(f2);

		j = remove("users.txt");
		j = rename("users_tmp.txt", "users.txt");
		
		// registo no ficheiro login
		if(op != 2) {
			f3 = fopen("logins.txt", "r");
			f4 = fopen("logins_tmp.txt", "w");

			while (fgets(buf, 500, f3) != NULL){
				char *token = strtok(buf, ";");
				strcpy(aux, token);

				if(strcmp(token, userLogged) == 0) {
					j=0;

					if ( op != 3) {
			    		// Keep printing tokens while one of the
			    		// delimiters present in str[].
			    		while ( (token = strtok(NULL, ";")) != NULL) {
			    			j++;
			    			//printf("ENTREI : %s",token);
			    		
			    			if( j == 1 ){
								strcat(aux,";");
								strcat(aux, pointer);
			    			} else {
			    				strcat(aux,";");
			    				strcat(aux,token);
			    			}
			    		}
			    		//printf("LOGIN: %s\n",aux);
			    		fprintf(f4,"%s",aux);
			    	}
				}
				else		fprintf(f4,"%s",buf);
			}
			fclose(f3);
			fclose(f4);

			j = remove("logins.txt");
			j = rename("logins_tmp.txt", "logins.txt");
			
		}

		sleep(1);
		system("clear");
		account();
	}
	else if( op == 4){
		system("clear");
		menu();
	}
	else	{
		printf("ERRO.\n");
		exit(0);
	}
}

/**** Show all topics registered **/
void showTopics() {
	FILE * f;
	char buf[500];
	int j;

	printf("//----------------//\n");
	printf("//     TOPICOS    //\n");
	printf("//----------------//\n\n");

	f = fopen("topics.txt","r");
	if( !f ) {
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

//2
void feed() {
	FILE *f;
	char buf[500];
	int count;

	f = fopen("topics.txt","r");
	if( !f ) {
		printf("Nao existem topicos.\n");
		sleep(1);
		system("clear");
		menu();
	}
	else{
		count = 0;
		while( (fgets(buf, 500, f)) != NULL) {
			char *token = strtok(buf, ";");
			if(subscribeCheck(atoi(token)) == 0){
				printf("\t| TOPICO %s |\n", token);
				showMessagesOfTopic(atoi(token));
				count++;
			}
		}
	}

	if(count == 0){
		printf("Nao existem topicos subscritos :( \n");
		sleep(1);
		system("clear");
		menu();
	}
}

//3
void showMessagesOfTopic(int topicID) {
	FILE *f;
	char file[20];
	char buf[500];
	char aux[500];
	int j=0, mensagens=0;

	sprintf(file, "messages%d.txt",topicID);
	f=fopen(file,"r");
	if ( !f ) {
		printf(":(  ---Nao existem mensagens no topico %d---\n", topicID);
	}
	else {
		while(fgets(buf,500,f) != NULL){
			char *token = strtok(buf, ";");
			strcpy(aux,token);
			printf("-------------------------------------------------------------------------------\n");
			printf("Mensagem %d: %s\n",mensagens, aux);
			j=0;
		    // Keep printing tokens while one of the
		    // delimiters present in buf[].
		    while ( (token = strtok(NULL, ";")) != NULL) {
	        	if(j == 1) {
	        		printf("User: %s\n", token);
	        	}
	        	if (j == 2) {
	        		printf("User: %s\n", token);
	        	} 
	        	if(j==3){
	        		printf("Data: %s\n", token);
	        	}
	        	if( j == 0) {
	        		j=1;
	        		printf("Likes: %d\n", atoi(token));
	        	}			
	        	j++;
		    }
		    mensagens++;
		}
		printf("NUMERO DE MENSAGENS: %d\n", mensagens);
		/* bug
		if(mensagens>0){
			int msg;
			printf("Gostar de uma mensagem (numero) | ( 0 ) - nenhum gosto: ");
			scanf("%d",&msg);

			if(msg>0) {
				FILE *f4, *f5;
				char str1[20], str2[20];
				char buf[500];
				char aux[500];

				sprintf(str1, "messages%d.txt", topicID);
				sprintf(str2, "messages%d_tmp.txt", topicID);
				f4 = fopen(str1,"r");
				f5 = fopen(str2, "w");
				int i=1;
				while(fgets(buf,500, f4) != NULL) {
					char *token = strtok(buf,";");
					strcpy(aux,token);
					int j=0;
					if(i == msg){
						printf("ENTREI\n");
						while( (token = strtok(NULL,";")) != NULL ) {
							if(j==0){
								sprintf(aux, "%s;%d", aux, atoi(token)+1);
								//strcat(aux,  itoa ( atoi( token)+1 ) );
							}
							else	{
								strcat(aux,";");
								strcat(aux, token);
							} 
							j++;
						}
						fprintf(f5,"%s",aux);
					}
					else	fprintf(f5,"%s",buf);
					i++;
				}
				fclose(f4);
				fclose(f5);

				msg=remove(str1);
				msg=rename(str2,str1);
			}		
		}
		*/
	}
}

//4
void searchActiveTopics() {
	int op;
	char * day_week;
	char * month;
	char *day;
	char * hour;
	char *year;

	printf("\t| Periodo de procura de mensagens |\n");
	printf("\t ( 1 ) Ultima Hora\n");
	printf("\t ( 2 ) Hoje\n");
	printf("\t ( 3 ) Esta Semana\n");
	printf("\t ( 4 ) Ultimo login\n");
	printf("PS: NAO INSIRA CARACTERES. GRANDES PROBABILIDADES DE BUG\n\n");	
	scanf("%d", &op); //\n

	
	struct tm *str_time;
	time_t  time_of_search;
  	time ( &time_of_search );
  	str_time = localtime( &time_of_search );

	str_time->tm_isdst = 1;

	if(op == 1){
		str_time->tm_hour -= 1; 
	} else if( op == 2 ) {
			str_time->tm_hour = 0;
			str_time->tm_min = 0;
			str_time->tm_sec = 0;
	} else if ( op == 3 ) {
		str_time->tm_mday -=7;
	} else if ( op == 4 ) {
		char buf[500];
		FILE *f;
		char *data;
		f=fopen("logins.txt","r");

		while( fgets(buf,500,f) != NULL ) {
			data = strtok(buf,";");

			if( strcmp(userLogged,data) == 0 ){
				data = strtok(NULL, ";");
				data = strtok(NULL, ";");
				data = strtok(NULL, ";");
			}
		}
		fclose(f);

		day_week = strtok(data," ");
		month = strtok(NULL," ");
		day = strtok(NULL," ");
		hour = strtok(NULL," ");
		year =  strtok(NULL," ");

		str_time->tm_mon = atoi(month);
		str_time->tm_mday = atoi(day);
		str_time->tm_hour = atoi(strtok(hour,":"));
		str_time->tm_min = atoi(strtok(NULL,":"));
		str_time->tm_sec = atoi(strtok(NULL,":"));
		str_time->tm_year = atoi(year)-1900;
	} else {
		printf(":(     --OPCAO INVALIDA--\n");
		sleep(1);
		system("clear");
		menu();
	}

	time_of_search = mktime( str_time );
	
	char buf[500], *str;
	char *data;
	int array_count[50];
	for(int i=0; i<50;i++)
		array_count[0] = 0;
	FILE *f1, *f2;
	f1 = fopen("topics.txt","r");

	/*procurar quais os topicos que tem mensagens mais recentes*/
	int i=0;
	while( fgets(buf, 500, f1) != NULL ) {
		char *token = strtok(buf,";");
		sprintf(str, "messages%d.txt", atoi(token));
		f2 = fopen(str,"r");

		while( fgets(buf,500,f2) != NULL ) {
			time_t time_of_message;
			struct tm *str_time_messages;
			str_time_messages->tm_isdst = 1;

			data = strtok(buf, ";");
			data = strtok(NULL,";");
			data = strtok(NULL,";");
			data = strtok(NULL,";");

			day_week = strtok(data," ");
			month = strtok(NULL," ");
			day = strtok(NULL," ");
			hour = strtok(NULL," ");
			year =  strtok(NULL," ");

			str_time_messages->tm_mon = atoi(month); //edit
			str_time_messages->tm_mday = atoi(day);
			str_time_messages->tm_hour = atoi(strtok(hour,":"));
			str_time_messages->tm_min = atoi(strtok(NULL,":"));
			str_time_messages->tm_sec = atoi(strtok(NULL,":"));
			str_time_messages->tm_year = atoi(year)-1900;

			time_of_message = mktime( str_time_messages );

			double seconds = difftime(time_of_message, time_of_search);
			if (seconds > 0)	array_count[i]++;
		}
		fclose(f2);
		i++;
	}
	fclose(f1);

	int max=array_count[0];
	int topicolinha = 0;
	for(int j=1; j<=i; j++){
		if( array_count[j] > max){
			max = array_count[j];
			topicolinha = j;
		}
	}

	f1=fopen("topics.txt","r");
	i=0;
	while(fgets(buf, 500, f1)){
		if(i == topicolinha){
			int id = atoi( strtok(buf,";") );
			char *desc = strtok(NULL,";");
			printf("\t| TOPICO COM MAIS MENSAGENS DESDE A DATA ESCOLHIDA | ID: %d DESCRICAO: %s\n", id, desc);
			printf("\t  MENSAGENS NOVAS: %d\n", array_count[topicolinha]);
		}
		i++;
	}
	fclose(f1);
}

//5
int topicCheck(int topicID) {
	FILE *f;
	char buf[500];
	f= fopen("topics.txt", "r");

	while( fgets(buf,500,f) != NULL ) {
		char *token = strtok(buf, ";");
		
		if( atoi(token) == topicID)	return 1;
	}

	return 0;
}

int subscribeCheck(int topicID) {
	FILE *f;
	char buf[500];

	f=fopen("users.txt","r");

	while(fgets(buf, 500, f) != NULL) {
		char *token = strtok(buf, ";");

		if(strcmp(token, userLogged) == 0) {
			while ((token = strtok(NULL, ";")) != NULL) {
				if(atoi(token) == topicID)	return 0;
			}
		}
	}

	return 1;
}
//5
void newSubscribe() {
	int topID, j;
	char buf[500];
	char aux[500];

	printf("//-------------------//\n");
	printf("//  NOVA SUBSCRICAO  //\n");
	printf("//-------------------//\n\n");
	showTopics();

	printf(" Numero de topico a subscrever: ");
	scanf("%d", &topID);

	if ( topicCheck(topID) == 0 ) {
		printf(":(         ---O Topico escolhido não existe---\n");
		sleep(1);
		system("clear");
		menu();
	}
	else if(subscribeCheck(topID) == 0){
		printf(":(         ---O Topico escolhido ja esta subscrito---\n");
		sleep(1);
		system("clear");
		menu();
	}
	else {
		FILE *f1, *f2;
		f1 = fopen("users.txt", "r");
		f2 = fopen("users_tmp.txt","w");

		while( fgets(buf,500,f1) != NULL ) {
			char *token = strtok(buf, ";");
			strcpy(aux, token);
			j=1;
			if(strcmp(token, userLogged) == 0) {
				while ((token = strtok(NULL, ";")) != NULL) {
		    		//token = strtok(NULL, ";");
		    		if(j >= 5){
		    			strcat(aux,";");
		    			strcat(aux,token);
		    			strcat(aux,";");
		    			size_t lenaux = strlen(aux);
		    			size_t lentoken = strlen(token);


		    			while ((token = strtok(NULL, ";")) != NULL) {
		    				lentoken = strlen(token);
		    				token[lentoken-1] = ';';

		    				strcat(aux,token);
							lenaux = strlen(aux);
		    			}
		    			aux[lenaux-2] = ';';
		    			aux[lenaux-1] = topID + '0';
		    			
		    			printf("%s",aux);
		    		}
		    		else{
		    			strcat(aux,";");
		    			strcat(aux,token);
		    		}
		    		j++;
		    	}
			    fprintf(f2, "%s\n", aux);
			    printf(":)    ---Subscricao feita---\n");
			}
			else fprintf(f2,"%s",buf);
		}
		fclose(f1);
		fclose(f2);

		j = remove("users.txt");
		j = rename("users_tmp.txt", "users.txt");
	

		FILE *f3,*f4;

		f3 = fopen("topics.txt","r");
		f4 = fopen("topics_tmp.txt","w");
		int i=1;
		while( (fgets(buf, 500, f3)) != NULL) {
			char *token = strtok(buf, ";");
			int subs;
			int id = atoi(token);
			strcpy(aux,token);
			int j=1;

		    // Keep printing tokens while one of the
		    // delimiters present in buf[].
		    while ((token = strtok(NULL, ";")) != NULL) {
		    	//token = strtok(NULL, ";");
	        	if(j == 3){
	        		subs = atoi(token);
	        	}
	        	else{
	        		strcat(aux,";");
	        		strcat(aux,token);
	        	}
	        	j++;
		    }

			if( id == topID ){	
					fprintf(f4, "%s;%d\n", aux,subs+1);
			}
			else    			fprintf(f4,"%s",buf);
			i++;
		}
		fclose(f3);
		fclose(f4);

		j=remove("topics.txt");
		j=rename("topics_tmp.txt", "topics.txt");

		sleep(1);
		system("clear");
		menu();
	}
}

//6
void post() {
	int id, maxMSG=0;
	char file1[20], file2[20];
	char string[250];
	char read[500];
	char buf;
	showTopics();

	FILE *f;
	char buf1[500];
	f= fopen("topics.txt", "r");
	printf("Numero do Topico a escrever : ");
	scanf("%d", &id);

	while( fgets(buf1,500,f) != NULL ) {
		char *token = strtok(buf1, ";");
		
		if( atoi(token) == id)	{
			char *aux=strtok(NULL, ";");
			maxMSG = atoi(strtok(NULL, ";"));
		}
	}
	fclose(f);

	
	sprintf(file1,"messages%d.txt",id);
	sprintf(file2,"messages%d_tmp.txt",id);

	if ( topicCheck(id) == 0 ) {
		printf(":(         ---O Topico escolhido não existe---\n");
		sleep(1);
		system("clear");
		menu();
	}
	else{
		showMessagesOfTopic(id);
		int i=0;
		printf("*INTRODUZA A SUA MENSAGEM*: ");
		buf=getchar();
		string[i] = buf;
		while( (buf = getchar()) != '\n' && i < 249){
			i++;
			string[i] = buf;
		}
		string[i+1] = '\0';

		FILE *f1, *f2, *f3;
		f1 = fopen(file1, "r");
		f2 = fopen(file2, "w");
		f3 = fopen(file1, "r");
		i=0;

		if (fgets(read, 500, f3) == NULL) {
				time_t t = time(NULL);
	    		struct tm *tm = localtime(&t);
				fprintf(f2,"%s;0;%s;%s",string, userLogged, asctime(tm));
				i=1;
		}
		else{
			while(fgets(read, 500, f1) != NULL && i<maxMSG){
				if(i=0){
					time_t t = time(NULL);
		    		struct tm *tm = localtime(&t);
					fprintf(f2,"%s;0;%s;%s",string, userLogged, asctime(tm));
				}
				else	fprintf(f2,"%s",read);
				i++;
			}
		}
		fclose(f1);
		fclose(f2);
		fclose(f3);

		i=remove(file1);
		i=rename(file2,file1);

		printf(":)   ---Mensagem guardada---\n");
		showMessagesOfTopic(id);
		sleep(2);
		system("clear");
		menu();
	}
}

void logout() {
	system("clear");
	login();
}