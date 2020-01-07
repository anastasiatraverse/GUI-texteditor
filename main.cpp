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
#include <FL/Fl_Choice.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>

int changed = 0;
char filename[256] = "";
Fl_Text_Buffer *textbuf;
int loading =0;
int check_save= 1;

class EditorWindow: public Fl_Window {
	static constexpr char win_title[] {"Text Editor"};
	static void changed_cb(){}

	static void load_file(char* newfile, int ipos){
		loading = 1;
		int insert = (ipos != -1);
		if (!insert) strcpy(filename, "");
		int r;
		if (!insert) r = textbuf->loadfile(newfile);
		else r = textbuf->insertfile(newfile, ipos);
		if (r)
			fl_alert("Error reading from file \'%s\':\n%s.", newfile, strerror(errno));
		else 
			if (!insert) strcpy(filename, newfile);
		loading = 0;
  		textbuf->call_modify_callbacks();
	}
	static void quit_cb(Fl_Widget* menu, void* main_window_in){
		EditorWindow* main_window = static_cast<EditorWindow*>(main_window_in);
        main_window->hide();
	}
	static void open_cb(Fl_Widget* menu, void* main_window_in){
		if (!check_save) return;
		char *newfile = fl_file_chooser("Open File?", "*", filename);
		if (newfile != NULL) load_file(newfile, -1);
	}
	static void paste_cb(){}
	static void new_cb(){}
	static void find_cb(){}
	static void delete_cb(){}
	static void cut_cb(){}
	static void copy_cb(){}
	static void save_cb(){}
	static void saveas_cb(){}
	static void undo_cb(){}
	static void replace_cb(){}
	static void replaceall_cb(){}

	Fl_Window *replace_dlg;
	Fl_Input *replace_find;
	Fl_Input *replace_with;
	Fl_Button *replace_all;
	Fl_Return_Button *replace_next;
	Fl_Button *replace_cancel;
	Fl_Text_Editor *editor;
	char search[256];

public:
  	EditorWindow(int w, int h):Fl_Window(w, h, win_title){
	    editor = new Fl_Text_Editor(0, 30, 640, 370);
		editor->buffer(textbuf);
		editor ->textfont(FL_COURIER);

		Fl_Menu_Item menuitems[] = {
		  	{ "&File",              0, 0, 0, FL_SUBMENU},
		    { "&New File",        0},
		    { "&Open File...",    FL_COMMAND + 'o', (Fl_Callback *)open_cb},
		    { "&Insert File...",  FL_COMMAND + 'i', 0, 0, FL_MENU_DIVIDER },
		    { "&Save File",       FL_COMMAND + 's', (Fl_Callback*)save_cb},
		    { "Save File &As...", FL_COMMAND + FL_SHIFT + 's', (Fl_Callback*)saveas_cb, 0, FL_MENU_DIVIDER},
		    { "E&xit", FL_COMMAND + 'q',(Fl_Callback *)quit_cb, 0},
		    { 0 },
		  	{ "&Edit", 0, 0, 0, FL_SUBMENU },
		    { "&Undo",       FL_COMMAND + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
		    { "Cu&t",        FL_COMMAND + 'x', (Fl_Callback *)cut_cb},
		    { "&Copy",       FL_COMMAND + 'c', (Fl_Callback *)copy_cb},
		    { "&Paste",      FL_COMMAND + 'v', (Fl_Callback *)paste_cb},
		    { "&Delete",     0, 0},
		    { 0 },
		  	{ "&Search", 0, 0, 0, FL_SUBMENU },
		    { "&Find...",       FL_COMMAND + 'f', (Fl_Callback *)find_cb},
		    { "&Replace...",    FL_COMMAND + 'r', (Fl_Callback *)replace_cb},
		    { "Re&place Again", FL_COMMAND + 't', (Fl_Callback *)replaceall_cb},
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

// int main() {
//      Fl_Double_Window *win  = new Fl_Double_Window(640, 480, "Simple Fl_Text_Editor");
//      Fl_Text_Buffer   *buff = new Fl_Text_Buffer();
//      Fl_Text_Editor   *edit = new Fl_Text_Editor(20, 20, 640-40, 480-40);
//      edit->buffer(buff);		// attach the text buffer to our editor widget
//      win->resizable(*edit);
//      win->show();

//      return(Fl::run());
// }