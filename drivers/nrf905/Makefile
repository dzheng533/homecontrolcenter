obj-m:=mod_nrf905.o
mod_nrf905-objs:= nrf905.o wiringPi.o wiringPiSPI.o
drivermodule-objs:=module
KDIR:=/lib/modules/3.6.11-17-ARCH+/build
MAKE:=make
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean