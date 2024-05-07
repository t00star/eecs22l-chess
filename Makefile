SOURCEDIR = src
DESTDIR = bin

CFLAGS = -std=c11 -Wno-return-local-addr
SRCS := $(wildcard $(SOURCEDIR)/*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
OUT = chesspionage

$(OUT): $(OBJS)
	gcc -g $(OBJS) $(CFLAGS) -o $(DESTDIR)/$(OUT)

%.o: %.c
	gcc -c $< $(CFLAGS) -o $@

clean:
	rm $(OBJS) $(DESTDIR)/$(OUT)

test:
	$(foreach src, $(SRCS), gcc -c $(src) -DTEST $(CFLAGS) -o $(basename $(src)).o;)
	gcc $(OBJS) $(CFLAGS) -o $(DESTDIR)/testRules
	gcc $(OBJS) $(CFLAGS) -o $(DESTDIR)/testBoardDisplay


tar:
	tar -zcvf Chess_Alpha.tar.gz ./README ./COPYRIGHT ./INSTALL ./bin ./doc/Chess_UserManual.pdf
	tar -zcvf Chess_Alpha_src.tar.gz ./README ./COPYRIGHT ./INSTALL ./doc ./bin ./src ./Makefile

clean_tar:
	rm *.tar.gz
