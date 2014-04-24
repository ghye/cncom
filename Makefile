objects = main_stsr.o serial_conf.o sig_handler.o g_param.o

cncom : $(objects)
	cc -o cncom $(objects)

.PHONY	: clean
clean :
	-rm cncom $(objects)
