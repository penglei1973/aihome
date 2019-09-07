#include<stdio.h>      /*��׼�����������*/
#include<stdlib.h>     /*��׼�����ⶨ��*/
#include<unistd.h>     /*Unix ��׼��������*/
#include<sys/types.h> 
#include<sys/stat.h>   
#include<fcntl.h>      /*�ļ����ƶ���*/
#include<termios.h>    /*PPSIX �ն˿��ƶ���*/
#include<errno.h>      /*����Ŷ���*/
#include<string.h>

//�궨��
#define FALSE  0
#define TRUE   1

/*******************************************************************
 * ����    �� UART0_Open
 * ����    �� �򿪴��ڲ����ش����豸�ļ�����
 * ��ڲ����� fd    :�ļ�������     port :���ں�(ttyS0,ttyS1,ttyS2)
 * ���ڲ����� ��ȷ����Ϊ1�����󷵻�Ϊ0
 *******************************************************************/
int uart_open(char * serial_port) 
{
	int fd;

	fd = open(serial_port, O_RDWR|O_NOCTTY | O_NDELAY);
	if (FALSE == fd){
		perror("Can't Open Serial Port");
		return(FALSE);
	}

	//�ָ�����Ϊ����״̬                               
	if(fcntl(fd, F_SETFL, 0) < 0){
		printf("fcntl failed!\n");
		return(FALSE);
	}else{
		printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
	}

#if 0
	//�����Ƿ�Ϊ�ն��豸    
	if(0 == isatty(STDIN_FILENO)){
		printf("standard input is not a terminal device\n");
		return(FALSE);
	}else{
		printf("isatty success!\n");
	}   

	printf("fd->open=%d\n",fd);
#endif	
    return fd;
}

/*****************************************************************************
 * ����    �� uart_close
 * ����    �� �رմ��ڲ����ش����豸�ļ�����
 * ��ڲ����� fd :�ļ������� port :���ں�(ttyS0,ttyS1,ttyS2,ttyUSB0,...)
 * ���ڲ����� void
 *****************************************************************************/
void uart_close(int fd)
{
   close(fd);
}

/************************************************************************************
 * ����    ��uart_set
 * ����    �����ô�������λ��ֹͣλ��Ч��λ
 * ��ڲ�����
 * @fd         �����ļ�������
 * @speed      ���ڲ�����
 * @flow_ctrl  ����������
 *             0:������
 *             1:Ӳ������
 *             2:�������
 *
 * @databits   ����λ   ȡֵΪ 7 ����8
 * @stopbits   ֹͣλ   ȡֵΪ 1 ����2
 * @parity     Ч������ ȡֵΪN,E,O,,S
 *���ڲ����� 
 *��ȷ����Ϊ1�����󷵻�Ϊ0
 *************************************************************************************/
int uart_init(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{

	int   i;
	int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};
	int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};

	struct termios options;

	/*
	 * tcgetattr(fd,&options)�õ���fdָ��������ز�����
	 * �������Ǳ�����options,�ú��������Բ��������Ƿ���ȷ���ô����Ƿ���õȡ�
	 * �����óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1.
	 */
	if(tcgetattr(fd,&options)  !=  0){
		perror("SetupSerial 1");    
		return(FALSE); 
	}

	//���ô������벨���ʺ����������
	for (i= 0; i < sizeof(speed_arr)/sizeof(int);  i++){
		if(speed == name_arr[i]){             
			cfsetispeed(&options, speed_arr[i]); 
			cfsetospeed(&options, speed_arr[i]);
			break;
		}
	}

	if(i == sizeof(speed_arr)/sizeof(int)){
		printf("Error,Baudrate %d not support!\n",speed);
		return FALSE;
	}

	//�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���
	options.c_cflag |= CLOCAL;
	//�޸Ŀ���ģʽ��ʹ���ܹ��Ӵ����ж�ȡ��������
	options.c_cflag |= CREAD;

	//��������������
	switch(flow_ctrl){
	case 0 ://��ʹ��������
		options.c_cflag &= ~CRTSCTS;
		break;   
	case 1 ://ʹ��Ӳ��������
		options.c_cflag |= CRTSCTS;
		break;
	case 2 ://ʹ�����������
		options.c_cflag |= IXON | IXOFF | IXANY;
		break;
	}

	//��������λ
	//����������־λ
	options.c_cflag &= ~CSIZE;
	switch (databits){  
	case 5    :
		options.c_cflag |= CS5;
		break;
	case 6    :
		options.c_cflag |= CS6;
		break;
	case 7    :    
		options.c_cflag |= CS7;
		break;
	case 8:    
		options.c_cflag |= CS8;
		break;  
	default:   
		fprintf(stderr,"Unsupported data size\n");
		return (FALSE); 
	}

	//����У��λ
	switch (parity){  
	case 'n':
	case 'N': //����żУ��λ��
		options.c_cflag &= ~PARENB; 
		options.c_iflag &= ~INPCK;    
		break; 
	case 'o':  
	case 'O'://����Ϊ��У��    
		options.c_cflag |= (PARODD | PARENB); 
		options.c_iflag |= INPCK;             
		break; 
	case 'e': 
	case 'E'://����ΪżУ��  
		options.c_cflag |= PARENB;       
		options.c_cflag &= ~PARODD;       
		options.c_iflag |= INPCK;      
		break;
	case 's':
	case 'S': //����Ϊ�ո� 
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break; 
	default:  
		fprintf(stderr,"Unsupported parity\n");    
		return (FALSE); 
	} 

	// ����ֹͣλ 
	switch (stopbits){  
	case 1:   
		options.c_cflag &= ~CSTOPB; break; 
	case 2:   
		options.c_cflag |= CSTOPB; break;
	default:   
		fprintf(stderr,"Unsupported stop bits\n"); 
		return (FALSE);
	}

	//�޸����ģʽ��ԭʼ�������
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//�Ҽӵ�
	//options.c_lflag &= ~(ISIG | ICANON);
	options.c_iflag &= ~(ICRNL | IGNCR |IXON); 

	//���õȴ�ʱ�����С�����ַ�
	options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */  
	options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */

	//�����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���
	tcflush(fd,TCIFLUSH);

	//�������� (���޸ĺ��termios�������õ������У�
	if (tcsetattr(fd,TCSANOW,&options) != 0)  {
		perror("com set error!\n");  
		return (FALSE); 
	}

	return (TRUE); 
}

/***********************************************************************************
 * ����    �� uart_recv
 * ����    �� ���մ�������
 * ��ڲ�����        
 * @fd          �ļ�������    
 * @rcv_buf     ���մ��������ݴ���rcv_buf��������
 * @data_len    һ֡���ݵĳ���
 * @time_out    ��ʱʱ��,��λΪ��
 * ���ڲ�����        
 * ��ȷ����Ϊ1�����󷵻�Ϊ0
 **********************************************************************************/
int uart_recv(int fd, char *rcv_buf,int data_len,struct timeval *timeout)
{
	int count = 0;
	int len = 0,ret;
	fd_set fs_read;

    FD_ZERO(&fs_read);
    FD_SET(fd,&fs_read);

    //ʹ��selectʵ�ִ��ڵĶ�·ͨ��
    ret = select(fd+1,&fs_read,NULL,NULL,timeout);
    if(ret == -1){
        printf("fail to select : %s\n",strerror(errno));
        return TRUE;
    }else if(ret){
        len = read(fd, rcv_buf, data_len);
        return TRUE;
    }else if (ret == 0){
        printf("Uart recv timeout!\n");
        return FALSE;
    }

    /*
	while(count < data_len){
		FD_ZERO(&fs_read);
		FD_SET(fd,&fs_read);

		//ʹ��selectʵ�ִ��ڵĶ�·ͨ��
		ret = select(fd+1,&fs_read,NULL,NULL,timeout);
		if(ret == -1){
			printf("fail to select : %s\n",strerror(errno));
			break;
		}else if(ret){
			len = read(fd,rcv_buf + count,data_len - count);
			count += len;
		}else if (ret == 0){
			printf("Uart recv timeout!\n");
			break;
		}
	}
    */

	//return ret;
}

/********************************************************************
 * ����    ��  uart_send
 * ����    ��  ��������
 * ��ڲ�����        
 * @fd          �ļ�������    
 * @send_buf    ��Ŵ��ڷ�������
 * @data_len    һ֡���ݵĸ���
 * ���ڲ�����        
 * ��ȷ����Ϊ1�����󷵻�Ϊ0
 *******************************************************************/
int uart_send(int fd, char *send_buf,int data_len)
{
	int len = 0;

	len = write(fd,send_buf,data_len);
	if (len == data_len ){
		return len;
	}else{
		tcflush(fd,TCOFLUSH);
		return FALSE;
	}
}
