# 📁 File Move Protocol (FMP)

**FMP** est un outil graphique simple et multiplateforme permettant de **déplacer automatiquement des fichiers** d'un dossier source vers un dossier de destination selon certaines règles. Il est conçu pour être rapide à utiliser et léger, tout en offrant un gain de temps significatif pour des actions répétitives de tri ou de transfert de fichiers.

---

## ✨ Fonctionnalités

- Interface graphique légère avec **FLTK**
- Déplacement automatique de fichiers d'un dossier vers un autre
- Configuration simple (dossiers source/destination)
- Supporte les chemins relatifs et absolus
- Compatible Windows et Linux (via Makefile multiplateforme)

---

## 🧰 Technologies utilisées

| Outil         | Description                                 |
| ------------- | ------------------------------------------- |
| **C/C++**     | Langages principaux                         |
| **FLTK**      | Toolkit GUI ultra-léger                     |
| **CMake**     | Utilisé pour construire FLTK si besoin      |
| **MinGW-w64** | Compilation sous Windows                    |
| **make**      | Système de build portable (Linux & Windows) |

---

## ⚙️ Compilation

Le projet utilise un **Makefile multiplateforme** pour compiler facilement sous Windows ou Linux.

### Sous Windows

- Installation détaillée : voir [WINDOWS_INSTALL](./documentation/WINDOWS_INSTALL.md)

```bash
mingw32-make
```

### Sous Linux

- Installation simplifiée : voir [LINUX_INSTALL](./documentation/LINUX_INSTALL.md.md)

```bash
make
```

L'exécutable est ensuite généré dans le même dossier : `FMP.exe` (Windows) ou `FMP` (Linux)

---

## 🏁 Exemple d'utilisation

1. Lancez le programme
2. Sélectionnez un dossier source contenant des fichiers
3. Sélectionnez un dossier destination
4. Cliquez sur « Déplacer » pour transférer automatiquement les fichiers

---

## 🤝 Contribuer

Les contributions sont les bienvenues !

1. Forkez le repo
2. Créez une branche
3. Proposez une Pull Request

---

## 📄 Licence

Projet open source sous licence MIT

---

**Créé avec passion pour simplifier le quotidien.**
