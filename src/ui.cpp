#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>

#include <string>
#include <sstream>
#include <iostream>

extern "C" {
    #include "./core/file_scan.h"
    #include "./core/file_move.h"
}

Fl_Input* input_source = nullptr;
Fl_Input* input_dest = nullptr;
Fl_Multiline_Output* output = nullptr;

void show_alert(const std::string& message) {
    fl_alert("%s", message.c_str());
}

void select_folder(Fl_Input* input_field) {
    const char* selected = fl_dir_chooser("Choisir un dossier", nullptr, 1);
    if (selected) {
        input_field->value(selected);
    }
}

void on_scan_clicked(Fl_Widget*, void*) {
    std::string source = input_source->value();
    if (source.empty()) {
        show_alert("Veuillez sélectionner un dossier source.");
        return;
    }

    int total = 0, valid = 0, invalid = 0;
    scan_files(source.c_str(), &total, &valid, &invalid);

    std::ostringstream oss;
    oss << "Analyse terminée :\n";
    oss << "Fichiers détectés : " << total << "\n";
    oss << "✔️ Fichiers valides : " << valid << " \n";
    oss << "❌Fichiers invalides : " << invalid << "\n";

    output->value(oss.str().c_str());
}

void on_move_clicked(Fl_Widget*, void*) {
    std::string source = input_source->value();
    std::string dest = input_dest->value();

    if (source.empty() || dest.empty()) {
        show_alert("Veuillez sélectionner les dossiers source et destination.");
        return;
    }

    int moved = 0, ignored = 0;
    move_files(source.c_str(), dest.c_str(), &moved, &ignored);

    std::ostringstream oss;
    oss << "Déplacement terminé :\n";
    oss << "✔️ Fichiers déplacés : " << moved << "\n";
    oss << "❌ Fichiers ignorés (existaient déjà) : " << ignored << "\n";

    output->value(oss.str().c_str());
}

int create_main_window(int argc, char** argv) {
    Fl_Window* win = new Fl_Window(600, 300, "FMP - File Move Protocol");

    input_source = new Fl_Input(160, 30, 300, 25, "Dossier source :");
    Fl_Button* btn_browse_source = new Fl_Button(470, 30, 100, 25, "Parcourir");
    btn_browse_source->callback([](Fl_Widget*, void*) {
        select_folder(input_source);
    });

    input_dest = new Fl_Input(160, 70, 300, 25, "Dossier destination :");
    Fl_Button* btn_browse_dest = new Fl_Button(470, 70, 100, 25, "Parcourir");
    btn_browse_dest->callback([](Fl_Widget*, void*) {
        select_folder(input_dest);
    });

    Fl_Button* btn_scan = new Fl_Button(160, 110, 150, 30, "Analyser");
    btn_scan->callback(on_scan_clicked);

    Fl_Button* btn_move = new Fl_Button(320, 110, 150, 30, "Déplacer les fichiers");
    btn_move->callback(on_move_clicked);

    output = new Fl_Multiline_Output(160, 160, 300, 100, "Résultats :");
    output->wrap(1);

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
