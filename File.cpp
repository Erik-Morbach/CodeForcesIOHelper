#include "File.h"

void downloadFile(std::string &url){
    system(("wget -O X -q -t 0 -c "+url).c_str());

}

std::ifstream getFile(std::string &url){
    std::string fileName = "X";

    downloadFile(url);

    std::ifstream file(fileName.c_str());
    return file;
}

std::string getStringHTMLfromFile(std::ifstream &file){
    std::string strHTML = "";
    while(!file.eof()){
        std::string aux;
        std::getline(file,aux);
        strHTML+=aux+"\n";
    }
    system("rm X");
    return strHTML;
}



void writeFile(std::ofstream &file, std::string w){
    if(file.is_open()){
        file << w.c_str();
        file.close();
    }

}


