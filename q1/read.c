#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int8_t read_buf[50];

int main()
{
        int fd = 0;

        fd = open("/dev/q1_dev", O_RDWR);
        if(fd < 0)
        {
                printf("Cannot open device file...\n");
                return 0;
        }
        printf("Data Reading ...");
        
	read(fd, read_buf, 50);
       	
	printf("Data: %s\n\n", read_buf);

        close(fd);

        return 0;
}
