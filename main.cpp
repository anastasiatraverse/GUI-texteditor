#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Input.H>


int            changed = 0;
char           filename[256] = "";
Fl_Text_Buffer *textbuf;

class EditorWindow: public Fl_Double_Window {
public:
  	EditorWindow(int w, int h, const char* t);
	~EditorWindow();
    Fl_Window          *replace_dlg;
    Fl_Input           *replace_find;
    Fl_Input           *replace_with;
    Fl_Button          *replace_all;
    Fl_Return_Button   *replace_next;
    Fl_Button          *replace_cancel;
    Fl_Text_Editor     *editor;
    char               search[256];
};


int main(int argc, char *argv[]){
	std::cout<<"Hello!"<<std::endl;
	return 0;
}