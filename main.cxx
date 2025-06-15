#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <stdlib.h>

// Fonction appelée quand on clique sur le bouton
void on_button_click(Fl_Widget* w, void* data) {
    system("/home/hazefury/Code/solo/FileMoveProtocol/File-Move-Protocol/file_move_protocol.sh"); // Remplace par le chemin absolu vers ton script
}

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(400, 200, "FMP v0.1");

    Fl_Button *btn = new Fl_Button(100, 80, 200, 40, "Déplacer les fichiers");
    btn->callback(on_button_click);  // Associe la fonction au clic

    window->end();
    window->show(argc, argv);
    return Fl::run();
}
