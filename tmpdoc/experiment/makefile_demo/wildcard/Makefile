FILES:=$(wildcard *.c)
ALLFILES:=$(subst ./, , $(foreach dir,.,$(wildcard $(dir)/*.c)) )
default:
	@echo ${FILES}
	@echo ${ALLFILES}
