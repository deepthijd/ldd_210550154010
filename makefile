obj-m:=mydriver.o
KDIR=/lib/module/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o app app.c
	clean:
	make -C $(KDIR) M=$(PWD) clean
	rm-rf app	
