#include <stdio.h>
#include <sys/stat.h>  //获得文件的属性，它可以返回一个结构，里面包含文件全部属性
#include <fcntl.h>        //设备驱动程序接口是由结构说明，它定义在fcntl.h中
#include <sys/types.h> //类型 clock_t,dev_t,off_t,ptrdiff,size_t,ssize_t,time_t

void main(void)
{
      int fd, num;
  
      fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR); 
      if (fd != -1 ){

            read(fd, &num, sizeof(int));
            printf("The globalvar is %d\n", num);

            printf("Please input the num written to globalvar\n");
            scanf("%d", &num);
            write(fd, &num, sizeof(int));
     
            read(fd, &num, sizeof(int));
            printf("The globalvar is %d\n", num);
   
            close(fd);
      }else{
            printf("Device open failure\n");
      }
}