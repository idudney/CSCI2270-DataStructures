#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/MessageDecoder.hpp"
#include "../code_2/EnqueueDequeue.hpp"


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

string test_push(char arr[], int length)
{
    MessageDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    Parser *temp = calc.getStackHead();
    cout << "Print stack from top to bottom:" << endl;
    while(temp != NULL){
        cout << temp->ch << endl;
        temp = temp->next;
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_pop(char arr[], int length)
{
    MessageDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    int flag = 0;
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            char num = calc.getStackHead()->ch;
            cout << num << endl;
            calc.pop();
            flag++;
            if(flag > 10000){
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}

string test_peek(char arr[], int length)
{
    MessageDecoder calc;
    testing::internal::CaptureStdout();
   
    for(int i=0;i<length;i++)
    {
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                char num = calc.peek()->ch;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;  
}

string test_all(char arr[], int length)
{
    MessageDecoder calc;
    testing::internal::CaptureStdout();
    
   
    for(int i=0;i<2;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout<<"poping thrice "<<endl;
    calc.pop();
    calc.pop();
    calc.pop();
    
    for(int i=2;i<length;i++)
    {
        cout<<"push: "<<arr[i]<<endl;
        calc.push(arr[i]);
    }
    
    cout << "Print stack from top to bottom:" << endl;
    if(!calc.isEmpty()){
        while(!calc.isEmpty()){
            if(calc.peek()){
                char num = calc.peek()->ch;
                cout << num << endl;
                calc.pop();
            }
            else{
                break;
            }
        }
    }
   
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}


string test_evaluate(char arr[], int length)
{
    MessageDecoder calc;
    testing::internal::CaptureStdout();
    calc.evaluate(arr);
       
    // string ss="";
    // for(int i=0;i<length;i++)
    // {
    //     ss = ss + arr[i]+" ";
    // }
    
    // if(status)
    // {
    //     cout << ss<<"= " << calc.peek()->letter << endl;
    //     calc.pop();
    //     cout<< "After computation poping"<<endl;
    //     if(!calc.peek()) 
    //         cout << "Correct!" << endl;
    //     else 
    //         cout << "should be empty." << endl;
    // }
    string output = testing::internal::GetCapturedStdout();
    return output;
    
}


string test_consQ(){
    testing::internal::CaptureStdout();
    EnqueueDequeue q;
    int front = q.getQueueFront();
    int back = q.getQueueEnd();
    if(front == -1 and back == -1) cout << "Correct!" << endl;
    else cout << "front and back are not -1, check constructor" << endl;
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_enQ(string show, int length){
    
    EnqueueDequeue queue;
    testing::internal::CaptureStdout();
    for(int i = 0; i < length; i++)
    {
        string s = show + to_string(i);
        queue.enqueue(s);
    }
    string* q = queue.getQueue();
    int front = queue.getQueueFront();
    int size = queue.queueSize();
    cout << "Print queue from front to back:" << endl;
    for(int i = front; i <= (front + size - 1) % length; i++) 
        cout << q[i] << endl;
   
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_deQ(string show, int length, int dequeue)
{
    EnqueueDequeue queue;
    testing::internal::CaptureStdout();
   
    for(int i = 0; i < length; i++)
    {
        string s = show + to_string(i);
        queue.enqueue(s);
    }
    
    cout<< "dequeuing "<< dequeue <<" times"<<endl;
    for(int i = 0; i < dequeue; i++)
    {
        queue.dequeue();
    }
    int front = queue.getQueueFront();
    int back = queue.getQueueEnd();
    string* q = queue.getQueue();

    if(length > dequeue)
    {
        cout << "Print queue from front to back:" << endl;
        if(!queue.isEmpty())
            for(int i = front; i <= back; i++) cout << q[i] << endl;
    }
    
    string output = testing::internal::GetCapturedStdout();
    return output;   
}

string test_peekQ(string show, int length, int deQ)
{
    EnqueueDequeue queue; //by default size is 5 so not passing length to constructor
    testing::internal::CaptureStdout();
     
    cout << "enqueuing " << length << " elements" << endl;
    for(int i = 0; i < length; i++)
    {
        string s = show+to_string(i);
        queue.enqueue(s);
    }
    
    cout << "dequeuing " << deQ << " times" << endl;
    for(int i = 0; i < deQ; i++)
    {
        queue.dequeue();
    }
    
    cout << "peeking in the queue" << endl;
    string it = queue.peek();
    
    if(it != "")
    {
        cout << "Front of the queue: " << it << endl;
    } else {
        cout << it << endl;
    }
    string output = testing::internal::GetCapturedStdout();

    return output;
}
    
    
string test_allQ(string show, string* op, int length)
{
    EnqueueDequeue q;
    testing::internal::CaptureStdout();

    int enq = 0;
    for(int i = 0; i < length; i++)
    {
        if(op[i] == "E")
        {
            string c = show + to_string(enq);
            cout << "Enqueue(" << c << ")" << endl;
            q.enqueue(c);
            enq++;
        }
        else if(op[i] == "D")
        {
            cout << "Dequeue" << endl;
            q.dequeue();
        }
        else if(op[i] == "P")
        {
            cout << "Peek" << endl;
            string it = q.peek();
            cout << it << endl;
        }
    }
    string full = q.isFull() ? "true" : "false";
    cout << "Queue is full? " << full << endl;
    
    string empty = q.isEmpty() ? "true" : "false";
    cout << "Queue is empty? " << empty << endl;
    
    cout << "Queue size: " << q.queueSize() << endl;
    cout << "Queue front index: " << q.getQueueFront() << endl;
    cout << "Queue back index: " << q.getQueueEnd() << endl;
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}
