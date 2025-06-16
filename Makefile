# Makefile multiplateforme pour le projet FMP

# Nom de l'exécutable
TARGET = FMP

# Fichier source
SRC = main.cxx

# Compilateur
CXX = g++

# Par défaut, on suppose Linux
CXXFLAGS = -I/usr/include
LDFLAGS  = -lfltk -lX11 -lm -lXext -lXft -lXinerama
EXT =

# Si on est sous Windows, OS est défini à Windows_NT par cmd.exe ou PowerShell
ifdef OS
ifeq ($(OS), Windows_NT)
    FLTK_DIR = C:/libs/fltk
    FLTK_BUILD = $(FLTK_DIR)/build
    LIB_DIR = $(FLTK_BUILD)/lib

    CXXFLAGS = -I$(FLTK_DIR) -I$(FLTK_DIR)/FL -I$(FLTK_BUILD)
    LDFLAGS = -L$(LIB_DIR) -lfltk -lole32 -luuid -lcomctl32 -lws2_32 -lgdiplus -lwinspool -mwindows -static-libgcc -static-libstdc++
    EXT = .exe
endif
endif

# Cible principale
all:
	$(CXX) $(SRC) -o $(TARGET)$(EXT) $(CXXFLAGS) $(LDFLAGS)

# Nettoyage
clean:
ifeq ($(OS), Windows_NT)
	del /Q $(TARGET)$(EXT) 2>nul || exit 0
else
	rm -f $(TARGET)$(EXT)
endif
