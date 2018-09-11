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
			encryptr(p, argv[2]);
	}
	else{
		help("");
	}
}

/**
 * encrypts and decrypts a file
 */
void encrypt(fs::path path, const std::string key){
	std::ifstream file {path};
	std::vector<char> text;
	char buf;
	if(file.is_open()){
		while(!file.eof()){
			file.get(buf);
			text.push_back(buf);
		}
		file.close();
	}
	else{
		help("Couldn't open file " + path.string());
		exit(-1);
	}
	int l = key.length();
	for(int i = 0; i < text.size(); i++){
			text[i] = text[i] ^ key[i%l];
	}
	fs::remove(path);
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
 * encrypts and decrypts a directory recursively
 */
void encryptr(fs::path path, const std::string key){
	if(fs::is_regular_file(path)){
		encrypt(path,key);
	}
	else{
		for(auto& p : fs::directory_iterator(path)){
			encryptr(p.path(), key);
		}
	}
}

/**
 * prints help to console
 */
void help(const std::string msg){
	if(msg == ""){
		std::cout << "\nenc (v1.1) by strmc\n";
	}
	else{
		std::cout <<"\n" <<  msg << "\n";
	}
	std::cout << "\nUsage:\n";
	std::cout << "  \"enc\" pathtofileordir key\n";
}
