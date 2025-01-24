
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
          gable_brick_element.h \
          half_brick_element.h \
          brick_element.h \
          half_foundation_element.h \
          foundation_element.h \
          double_foundation_element.h \
          triple_foundation_element.h \
          roof_element.h \
          flat_roof_element.h \
          window_element.h \
          corner_window_element.h \
          front_door_element.h \
          back_door_element.h \
          vertex_image.h \
          token_file.h \
          document.h \
          mouse_vector.h \
          choose.h \
          command.h \
          history.h \
          frame_model.h \
          door_model.h \
          front_door_model.h \
          window_model.h \
          corner_window_model.h \
          gable_brick_shape.h \
          roof_shape.h \
          button_shape.h \
          push_button.h \
          image_panel.h \
          image_button.h \
          material_menu.h \
          table.h \
          \
# note: all of the files after toy.h are there for toy.cpp only
#       they can be removed if toy.cpp doesn't need them anymore
         \

RESOURCES = \
          vshader.glsl \
          fshader.glsl \
          p_panel1.png \
          p_panel2.png \
          p_panel3.png \
          p_panel4.png \
          p_panel5.png \
          p_panel6.png \
          p_panel7.png \

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
          gable_brick_element.obj \
          half_brick_element.obj \
          brick_element.obj \
          half_foundation_element.obj \
          foundation_element.obj \
          double_foundation_element.obj \
          triple_foundation_element.obj \
          roof_element.obj \
          flat_roof_element.obj \
          window_element.obj \
          corner_window_element.obj \
          front_door_element.obj \
          back_door_element.obj \
          vertex_image.obj \
          token_file.obj \
          document.obj \
          mouse_vector.obj \
          choose.obj \
          command.obj \
          history.obj \
          frame_model.obj \
          door_model.obj \
          front_door_model.obj \
          window_model.obj \
          corner_window_model.obj \
          gable_brick_shape.obj \
          roof_shape.obj \
          button_shape.obj \
          push_button.obj \
          image_panel.obj \
          image_button.obj \
          material_menu.obj \
          table.obj \
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



