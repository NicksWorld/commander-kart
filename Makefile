AS=ca65
CC=cc65
LD=cl65

ASFLAGS=-t cx16
CFLAGS=-t cx16 -O
LDFLAGS=-t cx16 -O

OBJECTS=src/main.o src/menu.o src/track.o src/vera.o

COMMANDERKART.PRG: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $(addsuffix .tmp.s, $(basename $<)) $<
	$(AS) $(ASFLAGS) -o $@ $(addsuffix .tmp.s, $(basename $<))

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

.PHONY:
clean:
	$(RM) COMMANDERKART.PRG $(OBJECTS) $(wildcard src/*.tmp.s)
