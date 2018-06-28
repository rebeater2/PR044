#
TARGET = mtest

#
CROSS_COMPILE = arm-linux-gnueabihf-
ALT_DEVICE_FAMILY ?= soc_cv_av
CFLAGS =  -g -Wall  -I D:/intelFPGA/17.1/embedded/ip/altera/hps/altera_hps/hwlib/include -D$(ALT_DEVICE_FAMILY)
LDFLAGS =  -g -Wall  
CC = $(CROSS_COMPILE)gcc -lm
ARCH= arm


build: $(TARGET)
$(TARGET): main.o anyNonfinite.o cosd.o diag.o sind.o eig.o exp.o fft.o fliplr.o music_angle.o music_angle_emxAPI.o music_angle_emxutil.o music_angle_initialize.o music_angle_rtwutil.o music_angle_terminate.o recip.o relop.o rt_nonfinite.o rtGetInf.o rtGetNaN.o schur.o sort1.o sqrt.o xdlapy3.o xgehrd.o xgerc.o xhseqr.o xnrm2.o xscal.o xzggbal.o xzggev.o xzhgeqz.o xungorghr.o xzhseqr.o xzlarfg.o xzlartg.o xztgevc.o
	$(CC) $(LDFLAGS)   $^ -o $@  
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~ 
