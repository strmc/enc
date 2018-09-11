#include "enc.h"

/**
 * main method
 * parses commandline arguments
 */
int main(int argc, char** argv){
	if(argc ==  3){
			fs::path p{argv[1]};
			if(p.is_relative()){
				p = fs::current_path() / p;
			}
			encrypt(p, argv[2]);
	}
	else{
		help("");
	}
}

/**
 * encrypts a file
 */
void encrypt(fs::path path, const std::string key){
	std::ifstream file {path};
	std::vector<char> text;
	std::string buf;
	if(file.is_open()){
		while(!file.eof()){
			file >> buf;
			for(char c : buf){
				text.push_back(c);
			}
		}
		file.close();
	}
	else{
		help("Couldn't open file " + path.string());
		exit(-1);
	}
	int l = key.length();
	for(int i = 0; i < text.size(); i++){
		if(!(std::isspace(text[i]))){
			text[i] = text[i] ^ key[i%l];
		}
	}
	if(path.extension() == ".enc"){
		path.replace_extension("");
	}
	else{
		path += ".enc";
	}
	std::ofstream encfile {path};
	for(char c : text){
		encfile << c;
	}
	encfile.close();
}

/**
 * prints help to console
 */
void help(const std::string msg){
	if(msg == ""){
		std::cout << "\nenc (v0.1) by strmc\n";
	}
	else{
		std::cout <<"\n" <<  msg << "\n";
	}
	std::cout << "\nUsage:\n";
	std::cout << "  \"enc\" pathtofile key\n";
}
