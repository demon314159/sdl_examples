
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
          toy.h \
          \
          \
          \
          cube_shape.h \
          \
          \
          \
# note: all of the files after toy.h are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore

OBJECTS = main.obj \
          view.obj \
          host.obj \
          matrix4x4.obj \
          matrix3x3.obj \
          paint_can.obj \
          look.obj \
          navigate.obj \
          cad_model.obj \
          toy.obj \
          \
          \
          \
          cube_shape.obj \
          \
          \
          \
# note: all of the files after toy.obj are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore

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



