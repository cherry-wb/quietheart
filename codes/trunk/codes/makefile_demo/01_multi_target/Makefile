include Makefile.modules

default:
	@make depend MAKETARGET=depend
	@make libs MAKETARGET=libs

depend:$(MODULES)

libs:$(MODULES)

$(MODULES):
	@#we can replace it as 'make -C $@ ${MAKETARGET}' implements multi object and multi depends.
	@echo for dep, $@ target is:${MAKETARGET}
	
.PHONY:$(MODULES)
