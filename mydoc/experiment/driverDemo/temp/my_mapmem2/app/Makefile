_target:=test_demo
_lib_target:=libmapmem.a
_src_dir:=src
_lib_dir:=lib

export _target
all:${_target} ${libmapmem.a}

${_target}:${_lib_target}
	${MAKE} -C ${_src_dir}

${_lib_target}:
	${MAKE} -C ${_lib_dir}

.PHONY:clean
clean:
	${MAKE} -C ${_src_dir} clean
	${MAKE} -C ${_lib_dir} clean
