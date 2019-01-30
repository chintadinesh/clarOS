lm4dir = $(shell brew --prefix)/Cellar/lm4tools/master

init:
	git submodule update
	brew bundle
	$(MAKE) -C TivaWare all
	$(MAKE) -C lm4tools all install PREFIX=$(lm4dir)
	brew link lm4tools
