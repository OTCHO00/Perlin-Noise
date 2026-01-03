CXX = clang++
SFML_PATH = /opt/homebrew/opt/sfml

CXXFLAGS = -std=c++17 \
-Iincludes \
-I$(SFML_PATH)/include \
-Iimgui \
-Iimgui-sfml

LDFLAGS = -L$(SFML_PATH)/lib \
-lsfml-graphics -lsfml-window -lsfml-system \
-framework OpenGL -framework Cocoa

SRC = $(wildcard src/*.cpp) \
      $(wildcard imgui/*.cpp) \
      imgui-sfml/imgui-SFML.cpp

OBJ = $(patsubst %.cpp,build/%.o,$(SRC))

perlin: $(OBJ)
	$(CXX) $(OBJ) -o build/perlin $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

run: perlin
	./build/perlin