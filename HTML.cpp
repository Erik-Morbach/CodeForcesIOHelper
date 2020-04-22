#include "HTML.h"

HTML::HTML(std::string strHTML){
    this->strHTML = strHTML;
    index = 0;
}
HTML::HTML(std::ifstream &file){
    this->strHTML = getStringHTMLfromFile(file);
    index = 0;
}
void HTML::computeHTML(){
   // std::cout<<"HTML Map begin!!"<<std::endl;
    index  = 0;
    inputs.clear();
    outputs.clear();
    int qnt = 0;
    while(nextInputAndOutput()) qnt++;
   // std::cout<<"HTML Map End!!"<<std::endl;
   // std::cout<<qnt<<" inputs & outputs Find"<<std::endl;
}

std::string* HTML::getClass(const std::string &classForSearch){
    int novo = this->index;
    std::string_view htmlaux {strHTML} ;
    htmlaux = htmlaux.substr(this->index);
    std::size_t beginIndexClass = htmlaux.find(classForSearch);

    if(beginIndexClass==std::string::npos){
        return nullptr;
    }
    novo+=beginIndexClass;
    htmlaux = htmlaux.substr(beginIndexClass);
    std::size_t beginIndex = htmlaux.find("<pre>")+6;
    novo+=beginIndex;
    htmlaux = htmlaux.substr(beginIndex);

    std::size_t endIndex = htmlaux.find("</pre>");
    novo+=endIndex;

    std::string_view auxi = htmlaux.substr(0,endIndex);

    std::string *classSearched = new std::string(auxi.begin(),auxi.end());

    htmlaux = htmlaux.substr(endIndex);
    this->index = novo;
    return classSearched;
}
bool HTML::nextInputAndOutput(){
    std::string *input  = getClass(this->HTMLINPUTCLASS);
    if(input==nullptr) return false;
    std::string *output = getClass(this->HTMLOUTPUTCLASS);
    this->inputs.push_back(*input);
    this->outputs.push_back(*output);
    return true;
}

std::string HTML::getHTMLBetween(std::string initialTag,std::string endTag) const{
    std::size_t beginIndex = this->strHTML.find(initialTag);

    std::size_t endIndex = this->strHTML.substr(beginIndex).find(endTag)+beginIndex;
    return this->strHTML.substr(beginIndex, endIndex);
}

/*
while have inputs
    pick Input & Output()


pick Input & Output()
    pick input begin index
    pick input end index
    pick input

    pick output begin index
    pick output end index
    pick output


*/
