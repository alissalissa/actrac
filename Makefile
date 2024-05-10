#overarching makefile

source_dir=bin/

default: all

all:
	$(MAKE) -C $(source_dir)

clean:
	rm ./bin/*.o ./bin/actrac