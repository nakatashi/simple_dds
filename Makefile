CC=gcc
AR=ar
ARFLAGS=rcs
# Place generated static library where linker will search for.
AROUTDIR=/usr/local/lib/
CFLAGS=-O3 -Wall
DEPS=rp_dds.h
LIBPREFIX=lib
LFILE=librp_dds.a
APPSOURCE=main.c

all: $(LFILE)

test: main.c $(LFILE)
	$(CC) $< -L$(AROUTDIR) -lrp_dds

app: $(APPSOURCE) $(LFILE)
	$(CC) $< -L$(AROUTDIR) -lrp_dds

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIBPREFIX:=%.a): %.o
	$(AR) $(ARFLAGS) $(AROUTDIR:=$@) $^

#See Creating a shared and static library with the gnu compiler [gcc]

#gcc -c -o out.o out.c
#-c means to create an intermediary object file, rather than an executable.

#ar rcs libout.a out.o
