//���ڿͻ��˳�����ֱ��ƴ��GET����ͷ�����ͳ�ȥ����ͷ
//����3.c���� 
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//#define PORT 8900

void print_usage(char * cmd)
{
	fprintf(stderr," %s usage:\n",cmd);
	fprintf(stderr,"%s IP_Addr [port]\n",cmd);

}

//char gethost(){
//	char host[50];
//	char query2[50];
//	printf("what do you want:\n");
//	fgets(host,50,stdin);
//	char *tmp = NULL;
//	if ((tmp = strstr(host, "\n")))
//	{
//        *tmp = '\0';
//	}
//	strcpy(query2,host);
//	
//	char query[5] = "\r\n";
//	char query1[30] = "Host: ";
//	strcat(query1, query2);
//    strcat(query1, query);
//    
//    char L1[300] = "GET / HTTP/1.0\r\n";
//    char L2[50];
//    strcpy(L2,query1);
//    char L3[50] = "Accept:*/*\r\n";
//    char L4[80] = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)\r\n";
//    char L5[30] = "Accept-Language:zh-cn\r\n";
//	strcat(L1, L2);
//    strcat(L1, L3);
//    strcat(L1, L4);
//    strcat(L1, L5);
//    strcat(L1, query);
////    printf("all is\n%s", L1);
//    //\r��ʾ�س���\n��ʾ����  
//    //������Щ��Ϣ��Ӧ���൱�ڷ�����һ��GET��������socket������get����  
////    const char query[] =  
////        "GET /images/search.png HTTP/1.1\r\n"  
////        "Host: www.scu.edu.cn\r\n"
////    	"Accept:*/*\r\n"
////    	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)\r\n"
////    	"Accept-Language:zh-cn\r\n"  
////        "\r\n";  
//    char hostname[50];
//    strcpy(hostname,host);
//    return hostname;
//}

int main(int argc,char** argv)
{
	struct sockaddr_in server;//ֻ��һ��server 
	int ret;
	int len;
	int port;
	int sockfd;
	int sendnum;
	int recvnum;
//	char send_buf[500];
	const char *send_buf;
	char recv_buf[12048];

	if ((2>argc)|| (argc >3))
	{
		print_usage(argv[0]);
		exit(1);
	}

    if (3==argc) 
    {
		port = atoi(argv[2]);
    }
	
//	send_buf = (char)gethost(); 
	char host[50];
	char query2[50];
	printf("what do you want:\n");
	fgets(host,50,stdin);
	char *tmp = NULL;
	if ((tmp = strstr(host, "\n")))
	{
        *tmp = '\0';
	}
	strcpy(query2,host);
	
	char query[5] = "\r\n";
	char query1[50] = "Host: ";
	strcat(query1, query2);
    strcat(query1, query);
    
    char L1[500] = "GET / HTTP/1.0\r\n";
    char L2[50];
    strcpy(L2,query1);
    char L3[50] = "Accept:*/*\r\n";
    char L4[80] = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)\r\n";
    char L5[30] = "Accept-Language:zh-cn\r\n";
	strcat(L1, L2);
    strcat(L1, L3);
    strcat(L1, L4);
    strcat(L1, L5);
    strcat(L1, query);
//    printf("all is\n%s", L1);
    //\r��ʾ�س���\n��ʾ����  
    //������Щ��Ϣ��Ӧ���൱�ڷ�����һ��GET��������socket������get����  
//    const char query[] =  
//        "GET /images/search.png HTTP/1.1\r\n"  
//        "Host: www.scu.edu.cn\r\n"
//    	"Accept:*/*\r\n"
//    	"User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.7.6)\r\n"
//    	"Accept-Language:zh-cn\r\n"  
//        "\r\n";  
//    char hostname[50];
//    strcpy(send_buf,L1);
	send_buf = L1;
	printf("your message is\n%s\n", send_buf);
	
    if (-1==(sockfd=socket(AF_INET,SOCK_STREAM,0))) //�����׽���sockfd 
	{
		perror("can not create socket\n");
		exit(1);
	}

	memset(&server,0,sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);//argv[1]ΪҪ���ӵķ�������ip��ַ 
	server.sin_port = htons(port);

	if (0>(ret=connect(sockfd,(struct sockaddr*)&server,sizeof(struct sockaddr)))) //ret�����׽��ֺ�server 
	{
		perror("connect error");
		close(sockfd);
		exit(1);

	}

	//memset(send_buf,0,2048);
	//memset(recv_buf,0,2048);
	//Ҫ��whileѭ�� 
	while(1){
//		printf("what website do you want to get:\n");
	//gets(send_buf);
//		fgets(send_buf,2048,stdin); //�ŵ�send_buf��

        #ifdef DEBUG
		printf("Your message is\n%s\n",send_buf);
  	#endif 

	//sprintf(send_buf,"i am lg,thank for your servering\n");

		if (0>(len=send(sockfd,send_buf,strlen(send_buf),0)))
		{
			perror("send data error\n");
			close(sockfd);
			exit(1);

		}
	
//		ssize_t L = read(sockfd,rec_buf,sizeof(recv_buf));
//		if (L == 0) // 
//        {
//            printf("read done\n");
//            break;
//        } 
		
		if (0>(len=recv(sockfd,recv_buf,12048,0)))
		{
			perror("recv data error\n");
			close(sockfd);
			exit(1);
		}
		
		recv_buf[len]='\0';
		printf("the message from the server is:%s\n",recv_buf);
	}

	close(sockfd);

}






