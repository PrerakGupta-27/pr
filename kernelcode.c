#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

#define SOCKET_NAME "mhrydv.socket"
// #define BUFFER_SIZE 10

char Choices[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char array[51][12];

void generator(){
    srand(time(NULL));
    for(int i=0;i<250;i++){
        array[i] = Choices[rand() % 52];
    }
}

void getRandStr() {        
    srand (time(NULL));                            
    for (int j = 0; j <= 50; j++) {
        array[j][0] = j;
    }
    
    for(int i = 0; i <= 50; i++) {
		for(int j = 1; j <= 10; j++) {
			array[i][j] = rand() % 26 + 65;
		}
	}
}


int main(int argc, char* argv[]) {

	getRandStr();
    int l=0;
    for(int i=0;i<=50;i++){
        for(int j=0;j<12;j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }

	struct sockaddr_un addr;
	int ret;
	int data_socket;
	char buffer[100];

	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	memset(&addr, 0, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
	ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));


	if(argc > 1) {
		strncpy(buffer, "DOWN", sizeof("DOWN"));
		write(data_socket, buffer, sizeof(buffer));
		close(data_socket);
		exit(EXIT_SUCCESS);
	}
	else {
		int lastIdx = 1;int r=1;
		int b=0;
		int a=0;
		while(r) {

			int k=0;
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					buffer[k++]=array[a++];
				}
				buffer[k++]='\n';
			}

			printf("Sent string from %d to %d \n",b,b+5);

        	ret = write(data_socket, buffer, strlen(buffer) + 1);
        	// memset(buffer, 0, 100);

			//Reading Acknowledgements
			ret = read(data_socket, buffer, sizeof(buffer));

			buffer[sizeof(buffer) - 1] = 0;
			int finalIdx = atoi(buffer);
			
			printf("MAX ID SENT BACK BY SERVER = %s\n\n", buffer);
			if(finalIdx == 50) {
				printf("Successfully sent all Strings\n");
				strncpy(buffer, "DOWN", sizeof("DOWN"));
				write(data_socket, buffer, sizeof(buffer));
				close(data_socket);
				exit(EXIT_SUCCESS);
				r=0;
			
			}
			else {
				lastIdx = finalIdx + 1;
			}
			b+=5;
		}
	}
}
