#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#define MESSAGE_SIZE 256

struct Message{
	long message_type;
	int sender_client_id;
	int recevier_client_id;
	char message[MESSAGE_SIZE];
};

void* send_msg_handler(void *arg){

	key_t key ;	
	key = ftok("send", 'a');
	int id = msgget(key, IPC_CREAT | 0666);
	int *argv = (int *) arg;

	char tmp;

	while (1){
		struct Message *msg = malloc(sizeof(struct Message));
		printf("Please enter the receiver id (it must be integer): ");
		scanf("%d", &(msg->recevier_client_id));
		scanf("%c", &tmp);

		msg->sender_client_id = *argv;

		printf("Please enter your message: ");
		fgets(msg->message, MESSAGE_SIZE, stdin);

		msg->message_type = 2;

		msgsnd(id, msg, sizeof(struct Message), 0);
		free(msg);

		sleep(2);
	}
}

void* receive_msg_handler(void *arg){
	key_t key;	
	key = ftok("receive", 'b');
	int id = msgget(key, IPC_CREAT | 0666);
	int *argv = (int *) arg;

	while (1){
		struct Message *msg = malloc(sizeof(struct Message));

		msgrcv(id, msg, sizeof(struct Message), 3, 0);
		if (msg->recevier_client_id == *argv && msg->message_type == 3)
		{
			printf("\n-->>From %d = %s\n", msg->sender_client_id, msg->message);
		}
		free(msg);
	}
}

int main(int argc, char **argv){
	if(argc != 2){
		printf("Wrong usage!");
		return 1;
	}

	int client_id = atoi(argv[1]);

	struct Message *msg = malloc(sizeof(struct Message));
	strcpy(msg->message, argv[1]);
	msg->message_type = 1;
	
	key_t key;	
	key = ftok("progfile", 65);
	int id = msgget(key, IPC_CREAT | 0666);

	msgsnd(id, msg, sizeof(struct Message), 0);

	free(msg);

	pthread_t send_msg_thread;
  	if(pthread_create(&send_msg_thread, NULL, send_msg_handler, (void *) &client_id) != 0){
		printf("ERROR: pthread\n");
    	return EXIT_FAILURE;
	}

	pthread_t recv_msg_thread;
  	if(pthread_create(&recv_msg_thread, NULL, receive_msg_handler, (void *) &client_id) != 0){
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}
	
	pthread_join(send_msg_thread, NULL);
	pthread_join(recv_msg_thread, NULL);

	return 0;
}