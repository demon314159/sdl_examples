
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
          brick_shape.h \
          element.h \
          vertex_image.h \
          token_file.h \
          document.h \
          mouse_vector.h \
          choose.h \
          command.h \
          history.h \
          frame_model.h \
          door_model.h \
          window_model.h \
          gable_brick_shape.h \
          button_shape.h \
          push_button.h \
          image_panel.h \
          material_menu.h \
          \
# note: all of the files after toy.h are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore
         \

RESOURCES = \
          vshader.glsl \
          fshader.glsl \
          p_bricks.png \

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
          brick_shape.obj \
          element.obj \
          vertex_image.obj \
          token_file.obj \
          document.obj \
          mouse_vector.obj \
          choose.obj \
          command.obj \
          history.obj \
          frame_model.obj \
          door_model.obj \
          window_model.obj \
          gable_brick_shape.obj \
          button_shape.obj \
          push_button.obj \
          image_panel.obj \
          material_menu.obj \
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

%.res: %.rc $(RESOURCES)
	rc $<

$(TARGET): $(OBJECTS) bricks.res
	$(LXX) /out:$@ $(OBJECTS) $(LIBPATH) $(LIBRARIES) $(LINKFLAGS) bricks.res

i.PHONY: clean

clean:
	del *.obj; del play.exe; del *.res



