include path.include
default:
	@echo in sub makefile, exported var:${MYVAREXPORT}, not exported var:${MYVARNOEXPORT}
	@echo sub make:the path of pwd command is:$(pwd)
	@echo sub make:the path of \`pwd\` command is:`pwd`
	@echo sub make:the path of PWD var is:$(PWD)
	@echo sub include path var from dir:${MYPATH}
	make -C subsub
