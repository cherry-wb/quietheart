DVIPDFMX:=$(shell grep '\\def\\usewhat{dvipdfmx}' main.tex)
PDFLATEX:=$(shell grep '\\def\\usewhat{pdflatex}' main.tex)
DVIPSPDF:=$(shell grep '\\def\\usewhat{dvipspdf}' main.tex)
YAP:=$(shell grep '\\def\\usewhat{yap}' main.tex)
XELATEX :=$(shell grep '\\def\\usewhat{xelatex}'  main.tex)
empty=
GBK2UNI = ./Accessories/tools/gbk2uni
all:
ifneq ($(empty),$(XELATEX))
	@echo Making xelatex......
	rm main_xelatex.pdf &
	xelatex main.tex
	xelatex main.tex
	xelatex main.tex
	mv main.pdf main_xelatex.pdf
	@echo Done. Starting the browser......
	acroread main_xelatex.pdf&
endif
ifneq ($(empty),$(DVIPDFMX))
	@echo Making dvipdfmx......
	rm main.pdf main.dvi &
	latex main.tex
	env BIBINPUTS=./ BSTINPUTS=./ bibtex main
	latex main.tex
	latex main.tex
	dvipdfmx -p a4 main.dvi
	@echo Done. Starting the browser......
	acroread main.pdf&
endif
ifneq ($(empty),$(PDFLATEX))
	@echo Making pdflatex......
	rm main_pdflatex.pdf&
	pdflatex main.tex
	env BIBINPUTS=./ BSTINPUTS=./ bibtex main
	pdflatex main.tex
	$(GBK2UNI) main.out
	pdflatex main.tex
	mv main.pdf main_pdflatex.pdf
	@echo Done. Starting the browser......
	acroread main_pdflatex.pdf&
endif
ifneq ($(empty),$(DVIPSPDF))
	@echo Making dvipspdf......
	rm main_dvipspdf.pdf main.dvi main.ps&
	latex main.tex
	env BIBINPUTS=./ BSTINPUTS=./ bibtex main
	latex main.tex
	$(GBK2UNI) main.out
	latex main.tex
	dvips  -G0 -ta4 main.dvi
	ps2pdf main.ps main_dvipspdf.pdf
	@echo Done. Starting the browser......
	acroread main_dvipspdf.pdf&
endif
ifneq ($(empty),$(YAP))
	@echo Making dvi......
	rm main.dvi&
	latex main.tex
	env BIBINPUTS=./ BSTINPUTS=./ bibtex main
	latex main.tex
	$(GBK2UNI) main.out
	latex main.tex
	xdvi main.dvi&
endif

clean:
	@echo Cleaning up......
	-find -name '*.aux' -exec rm {} \;
	-find -name '*.bak' -exec rm {} \;
	-find -name '*.dvi' -exec rm {} \;
	-find -name '*~' -exec rm {} \;
	-find -name '#*#' -exec rm {} \;
	-find -name 'semantic.cache' -exec rm {} \;
	-find -name '*.log' -exec rm {} \;
	-rm *.bbl *.blg *.log *.out *.ps *.thm *.toc *.toe *.lof *.lot 
	-rm *.html *.css *.scm *.hlog
	-rm _region_.tex
	-rm -rf auto
	-rm *.fen
	-rm *.ten
	-rm -rf ./body/auto
	-rm -rf ./reference/auto
	-rm -rf ./setup/auto
	-rm -rf ./preface/auto
	-rm -rf *.prv
	@echo All done.
