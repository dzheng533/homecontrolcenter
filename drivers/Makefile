obj-m:=driver.o
drivermodule-objs:=module
KDIR:=/lib/modules/3.6.11-17-ARCH+/build
MAKE:=make
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
