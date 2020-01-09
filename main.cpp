#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

char filename[256] = "";
bool check_save = true;
int loading =0;
bool changed = false;
Fl_Text_Buffer *buff;

void to_text_buff(std::vector<std::string> v){
	std::string all = "";
	for(auto el:v)
		all+=el;

	const char *c = all.c_str();

	buff->text(c);
}

void load_file(char *file_path){
	std::cout<<file_path<<std::endl;
	std::string p = file_path;
	std::vector<std::string> lines;
	loading = 1;	
	std::ifstream myfile(p);
	std::string line;
	if (myfile.is_open()){
	    while ( getline (myfile,line)) lines.push_back(line+"\n");
	    myfile.close();
	}
	else fl_alert("Error reading from file \'%s\':\n%s.", file_path, strerror(errno));
	to_text_buff(lines);
}

void open_cb(Fl_Widget* menu, void* main_window_in){
	if (!check_save) return;
	char *newfile = fl_file_chooser("Open File?", "*", filename);
	if (newfile != NULL) load_file(newfile);
}

void save_file(char *newfile){
	if(buff->savefile(newfile)) fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
	else strcpy(filename, newfile);
  	changed = false;
  	buff->call_modify_callbacks();
}

void saveas_cb(){
	char *newfile;
	newfile = fl_file_chooser("Save File As?", "*", filename);
  	if (newfile != NULL) save_file(newfile);
}

void save_cb(Fl_Widget* menu, void* main_window_in){
	if (filename[0] == '\0') {
    	// No filename - get one!
    	saveas_cb();
    	return;
  	}
  	else save_file(filename);
}



void quit_cb(Fl_Widget* menu, void* main_window_in){
	// Fl_Window * main_window = static_cast<Fl_Window*>(main_window_in);
	// main_window-> hide();
	exit(0);
}
void undo_cb(Fl_Widget* menu, void* main_window_in){}
void copy_cb(Fl_Widget* menu, void* main_window_in){}
void cut_cb(){}
void paste_cb(){}
void find_cb(){}
void replace_cb(){}
void replaceall_cb(){}

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

int main(int argc, char *argv[]){
	Fl_Double_Window *win  = new Fl_Double_Window(680, 520, "Simple Text Editor");
    buff = new Fl_Text_Buffer();
    Fl_Text_Editor   *edit = new Fl_Text_Editor(20, 40, 660-40, 500-40);
    edit->buffer(buff);		// attach the text buffer to our editor widget
    win->resizable(*edit);
    Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, 640, 30);
	m -> copy(menuitems);
    win->show();
    return (Fl::run());
}