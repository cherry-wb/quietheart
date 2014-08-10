MYVAR?=1
ifeq "$(MYVAR)" "1"
all:
	@echo "my var is 1."
else
all:
	@echo "my var is 2."
endif

MYNULL=   
ifeq (,$(strip $(MYNULL)))
null:
	@echo "my null is null"
else
null:
	@echo "my null is not null"
endif
