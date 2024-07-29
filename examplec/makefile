
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
          tile_rec.h \
          tile_shape.h \
          token.h \
          token_set.h \
          piece.h \
          challenge.h \
          puzzle_book.h \
          \
# note: all of the files after toy.h are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore
         \

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
          tile_shape.obj \
          token.obj \
          token_set.obj \
          piece.obj \
          challenge.obj \
          puzzle_book.obj \
          \
# note: all of the files after toy.obj are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore
          \

LIBPATH = /libpath:c:/users/demon/sdl2/lib/x64 /libpath:c:/users/demon/glew/lib/Release/x64
INCPATH = /Ic:/users/demon/sdl2/include /Ic:/users/demon/glew/include
LIBRARIES = opengl32.lib glew32.lib SDL2main.lib SDL2.lib shell32.lib SDL2_mixer.lib
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



