#include "utils.h"

Fl_Menu_Item menuitems[] = {
		  	{ "&File",              0, 0, 0, FL_SUBMENU},
		    { "&New File",        0, (Fl_Callback*)new_cb},
		    { "&Open File...",    FL_COMMAND + 'o', (Fl_Callback *)open_cb},
		    { "&Insert File...",  FL_COMMAND + 'i', 0, 0, FL_MENU_DIVIDER },
		    { "&Save File",       FL_COMMAND + 's', (Fl_Callback*)save_cb},
		    { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback*)saveas_cb, 0, FL_MENU_DIVIDER},
		    { "E&xit", FL_COMMAND + 'q',(Fl_Callback *)quit_cb, 0},
		    { 0 },
		  	{ "&Edit", 0, 0, 0, FL_SUBMENU },
		    { "Cu&t",        FL_COMMAND + 'x', (Fl_Callback *)cut_cb},
		    { "&Copy",       FL_COMMAND + 'c', (Fl_Callback *)copy_cb},
		    { "&Paste",      FL_COMMAND + 'v', (Fl_Callback *)paste_cb},
		    { "&Delete",     0, (Fl_Callback*)delete_cb},
		    { 0 },
		  	{ "&Search", 0, 0, 0, FL_SUBMENU },
		    { "&Find...",       FL_COMMAND + 'f', (Fl_Callback *)find_cb},
		    { "&Replace...",    FL_COMMAND + 'r', (Fl_Callback *)replace_cb},
		    { "Re&place Again", FL_COMMAND + 't', (Fl_Callback *)replaceall_cb},
		    { 0 },
		  	{ 0 }
};


int main(int argc, char *argv[]){

	Fl_Double_Window *win  = new Fl_Double_Window(680, 520, "Simple Text Editor");
    buff = new Fl_Text_Buffer();
    editor = new Fl_Text_Editor(20, 40, 660-40, 500-40);
    editor->buffer(buff);		// attach the text buffer to our editor widget
    win->resizable(editor);
    Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, 640, 30);

	m -> copy(menuitems);

	if(argc-1>0) load_file(argv[1]);

    win->show();


    return (Fl::run());
}
