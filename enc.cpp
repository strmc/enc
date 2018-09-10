#include "enc.h"

/**
 * main method
 * parses commandline arguments
 */
int main(int argc, char** argv){
	if(argc ==  4){
		if(argv[1] == "-e" || argv[1] == "-d"){
			char* path;
			std::string test {argv[2]};
			if(test[0] != '/'){
				getcwd(path, 200);
				strcat(path, argv[2]);
			}
			else{
				path = argv[2];
			}
			if(argv[1] == "-e"){
				encrypt(path, argv[3]);
			}
			else if(argv[1] == "-d"){
				decrypt(path, argv[3]);
			}
		}
		else{
			help(strcat("Unknown option ", argv[1]));
			return(-1);
		}
	}
	else{
		help("");
	}
}

/**
 * encrypts a file
 */
void encrypt(char* path, const char* key){
	std::ifstream file {path};
	std::vector<char> text;
	std::string buf;
	if(file.is_open()){
		while(!file.eof()){
			file.read(buf,100);
			for(char c : buf){
				text.push_back(c);
			}
		}
		file.close();
	}
	else{
		help(strcat("Couldn't open file ", path));
		exit(-1);
	}
	int l = std::strlen(key);
	for(int i = 0; i < text.size(); i++){
		text[i] = text[i] ^ key[i%l];
	}
	strcat(path, ".enc");
	std::ofstream encfile {path};
	for(char c : text){
		encfile << c;
	}
	encfile.close();
}

/**
 * decrypts a file
 */
void decrypt(char* path, const char* key){
	
}

/**
 * prints help to console
 */
void help(const char* msg){
	if(msg = ""){
		std::cout << "\nenc (v0.1) by strmc\n";
	}
	else{
		std::cout <<"\n" <<  msg << "\n";
	}
	std::cout << "\nUsage:\n";
	std::cout << "  \"enc\" \"-e\" pathtofile key\n";
	std::cout << "  \"enc\" \"-d\" pathtofile key\n";
}
