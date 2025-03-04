# 컴파일러 설정
CXX = g++
CXXFLAGS = -Wall -Wextra -g
LDFLAGS =

# 프로젝트 디렉토리
SRC_DIR = source
HEADER_DIR = header
MAIN_DIR = main
BUILD_DIR = debug
OBJ_DIR = $(BUILD_DIR)/obj

# 소스 및 헤더 파일 목록
SRCS = $(MAIN_DIR)/main.cpp $(SRC_DIR)/List.cpp
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 실행 파일 이름
TARGET = $(BUILD_DIR)/single_linkedList.exe

# 빌드 규칙
all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

# 디렉토리 생성 (Windows 호환)
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(OBJ_DIR):
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(OBJ_DIR)/main" mkdir "$(OBJ_DIR)/main"
	@if not exist "$(OBJ_DIR)/source" mkdir "$(OBJ_DIR)/source"

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 모든 .o 파일을 debug/obj/ 폴더에 저장
$(OBJ_DIR)/%.o: %.cpp $(HEADER_DIR)/*.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -c $< -o $@

# 실행
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@cmd /c $(TARGET)

# 디버깅 실행
debug: $(TARGET)
	gdb $(TARGET)

# 빌드 파일 정리 (Windows 호환)
clean:
	@if exist "$(OBJ_DIR)\*.o" del /Q "$(OBJ_DIR)\*.o"
	@if exist "$(TARGET)" del /Q "$(TARGET)"

# 전체 정리 (debug 폴더까지 삭제)
distclean: clean
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
