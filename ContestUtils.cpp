#include "ContestUtils.h"

std::vector<std::string> getContestProblemsURLs(std::string baseUrl){
    int contestId = stoi(baseUrl.substr(baseUrl.rfind("/")+1));
    std::vector<std::string> ans;
    std::ifstream file = getFile(baseUrl);
    HTML html(file);
    std::string between = html.getHTMLBetween("<table class=\"problems\">","</table>");

    while(searchNextProblemName(between,ans,contestId));
    return ans;
}



bool searchNextProblemName(std::string &partialHTML,std::vector<std::string> &ans, int contestId){
    std::string next;
    std::string base = "/contest/"+std::to_string(contestId)+"/problem/";
    std::size_t indx = partialHTML.find(base);
    if(indx==std::string::npos) return false;
    partialHTML = partialHTML.substr(indx);
    next = partialHTML.substr(0,partialHTML.find("\""));
    next = "https://codeforces.com"+next;
    partialHTML = partialHTML.substr(partialHTML.find(base)+1);
    partialHTML = partialHTML.substr(partialHTML.find(base)+1);
    ans.push_back(next);

    return true;
}
