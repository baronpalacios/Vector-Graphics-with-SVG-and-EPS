all:	binaries

test:	binaries
	./main

binaries:		
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
	rm main
	rm -f figures/*.svg
	rm -f figures/*.eps

