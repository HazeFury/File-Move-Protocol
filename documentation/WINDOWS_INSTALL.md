## 🛠️ Installation du projet FMP sous Windows

Ce guide explique comment configurer un environnement de développement sous Windows pour compiler et exécuter le projet **FMP** (ou tout autre projet basé sur **FLTK** avec MinGW).

---

### ✅ Prérequis

#### 1. **Compiler : MinGW-w64**

Téléchargez un MinGW compatible avec votre architecture 64 bits.

- **Recommandé :** [https://winlibs.com](https://winlibs.com)
- Exemple de version testée : `mingw-w64 + gcc 15.1.0` (2024)

**Installation :**

- Dézippez l'archive dans un dossier, par exemple : `C:\mingw64`
- Ajoutez le dossier `C:\mingw64\bin` à votre **PATH** Windows :

  - Recherchez _Variables d'environnement_
  - Modifiez `Path` et ajoutez : `C:\mingw64\bin`

#### 2. **CMake (pour construire FLTK)**

Téléchargez ici : [https://cmake.org/download](https://cmake.org/download)

- Ajoutez CMake à votre PATH lors de l'installation (case à cocher).

#### 3. **FLTK**

Téléchargement : [https://www.fltk.org/software.php](https://www.fltk.org/software.php)

**Étapes :**

1. Dézippez dans : `C:\libs\fltk`
2. Ouvrez un terminal dans `C:\libs\fltk`
3. Créez un dossier de build :

   ```bash
   mkdir build
   cd build
   ```

4. Configurez CMake pour utiliser MinGW :

   ```bash
   cmake .. -G "MinGW Makefiles"
   ```

5. Compilez FLTK :

   ```bash
   mingw32-make
   ```

---

### 🧱 Arborescence recommandée

```
C:\
├── libs\
│   └── fltk\
│       ├── FL\
│       ├── build\
└── mingw64\
    └── ton-projet\
        ├── main.cxx
        └── Makefile
```

---

### 🦚 Test de la configuration

Créez un fichier `main.cxx` simple :

```cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main() {
    Fl_Window window(340,180);
    Fl_Box box(20,40,300,100,"Hello, FLTK!");
    window.end();
    window.show();
    return Fl::run();
}
```

---

### 📦 Compilation avec Makefile

Place ce fichier `Makefile` dans le même dossier que `main.cxx` :

```makefile
# Nom de l'exécutable
TARGET = FMP.exe

# Fichiers source
SRC = main.cxx

# Répertoire des bibliothèques
LIB_DIR = C:\libs\fltk\build\lib

# Compilation
CXX = g++
CXXFLAGS = -IC:\libs\fltk -IC:\libs\fltk\FL -IC:\libs\fltk\build
LDFLAGS = -L$(LIB_DIR) -lfltk -lole32 -luuid -lcomctl32 -lws2_32 -lgdiplus -lwinspool -mwindows

# Règle de compilation
all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	del $(TARGET)
```

Puis exécute la commande suivante dans un terminal ouvert dans ce dossier :

```bash
mingw32-make
```

L'exécutable `FMP.exe` devrait être généré 🎉

---

### 🛀 Nettoyage

Pour supprimer l'exécutable :

```bash
mingw32-make clean
```

---

### ❗ Problèmes fréquents

- \*\*"ld.exe: undefined reference to `OpenPrinterA'":** → Solution : ajouter `-lwinspool`dans`LDFLAGS\`

- **"No targets specified and no makefile found":** → Vérifie que le fichier s’appelle `Makefile` (sans `.txt`) et que tu es dans le bon dossier.

- **"cmake: command not found":** → Ajoute CMake à ton `PATH` ou réinstalle avec l'option correspondante.

- **Erreur sur **`**, **`**, etc.** : → Ces bibliothèques sont nécessaires sous Windows. Assure-toi qu’elles sont bien listées dans `LDFLAGS`.

- Si tu veux taper toute la commande pour compiler le projet depuis ton terminal, voici la commande complète à taper :

```
g++ main.cxx -IC:\libs\fltk -IC:\libs\fltk\FL -IC:\libs\fltk\build -LC:\libs\fltk\build\lib -lfltk -lole32 -luuid -lcomctl32 -lws2_32 -lgdiplus -lwinspool -mwindows -o FMP.exe
```

---
