# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Nome do executável
TARGET = $(BIN_DIR)/tp2.out

# Arquivos fonte
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra principal
all: $(TARGET)

# Criação dos diretórios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para gerar o executável
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@

# Regra para gerar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/tp2.out

# Limpeza completa
distclean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)


rebuild: distclean all


.PHONY: all clean distclean rebuild


$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/*.hpp
$(OBJ_DIR)/pacote.o: $(INCLUDE_DIR)/pacote.hpp $(INCLUDE_DIR)/vector.hpp $(INCLUDE_DIR)/map.hpp $(INCLUDE_DIR)/lista_duplamente_encadeada.hpp
$(OBJ_DIR)/armazem.o: $(INCLUDE_DIR)/armazem.hpp
$(OBJ_DIR)/escalonador.o: $(INCLUDE_DIR)/escalonador.hpp $(INCLUDE_DIR)/evento.hpp $(INCLUDE_DIR)/armazem.hpp $(INCLUDE_DIR)/pacote.hpp $(INCLUDE_DIR)/vector.hpp $(INCLUDE_DIR)/minheap.hpp
$(OBJ_DIR)/lerEntrada.o: $(INCLUDE_DIR)/lerEntrada.hpp
