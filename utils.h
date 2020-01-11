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
char search[256] = "";
int check_save = 0;
int loading =0;
int changed = 0;
Fl_Text_Buffer *buff;
Fl_Text_Editor *editor;
Fl_Window *replace_dlg;

void replace_dialog_win(){
	Fl_Window *replace_dlg = new Fl_Window(300, 105, "Replace");
	Fl_Input *replace_find = new Fl_Input(70, 10, 200, 25, "Find:");
	Fl_Input *replace_with = new Fl_Input(70, 40, 200, 25, "Replace:");
	Fl_Button *replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
	Fl_Button *replace_next = new Fl_Button(105, 70, 120, 25, "Replace Next");
	Fl_Button *replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
}

void changed_bd(Fl_Widget* menu, void* main_window_in){

}

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
	// if (!check_save) return;
	char *newfile = fl_file_chooser("Open File?", "*", filename);
	if (newfile != NULL) load_file(newfile);
}

void new_cb(Fl_Widget* menu, void* main_window_in){
	filename[0] = '\0';
  	buff->select(0, buff->length());
  	buff->remove_selection();
  	changed = 0;
  	buff->call_modify_callbacks();
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

void undo_cb(Fl_Widget* menu, void* main_window_in){

}

void copy_cb(Fl_Widget* menu, void* main_window_in){
	Fl_Window* main = static_cast<Fl_Window*>(main_window_in);
	Fl_Text_Editor::kf_copy(0, editor);
}

void cut_cb(Fl_Widget* menu, void* main_window_in){
	Fl_Window* main = static_cast<Fl_Window*>(main_window_in);
	Fl_Text_Editor::kf_cut(0, editor);
}

void paste_cb(Fl_Widget* menu, void* main_window_in){
	Fl_Window* main = static_cast<Fl_Window*>(main_window_in);
	Fl_Text_Editor::kf_paste(0, editor);
}

void delete_cb(Fl_Widget* menu, void* main_window_in){
	buff->remove_selection();
}


void find_cb(Fl_Widget* menu, void* main_window_in);
void find2(Fl_Widget* menu, void* main_window_in);

void find_cb(Fl_Widget* menu, void* main_window_in){
	const char *val;
	val = fl_input("Search String:", search);
	if (val != NULL) {
	    strcpy(search, val);

	    std::cout<<search<<std::endl;

	    find2(menu, main_window_in);
	}
}

void find2(Fl_Widget* menu, void* main_window_in){
	if (search[0] == '\0') {
		find_cb(menu, main_window_in);
		return;
	}
	int pos = editor->insert_position();
  	int found = buff->search_forward(pos, search, &pos);
  	if (found) {
	    buff->select(pos, pos+strlen(search));
	    editor->insert_position(pos+strlen(search));
	    editor->show_insert_position();
  	}
}

void replace_cb(Fl_Widget* menu, void* main_window_in){
	replace_dlg -> show();
}

void replaceall_cb(){
	std::cout<<"replace all function call"<<std::endl;
}