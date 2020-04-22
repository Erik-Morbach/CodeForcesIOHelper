#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <string_view>
#include <functional>
#include "File.h"

class HTML{
public:
    HTML(){ index = 0; };
    HTML(std::string strHTML);
    HTML(std::ifstream &file);

    std::string getHTMLBetween(std::string initialTag,std::string endTag) const;

    void computeHTML();

    std::vector<std::string> getInputs() const{ return inputs; };
    std::vector<std::string> getOutputs() const{ return outputs; };
    const std::string HTMLINPUTCLASS = "<div class=\"title\">Input</div>" ;
    const std::string HTMLOUTPUTCLASS= "<div class=\"title\">Output</div>";
private:
    bool nextInputAndOutput();
    std::string* getClass(const std::string &classForSearch);
    int index;
    std::string strHTML;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};
