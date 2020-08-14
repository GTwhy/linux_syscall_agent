MAKE = make -w

.PHONEY:all

all :
	cd ./daemon && $(MAKE)
	cd ./lib && $(MAKE)

.PHONEY:clean

clean:
	cd ./daemon && $(MAKE) clean
	cd ./lib && $(MAKE) clean


