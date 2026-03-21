
HEADERS = view.h \
          stb_image.h \
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
          plane_shape.h \
          cube_shape.h \
          cylinder_shape.h \
          ring_shape.h \
          navigate.h \
          cad_model.h \
          stl_file.h \
          bin_file.h \
          char_file.h \
          quaternion.h \
          texture.h \
          uniform.h \
          camera.h \
          pose.h \
          animated_toy.h \
          toy.h \
          \
          perimeter.h \
          sphere_shape.h \
          state.h \
          ball.h \
          table.h \
          concave_plane_shape.h \
          concave_reflector.h \
          concave_strip.h \
          convex_reflector.h \
          straight_reflector.h \
          wall.h \
          trap.h \
          log.h \
          \
          \
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
          shape.obj \
          plane_shape.obj \
          cube_shape.obj \
          cylinder_shape.obj \
          ring_shape.obj \
          navigate.obj \
          cad_model.obj \
          stl_file.obj \
          bin_file.obj \
          char_file.obj \
          quaternion.obj \
          texture.obj \
          uniform.obj \
          camera.obj \
          pose.obj \
          animated_toy.obj \
          toy.obj \
          \
          sphere_shape.obj \
          state.obj \
          ball.obj \
          table.obj \
          concave_plane_shape.obj \
          concave_reflector.obj \
          concave_strip.obj \
          convex_reflector.obj \
          straight_reflector.obj \
          wall.obj \
          trap.obj \
          log.obj \
          \
          \
          \
          \
          \
# note: all of the files after toy.obj are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore

LIBPATH = /libpath:c:/users/demon/sdl2/lib/x86 /libpath:c:/users/demon/glew/lib/Release/Win32
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



