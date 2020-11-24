ifndef KDIR
	KDIR=~/svp/caligula-linux
endif

obj-m := tas2505.o
obj-m := helloworld.o
obj-m := tas2505-svp.o

PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
