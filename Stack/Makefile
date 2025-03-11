# 컴파일러 설정
CXX = g++
CXXFLAGS = -Wall -Wextra -g
LDFLAGS = 

# 디렉터리 경로설정
SOURCE_DIR = source
HEADER_DIR = header
MAIN_DIR = main
BUILD_DIR = debug
OBJ_DIR = $(BUILD_DIR)/obj

# 소스/헤더파일 목록
SRCS = $(MAIN_DIR)/main.cpp $(SOURCE_DIR)/List.cpp $(SOURCE_DIR)/Stack.cpp
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 실행파일
TARGET = $(BUILD_DIR)/Stack.exe

# 빌드규칙
all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

# 빌드용 디렉터리 생성(윈도우용)
$(BUILD_DIR):
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

$(OBJ_DIR):
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(OBJ_DIR)/main" mkdir "$(OBJ_DIR)/main"
	@if not exist "$(OBJ_DIR)/source" mkdir "$(OBJ_DIR)/source"

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 동작 설명 : 타겟을 빌드하려면 obj 파일들이 필요함
# $(TARGET) : $(OBJS)
# obj가 변경되거나 존재 안하면, 아래명령을 실행
# -o $@ 
# -o : 출력파일 지정, $@ : $TARGET의 값
# $^ 
# 모든 의존파일 목록 -> $OBJS

# 모든 .o 파일을 debug/obj/ 폴더에 저장
$(OBJ_DIR)/%.o: %.cpp $(HEADER_DIR)/*.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(HEADER_DIR) -c $< -o $@

# $(OBJ_DIR)/%.o
# %(와일드카드) 를 사용하여 어떤 파일이든 .o 로 변환
# $(OBJ_DIR)/%.o : %.cpp $(HEADER_DIR)/*.h | $(OBJ_DIR)
# obj(왼쪽)은 src & h(오른쪽)에 의존적임
# -I$(HEADER_DIR) 
# 헤더의 경로
# -c $< -o $@
# 의존파일(소스)을 컴파일 하여 .o 파일을 생성


# 실행
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@$(TARGET)

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