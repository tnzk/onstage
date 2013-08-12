CPPFLAGS = -std=c++0x
OBJS = thestage.o stage_command.o

onstage: $(OBJS)
	g++ -o onstage $(OBJS)

thestage: thestage.cpp
	g++ thestage.cpp -c $(CPPFLAGS)

stage_command: thestage.cpp
	g++ stage_command.cpp -c $(CPPFLAGS)

# `pkg-config --libs --cflags librsvg-2.0`

clean:
	rm -f onstage $(OBJS)