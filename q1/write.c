#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int8_t write_buf[50];

int main()
{
	int fd = 0;

	fd = open("/dev/q1_dev", O_RDWR);
	if(fd < 0)
	{
                printf("Cannot open device file...\n");
                return 0;
        }
	printf("Enter the string to write into driver :");
        scanf("  %[^\t\n]s", write_buf);

        write(fd, write_buf, strlen(write_buf)+1);

	close(fd);

	return 0;
}

