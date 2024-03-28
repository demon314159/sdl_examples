
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
          plane_shape.h \
          cube_shape.h \
          cylinder_shape.h \
          ring_shape.h \
          navigate.h \
          cad_model.h \
          stl_file.h \
          bin_file.h \
          char_file.h \
          view.h \
          quaternion.h \
          toy.h \
          \
          sphere_shape.h \
          toroid_shape.h \
          triangular_prism_shape.h \
          cone_shape.h \
          top_panel_shape.h \
          bottom_panel_shape.h \
          flipper_shape.h \
          state.h \
          lamp.h \
          ball.h \
          straight_reflector.h \
          straight_diode_reflector.h \
          convex_reflector.h \
          concave_reflector.h \
          flipper_model.h \
          flipper.h \
          straight_strip.h \
          straight_diode_strip.h \
          concave_strip.h \
          concave_plane_shape.h \
          table.h \
          ring_model.h \
          ring.h \
          pipe.h \
          pipe_elbow.h \
          pipe_shape.h \
          pipe_elbow_shape.h \
          rollover.h \
          straight_wire_guide.h \
          pyramid_lane_guide.h \
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
          toy.obj \
          \
          sphere_shape.obj \
          toroid_shape.obj \
          triangular_prism_shape.obj \
          cone_shape.obj \
          top_panel_shape.obj \
          bottom_panel_shape.obj \
          flipper_shape.obj \
          state.obj \
          lamp.obj \
          ball.obj \
          straight_reflector.obj \
          straight_diode_reflector.obj \
          convex_reflector.obj \
          concave_reflector.obj \
          flipper_model.obj \
          flipper.obj \
          straight_strip.obj \
          straight_diode_strip.obj \
          concave_strip.obj \
          concave_plane_shape.obj \
          table.obj \
          ring_model.obj \
          ring.obj \
          pipe.obj \
          pipe_elbow.obj \
          pipe_shape.obj \
          pipe_elbow_shape.obj \
          rollover.obj \
          straight_wire_guide.obj \
          pyramid_lane_guide.obj \
          \
          \
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



