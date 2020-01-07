#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>


int changed = 0;
char filename[256] = "";
Fl_Text_Buffer *textbuf;



class EditorWindow: public Fl_Window {
	static constexpr char win_title[] {"TextEditor"};
	
public:
  	EditorWindow(int w, int h):Fl_Window(w, h, win_title){
  		Fl_Window *replace_dlg;
	    Fl_Input *replace_find;
	    Fl_Input *replace_with;
	    Fl_Button *replace_all;
	    Fl_Return_Button *replace_next;
	    Fl_Button *replace_cancel;
	    Fl_Text_Editor *editor;
	    char search[256];

	    editor = new Fl_Text_Editor(0, 30, 640, 370);
		editor->buffer(textbuf);

		Fl_Menu_Item menuitems[] = {
		  	{ "&File",              0, 0, 0, FL_SUBMENU},
		    { "&New File",        0},
		    { "&Open File...",    FL_COMMAND + 'o', 0},
		    { "&Insert File...",  FL_COMMAND + 'i', 0, 0, FL_MENU_DIVIDER },
		    { "&Save File",       FL_COMMAND + 's', 0},
		    { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', 0, 0, 0},
		    { "New &View", FL_ALT + 'v', 0, 0 },
		    { "&Close View", FL_COMMAND + 'w', 0, 0, FL_MENU_DIVIDER },
		    { "E&xit", FL_COMMAND + 'q', 0, 0 },
		    { 0 },
		  	{ "&Edit", 0, 0, 0, FL_SUBMENU },
		    { "&Undo",       FL_COMMAND + 'z', 0, 0, FL_MENU_DIVIDER },
		    { "Cu&t",        FL_COMMAND + 'x', 0},
		    { "&Copy",       FL_COMMAND + 'c', 0},
		    { "&Paste",      FL_COMMAND + 'v', 0},
		    { "&Delete",     0, 0},
		    { 0 },
		  	{ "&Search", 0, 0, 0, FL_SUBMENU },
		    { "&Find...",       FL_COMMAND + 'f', 0},
		    { "F&ind Again",    FL_COMMAND + 'g', 0},
		    { "&Replace...",    FL_COMMAND + 'r', 0},
		    { "Re&place Again", FL_COMMAND + 't', 0},
		    { 0 },
		  	{ 0 }
		};
		Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, 640, 30);
		m -> copy(menuitems);	
  	}
  	
};

int main(int argc, char *argv[]){
	EditorWindow *window = new EditorWindow(600, 400);

	window->end();

	window->show(argc, argv);
	return Fl::run();
}