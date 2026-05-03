vm_app :
	gcc main.c interpret.c vm.c stack.c -o vm_app

clean :
	rm -f vm_app *.o 