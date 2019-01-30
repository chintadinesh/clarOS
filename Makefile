lm4dir = $(shell brew --prefix)/Cellar/lm4tools/master

init:
	cd .git/hooks && ln -s ../../pre-commit
	git submodule update --init
	brew bundle
	$(MAKE) -C TivaWare all
	$(MAKE) -C lm4tools all install PREFIX=$(lm4dir)
	brew link lm4tools
