include Makefile.includehead
MYVARNOEXPORT="aa"
MYVAREXPORT="bb"
export MYVAREXPORT
default:dephead subdep depend
	@echo "head defined var:" ${MYVARINCLUDEHEAD}
	make -C submake
include submake/submake.include
include Makefile.includeend
