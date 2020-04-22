#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "File.h"
#include "HTML.h"
#include "ContestUtils.h"

const std::string base = "/home/erik";
const std::string contestPath  = base+"/dev/Codeforces/Contests";
const std::string problemsPath = base+"/dev/Codeforces/Problems";
const std::string contestSolutionsPath = base+"/dev/Codeforces/Solutions/Contests";
const std::string problemSolutionsPath = base+"/dev/Codeforces/Solutions/Problems";

const std::string templateFilePath = base+"/dev/Template.cxx";

const std::string problemsetURLPrefix = "https://codeforces.com/problemset";
const std::string contestURLPrefix    = "https://codeforces.com/contest";

std::string urlPrefix;
int main()
{
    std::cout<< "(1) Contest"<<std::endl;
    std::cout<< "(2) ProblemSet"<<std::endl;
    int option = -1;
    std::cin>>option;
    std::vector<std::string> problems;
    std::vector<std::string> paths;

    std::string contestNumber;
    std::string thisContestIOPath;
    std::string thisContestSolutionPath;


    std::string data;
    std::string thisProblemsetIOPath;
    std::string thisProblemsetSolutionPath;
    switch(option){
    case 1:
        urlPrefix = contestURLPrefix;
        std::cout<<"Insert the contest number:";
        std::cin>>contestNumber;

        thisContestSolutionPath = contestSolutionsPath+"/"+contestNumber;

        thisContestIOPath = contestPath+"/"+contestNumber;

        system(("mkdir "+thisContestIOPath).c_str());
        urlPrefix+="/"+contestNumber;
        problems = getContestProblemsURLs(urlPrefix);

        system(("mkdir "+thisContestSolutionPath).c_str());
        for(auto w: problems){
            std::string problemName = w.substr(w.rfind("/")+1);
            paths.push_back(thisContestIOPath+"/"+problemName);

            std::string thisProblemPath = thisContestSolutionPath+"/"+problemName+".cxx";
            system(("touch "+thisProblemPath).c_str());
            system(("cat "+templateFilePath+" >> "+thisProblemPath).c_str());
        }

        break;
    case 2:
        int qntProblems = 0;
        std::cout<<"Insert today's date(dd:mm:yyyy)";
        std::cin>>data;
        thisProblemsetIOPath = problemsPath+"/"+data;
        system(("mkdir "+thisProblemsetIOPath).c_str());


        thisProblemsetSolutionPath = problemSolutionsPath+"/"+data;
        system(("mkdir "+thisProblemsetSolutionPath).c_str());

        std::cout<<"Insert the quantity of problems you will try to solve:";
        std::cin>>qntProblems;
        std::cout<<"Insert "<<qntProblems<<" URLs."<<std::endl;
        for(int i=0;i<qntProblems;i++){
            std::cin >> urlPrefix;
            problems.push_back(urlPrefix);

            std::size_t beginProblemName = urlPrefix.rfind("/");

            std::string problem = urlPrefix.substr(beginProblemName+1);
            std::string urlPrefixAux = urlPrefix.substr(0,beginProblemName);

            std::string contestOfProblem = urlPrefixAux.substr(urlPrefixAux.rfind("/")+1);

            std::string problemId = problem+"-"+contestOfProblem;

            paths.push_back(problemsPath+"/"+data+"/"+problemId);

            std::string thisProblemPath = thisProblemsetSolutionPath+"/"+problemId+".cxx";
            system(("touch "+ thisProblemPath).c_str());
            system(("cat "+templateFilePath+" >> "+thisProblemPath).c_str());
        }
        break;

    }
    std::cout<< "Problems Have been Load, the program will process they and put your inputs/outputs in:"+(option==1?thisContestIOPath:thisProblemsetIOPath)<<std::endl;
    std::cout<< "The Source Files for solving them are in:"+(option==1?thisContestSolutionPath:thisProblemsetSolutionPath)<<std::endl;
    std::vector<HTML> problemsHTML;
    for(int i=0;i<problems.size();i++){
        system(("mkdir "+paths[i]).c_str());

        std::ifstream fileProblem = getFile(problems[i]);
        problemsHTML.push_back(fileProblem);
        int number = 1;
        problemsHTML.back().computeHTML();
        for(std::string w: problemsHTML[i].getInputs()){
            std::string caminho = paths[i]+"/in"+std::to_string(number++);
            system(("touch "+caminho).c_str());
            std::ofstream infile(caminho);
            writeFile(infile,w);
        }
        number = 1;
        for(std::string w: problemsHTML[i].getOutputs()){
            std::string caminho = paths[i]+"/out"+std::to_string(number++);
            system(("touch "+caminho).c_str());
            std::ofstream offile(caminho);
            writeFile(offile,w);
        }


    }
    std::cout<<"Inputs and Outputs Of the problems are now avaliable!!"<<std::endl;
    std::cout<<"Good Luck!"<<std::endl;
    return 0;
}

