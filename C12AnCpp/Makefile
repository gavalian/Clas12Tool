.PHONY: all

list = Core Clas12 Root
all: 
	for i in $(list); do	$(MAKE) -C $$i ; done

clean:
	for i in $(list); do	$(MAKE) clean -C $$i ; done
