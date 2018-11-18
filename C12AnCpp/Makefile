.PHONY: all

list = Core Clas12 Root Tools Lund
all: 
	for i in $(list); do mkdir -p includes/$$i ; cp $$i/inc/* includes/$$i ; done
	for i in $(list); do	$(MAKE) -C $$i ; done
	
clean:
	for i in $(list); do	$(MAKE) clean -C $$i ; done
