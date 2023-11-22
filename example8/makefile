
HEADERS = view.h \
          pi.h \
          host.h \
          matrix4x4.h \
          matrix3x3.h \
          int3.h \
          float3.h \
          facet.h \
          face.h \
          vertex_data.h \
          paint_can.h \
          bounding_box.h \
          look.h \
          shape.h \
          navigate.h \
          cad_model.h \
          view.h \
          cube_shape.h \
          toy.h \
          track.h \
          anchor.h \
          car.h \
          curved_left_section.h \
          curved_right_section.h \
          double3.h \
          rise_profile.h \
          section.h \
          straight_section.h \
          box_shape.h \
          curved_left_track_shape.h \
          curved_right_track_shape.h \
          cylinder_shape.h \
          ring_shape.h \
          straight_track_shape.h \
          track_style.h \

OBJECTS = main.obj \
          view.obj \
          host.obj \
          matrix4x4.obj \
          matrix3x3.obj \
          paint_can.obj \
          look.obj \
          navigate.obj \
          cad_model.obj \
          cube_shape.obj \
          toy.obj \
          track.obj \
          car.obj \
          curved_left_section.obj \
          curved_right_section.obj \
          rise_profile.obj \
          section.obj \
          straight_section.obj \
          box_shape.obj \
          curved_left_track_shape.obj \
          curved_right_track_shape.obj \
          cylinder_shape.obj \
          ring_shape.obj \
          straight_track_shape.obj \
          track_style.obj \

LIBPATH = /libpath:c:/users/demon/sdl2/lib/x64 /libpath:c:/users/demon/glew/lib/Release/x64
INCPATH = /Ic:/users/demon/sdl2/include /Ic:/users/demon/glew/include
LIBRARIES = opengl32.lib glew32.lib SDL2main.lib SDL2.lib shell32.lib
DEPS = $(HEADERS)
CXX = cl
LXX = link
CXXFLAGS = /c
LINKFLAGS = /SUBSYSTEM:CONSOLE
TARGET = play.exe

%.obj: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCPATH) /Fo$@ $<

$(TARGET): $(OBJECTS)
	$(LXX) /out:$@ $(OBJECTS) $(LIBPATH) $(LIBRARIES) $(LINKFLAGS)

i.PHONY: clean

clean:
	del *.obj; del play.exe



