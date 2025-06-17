#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "ui.hpp"
#include "core/file_move.h"

// Callback exemple
void on_click(Fl_Widget*, void*) {
    // Exemple d'appel à une fonction C
    move_files("ATTENTES_SIGNATURE", "TRAITES");
}

int create_main_window(int argc, char** argv) {
    Fl_Window* win = new Fl_Window(400, 200, "FMP v0.2");

    Fl_Button* btn = new Fl_Button(150, 80, 100, 30, "Déplacer");
    btn->callback(on_click);

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
