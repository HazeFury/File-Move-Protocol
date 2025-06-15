## 🛠️ Installation du projet FMP sous Linux

Ce guide explique comment configurer un environnement de développement sous **Linux** pour compiler et exécuter le projet **FMP**, qui utilise la bibliothèque graphique **FLTK**.

---

### ✅ Prérequis

#### 1. Installer les outils de compilation

Ouvre un terminal et installe les paquets suivants selon ta distribution :

##### Pour les distributions basées sur Debian/Ubuntu :

```bash
sudo apt update
sudo apt install build-essential cmake libfltk1.3-dev
```

##### Pour Arch Linux / Manjaro :

```bash
sudo pacman -S base-devel cmake fltk
```

##### Pour Fedora :

```bash
sudo dnf install @development-tools cmake fltk-devel
```

---

### 🧪 Test de la configuration

Crée un fichier `main.cxx` avec ce code de test FLTK :

```cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main() {
    Fl_Window window(340, 180);
    Fl_Box box(20, 40, 300, 100, "Hello, FLTK!");
    window.end();
    window.show();
    return Fl::run();
}
```

---

### ⚙️ Compilation avec Makefile

Crée un fichier `Makefile` à côté de `main.cxx` :

```makefile
# Nom de l'exécutable
TARGET = FMP

# Fichiers source
SRC = main.cxx

# Compilation
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lfltk

# Règle de compilation
all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
```

Puis exécute :

```bash
make
```

Un exécutable `FMP` devrait être généré. Tu peux le lancer avec :

```bash
./FMP
```

---

### 🧹 Nettoyage

Pour nettoyer les fichiers générés :

```bash
make clean
```

---

### ✅ Remarques

- Aucune compilation manuelle de FLTK n'est nécessaire sous Linux, car elle est disponible via les gestionnaires de paquets.
- Ce guide est compatible avec tous les systèmes Unix modernes (Ubuntu, Debian, Arch, Fedora, etc).
- Si tu veux taper toute la commande pour compiler le projet depuis ton terminal, voici la commande complète à taper :

```
fltk-config --compile main.cxx
```

---
