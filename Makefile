CPPFLAGS = -std=c++0x `pkg-config --cflags cairo librsvg-2.0 gtk+-3.0` -I./headers
OBJS =	onstage.o \
	thestage.o \
	camera.o \
	stage_viewer.o \
	joystick_state.o \
	joystick_event.o \
	user_control_state.o \
	user_control_context.o \
	stage_command.o \
	stage_command_sync.o \
	stage_command_null.o \
	stage_command_move.o \
	stage_command_load_actor.o \
	stage_command_load_symbol.o \
	stage_command_scale.o \
	stage_command_camera_zoom.o \
	stage_command_camera_move.o \
	stage_command_lookat.o \
	stage_command_eyeblows.o \
	stage_command_speak.o \
	stage_command_facial.o \
	stage_command_shut.o \
	stage_command_left_hand.o \
	stage_command_right_hand.o \
	stage_command_walk.o \
	stage_command_stop.o \
	symbol.o \
	shape.o \
	image_svg.o \
	shape_circle.o \
	shape_path.o \
	actor.o \
	head.o \
	mouth.o \
	eyes.o \
	arm.o

#GCC48 = /opt/bin/g++
GCC48 = g++

onstage: $(OBJS)
	$(GCC48) -o onstage $(OBJS) `pkg-config --libs cairo librsvg-2.0 gtk+-3.0`

onstage.o: onstage.cpp
	$(GCC48) onstage.cpp -c $(CPPFLAGS)

thestage.o: thestage.cpp
	$(GCC48) -c thestage.cpp $(CPPFLAGS) 

stage_viewer.o: stage_viewer.cpp
	$(GCC48) -c stage_viewer.cpp $(CPPFLAGS) 

joystick_state.o: joystick_state.cpp
	$(GCC48) -c joystick_state.cpp $(CPPFLAGS) 

joystick_event.o: joystick_event.cpp
	$(GCC48) -c joystick_event.cpp $(CPPFLAGS) 

user_control_state.o: user_control_state.cpp
	$(GCC48) -c user_control_state.cpp $(CPPFLAGS) 

user_control_context.o: user_control_context.cpp
	$(GCC48) -c user_control_context.cpp $(CPPFLAGS) 

actor.o: actor.cpp
	$(GCC48) -c actor.cpp $(CPPFLAGS)

arm.o: arm.cpp
	$(GCC48) -c arm.cpp $(CPPFLAGS)

head.o: head.cpp
	$(GCC48) -c head.cpp $(CPPFLAGS)

mouth.o: mouth.cpp
	$(GCC48) -c mouth.cpp $(CPPFLAGS)

eyes.o: eyes.cpp
	$(GCC48) -c eyes.cpp $(CPPFLAGS)

shape.o: shape.cpp
	$(GCC48) -c shape.cpp $(CPPFLAGS)

shape_circle.o: shape_circle.cpp
	$(GCC48) -c shape_circle.cpp $(CPPFLAGS)

shape_path.o: shape_path.cpp
	$(GCC48) -c shape_path.cpp $(CPPFLAGS)

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
