include src1/src1.make
include src2/src2.make

CUR_DIR_MAKE  = $(PWD)
MY_HOME = ${HOME}
CC := gcc
GCCV := $(shell ${CC} --version |grep -m 1 '[0-9]\+.[0-9]\+.[0-9]\+' |sed -e 's/.*\([0-9]\+.[0-9]\+.[0-9]\+\).*/\1/g')
ifneq (,$(filter 4.6.3,$(GCCV)))
NEW = YES
else
NEW = NO
endif
default:
	@echo ${CUR_DIR_MAKE}
	@echo ${CUR_DIR_SRC1}
	@echo ${CUR_DIR_SRC2}
	@echo ${MY_HOME}
	@echo $$MY_HOME
	@echo $$HOME
	@echo $(HOME)
	@echo ${HOME}
	@echo ${GCCV}
	@echo ${NEW}
	@echo ${EXT}
