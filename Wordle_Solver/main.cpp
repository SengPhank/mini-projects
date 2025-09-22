#include <iostream>
#include <wx/wx.h>
#include "Possible_Words.h"
#include "gui/Frame.h"

class MainApp : public wxApp {
    public:
        // On App run
        bool OnInit() override;

};

// On App run (main function)
bool MainApp::OnInit() {
    // Run Program
    std::cout << "Running!" << std::endl;
    // === Create window ===
    Frame* mainFrame = new Frame("Wordle Solver");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();

    // Complet and Show the window
    mainFrame->Show();
    std::cout << "Window Running!" << std::endl;
    return true;
}

wxIMPLEMENT_APP(MainApp);