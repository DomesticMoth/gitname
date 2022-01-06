build: src/gitname.c src/lb.c
	mkdir -p bin
	gcc -O3 -s -o bin/gitname src/gitname.c 

clean:
	rm -rf bin
	rm -rf package
	rm -f ./package.deb

createdeb: build
	mkdir -p package/DEBIAN
	cp control package/DEBIAN/control
	mkdir -p package/usr/bin
	cp bin/gitname package/usr/bin/gitname
	dpkg-deb --build ./package

installdeb: clean createdeb
	apt install ./package.deb

install: build
	cp bin/gitname /usr/bin/gitname
