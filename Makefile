TARGET = StackImpl

init:
	mkdir build -p && cd build && cmake ..

r:
	cmake --build ./build && ./build/$(TARGET)
