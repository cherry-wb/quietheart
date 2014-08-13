_src:=mapmem_demo.c

${_target}:${_src}
	gcc ${_src} -lpthread -L../lib -lmapmem -o $@
.PHONY:clean
clean:
	$(RM) -rf *.o ${_target}
