#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>      // pour fl_alert
#include <filesystem>
#include <regex>
#include <string>
#include "ui.hpp"
#include "core/file_move.h"

namespace fs = std::filesystem;

// Variables globales pour stocker les chemins
static std::string source_path = "";
static std::string destination_path = "";

// --- UTILS ---

// Vérifie si une chaîne commence par exactement 5 chiffres
bool starts_with_5_digits(const std::string& filename) {
    return std::regex_match(filename.substr(0, 5), std::regex("^[0-9]{5}$"));
}

// Scan tous les fichiers du dossier source
bool scan_files_in_source(const std::string& dir_path) {
    if (dir_path.empty()) {
        fl_alert("Aucun dossier source sélectionné.");
        return false;
    }

    try {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (entry.is_regular_file()) {
                std::string name = entry.path().filename().string();
                if (name.size() < 5 || !starts_with_5_digits(name)) {
                    fl_alert(("Nom de fichier invalide : " + name).c_str());
                    return false;
                }
            }
        }
        fl_alert("Tous les fichiers sont valides !");
        return true;
    } catch (const std::exception& e) {
        fl_alert(("Erreur lors du scan : " + std::string(e.what())).c_str());
        return false;
    }
}

// --- CALLBACKS ---

void on_select_source(Fl_Widget*, void*) {
    const char* path = fl_dir_chooser("Choisir dossier source", "", 1);
    if (path) {
        source_path = path;
    }
}

void on_select_destination(Fl_Widget*, void*) {
    const char* path = fl_dir_chooser("Choisir dossier destination", "", 1);
    if (path) {
        destination_path = path;
    }
}

void on_scan_files(Fl_Widget*, void*) {
    scan_files_in_source(source_path);
}

void on_click_move(Fl_Widget*, void*) {
    if (source_path.empty() || destination_path.empty()) {
        fl_alert("Veuillez d'abord choisir les dossiers source et destination.");
        return;
    }
    if (!scan_files_in_source(source_path)) {
        return; // Ne pas déplacer si fichiers invalides
    }
    move_files(source_path.c_str(), destination_path.c_str());
    fl_alert("Déplacement terminé !");
}

// --- GUI ---

int create_main_window(int argc, char** argv) {
    Fl_Window* win = new Fl_Window(500, 250, "FMP v0.3");

    Fl_Button* btn_src = new Fl_Button(50, 30, 180, 30, "Dossier Source");
    btn_src->callback(on_select_source);

    Fl_Button* btn_dst = new Fl_Button(270, 30, 180, 30, "Dossier Destination");
    btn_dst->callback(on_select_destination);

    Fl_Button* btn_scan = new Fl_Button(50, 80, 180, 30, "Scanner les fichiers");
    btn_scan->callback(on_scan_files);

    Fl_Button* btn_move = new Fl_Button(270, 80, 180, 30, "Déplacer");
    btn_move->callback(on_click_move);

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
