obj-m:=18b20.o
18b20module-objs:=module
KDIR:=/lib/modules/$(shell uname -r)/build
MAKE:=make
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
