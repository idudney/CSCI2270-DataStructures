#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/ShowsList.hpp"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}


string test_removeShow(string name, bool build)
{
    ShowsList showsNet;
    testing::internal::CaptureStdout();
    if(build)
    {
        showsNet.buildShowsList();
        cout << "** Default list constructed **" << endl;
    }
    showsNet.displayShows();
    cout << "** Deleting "+ name +"!" << endl;
    showsNet.removeShows(name);
    showsNet.displayShows();
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}


string test_purgeCompleteShowList(bool build)
{
    ShowsList showsNet;
    testing::internal::CaptureStdout();
    if(build)
    {
        showsNet.buildShowsList();
        cout << "** Default list constructed **" << endl;
    }
    cout << "** Calling purgeCompleteShowList()" << endl;
    showsNet.purgeCompleteShowList();
    string op;
    if(showsNet.isEmpty()) op = "True";
    else op = "False";
    cout << "** Does head == NULL? (true if network was deleted): " << op << endl;
        
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}

string test_findGlitch(string name, bool build)
{
    ShowsList showsNet;
    testing::internal::CaptureStdout();
    
    if(build)
    {
        showsNet.buildShowsList();
        cout << "** Default list constructed **" << endl;
    }
    cout<< "** Creating loop to "<<name<<endl;
    Show* last = showsNet.produceGlitch(name);
    cout << "** Calling findGlitch()" << endl;
    bool isLoop = showsNet.findGlitch();
    if(isLoop && last->next->name == name)
    {
       cout<< "Loop is detected"<<endl;
       cout<< "** Breaking the loop"<<endl;
       last->next = NULL;
    }
    else if (isLoop && last->next->name != name)
    {
       cout << "Loop is detected but at incorrect node" << endl;
    return 0;
    }
    else
       cout<< "No loop found"<<endl;

    cout << "** Calling displayShows()" << endl;
    showsNet.displayShows();
    string output = testing::internal::GetCapturedStdout();
    
    return output;

}
    

string test_rearrangeShowList(int start, int end, bool build)
{
    ShowsList showsNet;
    testing::internal::CaptureStdout();
    //cout << "** Default network constructed" << endl;
    
    if(build)
    {
        showsNet.buildShowsList();
        cout << "** Default list constructed **" << endl;
    }


    cout<< "** Shows list before rearrangement"<<endl;
    showsNet.displayShows();
    cout<<"== After rearrangement =="<<endl;
    showsNet.rearrangeShowList(start,end);
    showsNet.displayShows();
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}
