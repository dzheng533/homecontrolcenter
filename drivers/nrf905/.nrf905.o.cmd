cmd_/root/projects/hcc/drivers/nrf905/nrf905.o := gcc -Wp,-MD,/root/projects/hcc/drivers/nrf905/.nrf905.o.d  -nostdinc -isystem /usr/lib/gcc/armv6l-unknown-linux-gnueabihf/4.7.2/include -I/usr/src/linux-3.6.11-17-ARCH+/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /usr/src/linux-3.6.11-17-ARCH+/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-bcm2708/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=6 -march=armv6 -mtune=arm1136j-s -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(nrf905)"  -D"KBUILD_MODNAME=KBUILD_STR(mod_nrf905)" -c -o /root/projects/hcc/drivers/nrf905/.tmp_nrf905.o /root/projects/hcc/drivers/nrf905/nrf905.c

source_/root/projects/hcc/drivers/nrf905/nrf905.o := /root/projects/hcc/drivers/nrf905/nrf905.c

deps_/root/projects/hcc/drivers/nrf905/nrf905.o := \
  /root/projects/hcc/drivers/nrf905/nrf905.h \
  /root/projects/hcc/drivers/nrf905/wiringPi.h \
  /root/projects/hcc/drivers/nrf905/wiringPiSPI.h \

/root/projects/hcc/drivers/nrf905/nrf905.o: $(deps_/root/projects/hcc/drivers/nrf905/nrf905.o)

$(deps_/root/projects/hcc/drivers/nrf905/nrf905.o):
