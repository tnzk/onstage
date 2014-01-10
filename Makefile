CPPFLAGS = -std=c++0x `pkg-config --cflags cairo librsvg-2.0` -I./headers
OBJS = thestage.o stage_command.o stage_command_sync.o stage_command_null.o stage_command_move.o stage_command_load_actor.o \
       stage_command_load_symbol.o onstage.o actor.o symbol.o stage_command_scale.o camera.o stage_command_camera_zoom.o \
       stage_command_camera_move.o shape.o image_svg.o
GCC48 = /opt/bin/g++

onstage: $(OBJS)
	$(GCC48) -o onstage $(OBJS) `pkg-config --libs cairo librsvg-2.0`

onstage.o: onstage.cpp
	$(GCC48) onstage.cpp -c $(CPPFLAGS)

thestage.o: thestage.cpp
	$(GCC48) -c thestage.cpp $(CPPFLAGS) 

actor.o: actor.cpp
	$(GCC48) -c actor.cpp $(CPPFLAGS)

shape.o: shape.cpp
	$(GCC48) -c shape.cpp $(CPPFLAGS)

image_svg.o: image_svg.cpp
	$(GCC48) -c image_svg.cpp $(CPPFLAGS)

symbol.o: symbol.cpp
	$(GCC48) -c symbol.cpp $(CPPFLAGS)

camera.o: camera.cpp
	$(GCC48) -c camera.cpp $(CPPFLAGS)

stage_command.o: stage_command.cpp
	$(GCC48) -c stage_command.cpp $(CPPFLAGS)
	$(GCC48) -c commands/*.cpp $(CPPFLAGS)

clean:
	rm -f onstage $(OBJS)
