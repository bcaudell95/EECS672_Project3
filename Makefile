CPP = g++
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so
OGL_LIBRARIES = -lglfw -lGLU -lGL

OBJS = project3.o ModelViewWithPhongLighting.o SmallCappingModelView.o LaneModelView.o ModelView_Additions.o Block.o PinModelView.o TenPinsModelView.o GutterModelView.o BigCappingModelView.o PairModelView.o DynamicController.o

project3: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o project3 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(OGL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project3.o: project3.c++
	$(CPP) $(C_FLAGS) project3.c++
ModelView_Additions.o: ModelView_Additions.c++
	$(CPP) $(C_FLAGS) ModelView_Additions.c++
ModelViewWithPhongLighting.o: ModelViewWithPhongLighting.h ModelViewWithPhongLighting.c++
	$(CPP) $(C_FLAGS) ModelViewWithPhongLighting.c++
Block.o: Block.h Block.c++
	$(CPP) $(C_FLAGS) Block.c++
LaneModelView.o: LaneModelView.h LaneModelView.c++
	$(CPP) $(C_FLAGS) LaneModelView.c++
PinModelView.o: PinModelView.h PinModelView.c++
	$(CPP) $(C_FLAGS) PinModelView.c++
TenPinsModelView.o: TenPinsModelView.h TenPinsModelView.c++
	$(CPP) $(C_FLAGS) TenPinsModelView.c++
GutterModelView.o: GutterModelView.h GutterModelView.c++
	$(CPP) $(C_FLAGS) GutterModelView.c++
SmallCappingModelView.o: SmallCappingModelView.h SmallCappingModelView.c++
	$(CPP) $(C_FLAGS) SmallCappingModelView.c++
BigCappingModelView.o: BigCappingModelView.h BigCappingModelView.c++
	$(CPP) $(C_FLAGS) BigCappingModelView.c++
PairModelView.o: PairModelView.h PairModelView.c++
	$(CPP) $(C_FLAGS) PairModelView.c++
DynamicController.o : DynamicController.h DynamicController.c++
	$(CPP) $(C_FLAGS) DynamicController.c++
