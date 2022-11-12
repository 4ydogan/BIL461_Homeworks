#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#define MESSAGE_SIZE 256

int clients[100];

struct Message{
	long message_type;
	int sender_client_id;
	int recevier_client_id;
	char message[MESSAGE_SIZE];
};

void handle_client(void *arg){
	
	key_t key1, key2;	
	key1 = ftok("send", 'a');
	int id1 = msgget(key1, IPC_CREAT | 0666);
	key2 = ftok("receive", 'b');
	int id2 = msgget(key2, IPC_CREAT | 0666);

	while(1){
		struct Message *msg = malloc(sizeof(struct Message));

		msgrcv(id1, msg, sizeof(struct Message), 2, 0);
		printf("%d -> %d = %s \n", msg->sender_client_id, msg->recevier_client_id, msg->message);
		if (msg->message_type == 2)
		{
			msg->message_type = 3;
			msgsnd(id2, msg, sizeof(struct Message), 0);
		}
		
		free(msg);
	}
}

int isNewClient(int client_id){
	for(int i=0; i<100; i++){
		if(clients[i] == client_id){
			return 0;
		}
	}

	return 1;
}

int main(){
	
 	pthread_t tid;
	
	key_t key;	
	key = ftok("progfile", 65);
	int id = msgget(key, IPC_CREAT | 0666);

	while(1){
		struct Message *msg = malloc(sizeof(struct Message));

		msgrcv(id, msg, sizeof(struct Message), 1, 0);

		if(isNewClient(1) && msg->message_type == 1){
			pthread_create(&tid, NULL, (void *) handle_client, NULL);
			pthread_join(tid, NULL);
		} 
		free(msg);
	}

	return 0;
}