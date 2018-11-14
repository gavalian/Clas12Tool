.PHONY: all

list = Core Clas12 Root Tools
all: 
	for i in $(list); do	$(MAKE) -C $$i ; done

clean:
	for i in $(list); do	$(MAKE) clean -C $$i ; done
