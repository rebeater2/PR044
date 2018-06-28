/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Apr-2018 18:52:48
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "music_angle.h"
#include "main.h"
#include "music_angle_terminate.h"
#include "music_angle_emxAPI.h"
#include "music_angle_initialize.h"

/* hps includes*/ 
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#include "hps_0_arm_a9_0.h"

#include <stdio.h>
//#include "signal.h"
#include"han.h"
/* Expected System Environment */
#define SYSFS_FPGA0_STATE_PATH "/sys/class/fpga_manager/fpga0/state"
#define SYSFS_FPGA0_STATE "operating"

#define SYSFS_LWH2F_BRIDGE_NAME_PATH "/sys/class/fpga_bridge/br0/name"
#define SYSFS_LWH2F_BRIDGE_NAME "lwhps2fpga"

#define SYSFS_LWH2F_BRIDGE_STATE_PATH "/sys/class/fpga_bridge/br0/state"
#define SYSFS_LWH2F_BRIDGE_STATE "enabled"


#define PI 3.14159265
//#define LED_PIO_BASE 0xff210000
//#define LED_PIO_SPAN 16
/* Function Declarations */
static void argInit_6x8192_real_T(double result[49152]);
static void main_music_angle(void);
void pio_init(void);

volatile u_int *led_pio_ptr;
volatile u_int *sound1_pio_ptr;
volatile u_int *sound2_pio_ptr;
volatile u_int *sound3_pio_ptr;
volatile u_int *sound4_pio_ptr;
volatile u_int *sound5_pio_ptr;
volatile u_int *sound6_pio_ptr;
volatile u_int *clk_for_data_ptr;
volatile u_int *x_ptr;
volatile u_int *y_ptr;
/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc,const char *const argv[])
{

  /* Initialize the application.
     You do not need to do this more than one time. */
  music_angle_initialize();
  pio_init();
   printf("input main1\n");
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_music_angle();

  /* Terminate the application.
     You do not need to do this more than one time. */
  music_angle_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_music_angle(void)
{
  int angle_num = 0;
  int angle=0;
  int x0=461,y0=274;
  int x,y;

  int ge,shi,bai;
  int baishige;
  double r0=150;
  emxArray_real_T *est_phi;
  emxArray_real_T *est_thi;
  static double dv1[49152];
  emxInitArray_real_T(&est_phi, 1);
  emxInitArray_real_T(&est_thi, 1);
 printf("input main\n");
  /* Initialize function 'music_angle' input arguments. */
  /* Initialize function input argument 'sig'. */
  /* Call the entry-point 'music_angle'. */
  while (1)
 {
    argInit_6x8192_real_T(dv1);
	//printf("input main2\n");
    music_angle(dv1, est_phi, est_thi);
    printf("est_phi = %f est_thi=%f\n", *(est_phi->data), *(est_thi->data));
  // printf("est_thi=%f\t", *(est_thi->data));
    angle=*(est_thi->data);
    if ((angle>330)||(angle<=30))
      angle_num=0;
      else if((angle>30)&&(angle<=90))
      angle_num=1;
      else if((angle>90)&&(angle<=150))
         angle_num=2;
      else if((angle>150)&&(angle<=210))
            angle_num=3;
      else if((angle>210)&&(angle<=270))
            angle_num=4;
      else 
          angle_num=5;
      x=x0+r0*sin(angle*PI/180);
      y=y0-r0*cos(angle*PI/180);
      printf("x=%d\t y=%d\n",x,y);

      led_pio_ptr[0] = 1 << angle_num;//点亮对应的led

      ge=angle%10;
      bai=angle/100;
      shi=((angle-ge)/10)%10;
      baishige=bai*256+shi*16+ge;
      
      x_ptr[0]=x+(baishige<<10);//传送坐标
      y_ptr[0]=y;
  }

}


/* Function Definitions */

/*
 * Arguments    : double result[49152]
 * Return Type  : void
 */
static void argInit_6x8192_real_T(double result[49152])
{
  int i = 0;
 double sum[6] = {0};
  u_int32_t *buffer;
  int clk_for_data;
  unsigned int a;
 // int result[49152];
  FILE *fd;
  char str[10];
  fd = fopen("b.txt", "w");//注意之前自己定义个a.txt
   while (i < 49152) 
   {
    // printf("i=%d\n",i);
     clk_for_data=clk_for_data_ptr[0];
     //   printf("clk_for_data=%d\n",clk_for_data);
   if (clk_for_data)
     {
       a = sound6_pio_ptr[0] ;
        result[i + 0] =(int) (a & 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);	 
        sum[0]+=(result[i + 0]/8192);
      
     // printf("%f\n",result[i + 0]);

       a = sound5_pio_ptr[0] ;
        result[i + 1] = (int)(a& 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);
        sum[1]+=(result[i + 1]/8192);
      //	sprintf(str,"%f",result[i +1]); fputs(str,fd); fputs("\r\n",fd);//写换行符

       a = sound4_pio_ptr[0] ;
        result[i + 2] = (int)(a & 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);
         sum[2]+=(result[i + 2]/8192);
       //	sprintf(str,"%f",result[i + 2]); fputs(str,fd); fputs("\r\n",fd);//写换行符

       a = sound3_pio_ptr[0] ;
        result[i + 3] =(int) (a& 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);
         sum[3]+=(result[i + 3]/8192);
        //	sprintf(str,"%f",result[i + 3]); fputs(str,fd); fputs("\r\n",fd);//写换行符
			
       a = sound2_pio_ptr[0];
        result[i + 4] =(int)( a & 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);
         sum[4]+=(result[i + 4]/8192);
       //	sprintf(str,"%f",result[i + 4]); fputs(str,fd); fputs("\r\n",fd);//写换行符
				
       a = sound1_pio_ptr[0];
        result[i + 5] = (int)(a & 0x8000 ? (0 - ((~(a & 0x7fff)) & 0x7fffu) - 1) : a);
         sum[5]+=(result[i + 5]/8192);
        // 	sprintf(str,"%f",result[i + 5]); fputs(str,fd); fputs("\r\n",fd);//写换行符
       // printf("data = %d \n",result[i]);
       while (clk_for_data)
        clk_for_data=clk_for_data_ptr[0];//等待下一个时钟
       i += 6;
     }
	 result=result;
   }
   printf("sum[0]=%f\n",sum[0]);
i=0;

  while (i < 49152) 
  {
    result[i+0]-=sum[0];
	//  printf("%d\n",result[i + 0]);
     // result[n+0]*=signal[n];
    
    // result[n+1]*=signal[n];
//printf("result[i]=%f\n",result[i+0]);

        result[i+1]-=sum[1];
     //	sprintf(str,"%f",result[i + 1]); fputs(str,fd); fputs("\r\n",fd);//写换行符


    result[i+2]-=sum[2];
    // result[n+2]*=signal[n];
    // 	sprintf(str,"%f",result[i + 2]); fputs(str,fd); fputs("\r\n",fd);//写换行符


    result[i+3]-=sum[3];
    // result[n+3]*=signal[n];
     //	sprintf(str,"%f",result[i + 3]); fputs(str,fd); fputs("\r\n",fd);//写换行符
    


    result[i+4]-=sum[4];
    // result[n+4]*=signal[n];
    // 	sprintf(str,"%f",result[i + 4]); fputs(str,fd); fputs("\r\n",fd);//写换行符
   	//

    result[i+5]-=sum[5];
    // result[n+5]*=signal[n];
    //sprintf(str,"%f",result[i + 5]); fputs(str,fd); fputs("\r\n",fd);//写换行符
    // 	sprintf(str,"%f",result[i + 5]); fputs(str,fd); fputs("\r\n",fd);//写换行符
       i+=6;
  }
     fclose(fd);//关闭设备文件
  //printf("complete~");
}

void pio_init()
{
  int result;
  int sysfs_fd;
  char sysfs_str[256];
  int dev_mem_fd;
  void *mmap_addr;
  size_t mmap_length;
  int mmap_prot;
  int mmap_flags;
  int mmap_fd;
  off_t mmap_offset;
  void *mmap_ptr;

u_int32_t sound1_pio_value;
u_int32_t sound2_pio_value;
u_int32_t sound3_pio_value;
u_int32_t sound4_pio_value;
u_int32_t sound5_pio_value;
u_int32_t sound6_pio_value;
 u_int32_t led_pio_value;
 boolean_T clk_for_dada_value;
  int i;
  int j;
  printf("\nStart of program...\n\n");

  /* validate the FPGA state */
  sysfs_fd = open(SYSFS_FPGA0_STATE_PATH, O_RDONLY);
  if (sysfs_fd < 0)
    error(1, errno, "open sysfs FPGA state");
  result = read(sysfs_fd, sysfs_str, strlen(SYSFS_FPGA0_STATE));
  if (result < 0)
    error(1, errno, "read sysfs FPGA state");
  close(sysfs_fd);
  if (strncmp(SYSFS_FPGA0_STATE, sysfs_str, strlen(SYSFS_FPGA0_STATE)))
    error(1, 0, "FPGA not in operate state");

  /* validate the LWH2F bridge name */
  sysfs_fd = open(SYSFS_LWH2F_BRIDGE_NAME_PATH, O_RDONLY);
  if (sysfs_fd < 0)
    error(1, errno, "open sysfs LWH2F bridge name");
  result = read(sysfs_fd, sysfs_str, strlen(SYSFS_LWH2F_BRIDGE_NAME));
  if (result < 0)
    error(1, errno, "read sysfs LWH2F bridge name");
  close(sysfs_fd);
  if (strncmp(SYSFS_LWH2F_BRIDGE_NAME, sysfs_str,
              strlen(SYSFS_LWH2F_BRIDGE_NAME)))
    error(1, 0, "bad LWH2F bridge name");

  /* validate the LWH2F bridge state */
  sysfs_fd = open(SYSFS_LWH2F_BRIDGE_STATE_PATH, O_RDONLY);
  if (sysfs_fd < 0)
    error(1, errno, "open sysfs LWH2F bridge state");
  result = read(sysfs_fd, sysfs_str, strlen(SYSFS_LWH2F_BRIDGE_STATE));
  if (result < 0)
    error(1, errno, "read sysfs LWH2F bridge state");
  close(sysfs_fd);
  if (strncmp(SYSFS_LWH2F_BRIDGE_STATE, sysfs_str,
              strlen(SYSFS_LWH2F_BRIDGE_STATE)))
    error(1, 0, "LWH2F bridge not enabled");

  /* map the peripheral span through /dev/mem */
  dev_mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
  if (dev_mem_fd < 0)
    error(1, errno, "open /dev/mem");

  //*************************************************************************************************************************led base*/
  mmap_addr = NULL;
  mmap_length = LED_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = LED_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  led_pio_ptr = (u_int *)((u_int)mmap_ptr +
                          (LED_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  led_pio_value = led_pio_ptr[0];
  printf("LED_BASE=%x", LED_PIO_BASE);
  printf("led_pio_value address= %x", led_pio_ptr);
  led_pio_value = 0;

  printf("Initial LED PIO value: 0x%08X\n", led_pio_value);

  // for(j=0;j<8;j++)
  for (i = 0; i < 6; i++)
  {
    led_pio_ptr[0] = 1 << i;
    // printf("led =%d\n",led_pio_ptr[0]);
    usleep(225000);
  }

  /* restore the LED PIO value */
  led_pio_ptr[0] = led_pio_value;
  printf("Initial LED PIO value restored\n");
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
 result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
  if (result < 0)
    error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound6 base */
  mmap_addr = NULL;
  mmap_length = SOUND6_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND6_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound6_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND6_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound6_pio_value = sound6_pio_ptr[0];
  printf("SOUND6_PIO_BASE=%x", SOUND6_PIO_BASE);
  printf("sound6_pio_value address= %x", sound6_pio_ptr);

  printf("Initial sound6_pio_value : 0x%08X\n", sound6_pio_value);
  led_pio_ptr[0] = 1 << 6; //亮第六个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
  if (result < 0)
     error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound5 base */
  mmap_addr = NULL;
  mmap_length = SOUND5_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND5_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound5_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND5_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound5_pio_value = sound5_pio_ptr[0];
  printf("SOUND5_PIO_BASE=%x", SOUND5_PIO_BASE);
  printf("sound5_pio_value address= %x", sound5_pio_ptr);

  printf("Initial sound5_pio_value : 0x%08X\n", sound5_pio_value);
  led_pio_ptr[0] = 1 << 5; //亮第六个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
//   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 //  if (result < 0)
 //    error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound4 base */
  mmap_addr = NULL;
  mmap_length = SOUND4_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND4_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound4_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND4_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound4_pio_value = sound4_pio_ptr[0];
  printf("SOUND4_PIO_BASE=%x", SOUND4_PIO_BASE);
  printf("sound4_pio_value address= %x", sound4_pio_ptr);

  printf("Initial sound4_pio_value : 0x%08X\n", sound4_pio_value);
  led_pio_ptr[0] = 1 << 4; //亮第六个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
//   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 //  if (result < 0)
 //    error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound3 base */
  mmap_addr = NULL;
  mmap_length = SOUND3_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND3_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound3_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND3_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound3_pio_value = sound3_pio_ptr[0];
  printf("SOUND3_PIO_BASE=%x", SOUND3_PIO_BASE);
  printf("sound3_pio_value address= %x", sound3_pio_ptr);

  printf("Initial sound3_pio_value : 0x%08X\n", sound3_pio_value);
  led_pio_ptr[0] = 1 << 3; //亮第i个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
//   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 //  if (result < 0)
 //    error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound2 base */
  mmap_addr = NULL;
  mmap_length = SOUND2_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND2_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound2_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND2_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound2_pio_value = sound2_pio_ptr[0];
  printf("SOUND2_PIO_BASE=%x", SOUND2_PIO_BASE);
  printf("sound2_pio_value address= %x", sound2_pio_ptr);

  printf("Initial sound2_pio_value : 0x%08X\n", sound2_pio_value);
  led_pio_ptr[0] = 1 << 2; //亮第i个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
//   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 //  if (result < 0)
 //    error(1, errno, "munmap /dev/mem");
  //**************************************************************************************************************************sound1 base */
  mmap_addr = NULL;
  mmap_length = SOUND1_PIO_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = SOUND1_PIO_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  sound1_pio_ptr = (u_int *)((u_int)mmap_ptr +
                             (SOUND1_PIO_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  sound1_pio_value = sound1_pio_ptr[0];
  printf("SOUND1_PIO_BASE=%x", SOUND1_PIO_BASE);
  printf("sound1_pio_value address= %x", sound1_pio_ptr);

  printf("Initial sound1_pio_value : 0x%08X\n", sound1_pio_value);
  led_pio_ptr[0] = 1 << 1; //亮第i个灯
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
//   result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 //  if (result < 0)
 //    error(1, errno, "munmap /dev/mem");

  //**************************************************************************************************************************clk_for_dada base */
  mmap_addr = NULL;
  mmap_length = CLK_FOR_DATA_SPAN;
  mmap_prot = PROT_READ | PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = CLK_FOR_DATA_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  clk_for_data_ptr = (u_int *)((u_int)mmap_ptr + (CLK_FOR_DATA_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  /* read the LED PIO value */
  clk_for_dada_value =(boolean_T)clk_for_data_ptr[0];
  printf("CLK_FOR_DATA_BASE=%x", CLK_FOR_DATA_BASE);
  printf("clk_for_data_value address= %x", clk_for_dada_value);

  printf("Initial clk_for_data_ptr : 0x%08X\n", clk_for_data_ptr);
  led_pio_ptr[0] = 0x00; //灭灯
  // printf("input main\n");
  //usleep(5000000);
  // for(j=0;j<8;j++)
  /* restore the LED PIO value */
  printf("P I/O initial complete!\n");
  /* unmap /dev/mem mappings */
 // result = munmap(mmap_ptr, mmap_length); //取消内存所指的地址
 // if (result < 0)
  //  error(1, errno, "munmap /dev/mem");
  
  //*************************************************************************************************************************x base */
  mmap_addr = NULL;
  mmap_length = L_X_SPAN;
  mmap_prot =  PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = L_X_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  x_ptr = (u_int *)((u_int)mmap_ptr + (L_X_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  printf("X_BASE=%x", L_X_BASE);
  printf("Initial x_ptr : 0x%08X\n", x_ptr);

  
  //*************************************************************************************************************************y base */
  mmap_addr = NULL;
  mmap_length = L_Y_SPAN;
  mmap_prot =  PROT_WRITE;
  mmap_flags = MAP_SHARED;
  mmap_fd = dev_mem_fd;
  mmap_offset = L_Y_BASE & ~(sysconf(_SC_PAGE_SIZE) - 1);
  mmap_ptr = mmap(mmap_addr, mmap_length, mmap_prot, mmap_flags,
                  mmap_fd, mmap_offset);
  if (mmap_ptr == MAP_FAILED)
    error(1, errno, "mmap /dev/mem");

  y_ptr = (u_int *)((u_int)mmap_ptr + (L_Y_BASE & (sysconf(_SC_PAGE_SIZE) - 1)));

  printf("X_BASE=%x", L_Y_BASE);
  printf("Initial x_ptr : 0x%08X\n", y_ptr);




  printf("P I/O initial complete!\n");

  close(dev_mem_fd);
}






/*
 * File trailer for main.c
 *
 * [EOF]
 */
