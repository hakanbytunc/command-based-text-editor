#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
    string lineInLinkedList;
    Node* next;
};

void displayAll(Node *linkedList){
    Node *tempForPrint = new Node;
    tempForPrint = linkedList;
    int i=1;
    while (tempForPrint!=NULL){
        cout <<i<<"-)"<< tempForPrint -> lineInLinkedList << endl;
        tempForPrint = tempForPrint -> next;
        i++;
    }
}


int openAndReadFile(Node *creator,string filename){
    int countPage=1;
    int countLine = 1;
    string lineFromText;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        Node* temp = new Node;
        temp = creator;
        while ( getline (myfile,lineFromText) )
        {
            temp -> lineInLinkedList = lineFromText;
            temp->next=new Node;
            temp = temp->next;
            countLine++;
            if (countLine%10==0){
                countPage++;
            }
        }
    }
    else {
        cout << "Unable to open file";
    }
    return countPage;
}
void displayByPage(Node *linkedList,int pageNumber){
    cout << "---Page number "<<pageNumber<< " starts"<<endl;
    Node *tempForPrint = new Node;
    tempForPrint = linkedList;
    int i =1;
    int k =0;
    if (pageNumber==1){
        while (tempForPrint!=NULL && i<=10){
            cout <<i<<"-)"<< tempForPrint -> lineInLinkedList << endl;
            tempForPrint = tempForPrint->next;
            i++;
        }
    }
    else {
        for(int j=0; j<((pageNumber*10)-10);j++){
            tempForPrint = tempForPrint -> next;
        }
        while (tempForPrint!=NULL && k<10){
            cout <<k+((pageNumber*10)-10)<<"-)"<< tempForPrint -> lineInLinkedList << endl;
            tempForPrint = tempForPrint -> next;
            k++;
        }
    }
    cout << "---Page number "<<pageNumber<< " ends"<<endl<<endl;
}
void writeAndSave(string filename,Node *writeThisLinkedList){
    ofstream myfile (filename);
    ofstream tempTXT;
    tempTXT.open("temp.txt");
    Node *temp = writeThisLinkedList;
    if (myfile.is_open())
    {
        while (temp->next!=NULL){
            tempTXT << temp->lineInLinkedList <<endl;
            temp=temp->next;}
        tempTXT.close();
        myfile.close();
        
        remove(filename.c_str());
        rename("temp.txt",filename.c_str());
        
    }
    else cout << "Unable to open file";
}

string lineParser(string line, string words[])
{
    string word = "";
    line = line + " ";
    int array_index = 0;
    int number_of_words = 1;
    int string_index = 0;
    while (string_index < line.length())
    {
        if (line.substr(string_index,1) != " ")
        {
            int j = string_index;
            while (line.substr(j,1) != " ")
            {
                word += line.substr(j,1);
                j++;
            }
            words[array_index] = word;
            array_index++;
            word = "";
            number_of_words++;
            string_index = j;
        }
        else
        {
            string_index++;
        }
    }
    
    return *words;
}



void chooseCommandAndRun(Node *creator,string parsedWord[]){
    int pageCounter;
    if (parsedWord[0]=="open"){
        Node *creator2 = new Node;
        creator2 = creator;
        pageCounter=openAndReadFile(creator2,parsedWord[1]);
        
    }
    if (parsedWord[0]=="save"){
        cout<<"It's saved. To exit, type exit."<<endl;
    }
    
    return;
}

Node deleteLine(Node *LinkListToDelete,int deletedLineNumber){
    Node *p = LinkListToDelete;
    for(int c=0;c<deletedLineNumber-2 && p!=NULL;++c)
    {
        p = p->next;
    }
    p->next=p->next->next;
    p=LinkListToDelete;
    cout << deletedLineNumber <<"'TH LINE DELETED SUCCESFULLY" << endl;
    
    return *p;
}
Node insertLine(Node *LinkListToInsert,int insertedLineNumber,string insertedLine){
    Node *p = LinkListToInsert;
    Node* temp=new Node;
    if (insertedLineNumber!=1){
        for(int c=0;c<insertedLineNumber-2 && p!=NULL;++c)
        {
            p = p->next;
        }
        temp->lineInLinkedList=insertedLine;
        temp->next=p->next;
        p->next=temp;
        p=LinkListToInsert;
        cout<<"inserted 1 dışındasın "<<insertedLineNumber<<endl;
    }
    else if (insertedLineNumber==1){
        temp->lineInLinkedList=insertedLine;
        temp->next=p;
        p=temp;
        free(temp);
        cout<<"inserted 1'dasın' "<<insertedLineNumber<<endl;
    }
    
    return *p;
}
void moveLine(Node *LinkedListTobeMoved,int moveThis,int moveHere){
    Node *temp1= new Node;
    Node *temp2= new Node;
    Node *temp3= new Node;

    temp1=LinkedListTobeMoved;
    temp3=LinkedListTobeMoved;
    
    int i=0;
    int j=0;
    while (i<moveThis-1){
        temp1=temp1->next;
        i++;
    }
    
    temp2->lineInLinkedList=temp1->lineInLinkedList;
    temp1->lineInLinkedList=" ";
    while (j<moveHere-2){
        temp3=temp3->next;
        j++;
    }
    temp2->next=temp3->next;
    temp3->next=temp2;
    
    return;
}

void replaceLine(Node *LinkedListTobeMoved,int replaceThis,string replaceWithThis){
    Node *temp1= new Node;
    temp1=LinkedListTobeMoved;
    
    int i=0;
    while (i<replaceThis-1){
        temp1=temp1->next;
        i++;
    }
    temp1->lineInLinkedList=" ";
    temp1->lineInLinkedList=replaceWithThis;
    
    return;
}

int main(int argc, const char * argv[]) {
    int pageNumber=1;
    Node* lineNode = new Node;
    string filenameForAll;
    cout<< "--Welcome to my text-editor-- "<<endl;
    cout<<"--Enter exit to exit--" << endl;
    cout<< "Enter your command: "<<endl;
    string command;
    getline(cin,command);
    string words[100];
    bool exit=0;
    lineParser(command, words);
    chooseCommandAndRun(lineNode,words);
    if (words[0]=="open"){
        filenameForAll=words[1];
    }
    if (words[0]=="exit"){
        exit=1;
    }
    displayByPage(lineNode, pageNumber);
    while (!exit){
        cout<< "Enter your next command: "<<endl;
        getline(cin,command);
        lineParser(command, words);
        chooseCommandAndRun(lineNode,words);
        if (words[0]=="open"){
            cout<<"You've change the file. Hope you saved before you change :)" << endl;
            filenameForAll=words[1];
            displayByPage(lineNode, pageNumber);
        }
        if (words[0]=="save"){
            writeAndSave(filenameForAll, lineNode);
        }
        if (words[0]=="next"){
            pageNumber++;
            displayByPage(lineNode, pageNumber);
        }
        else if (words[0]=="prev"){
            pageNumber--;
            if(pageNumber<=0){
                cout<<"THERE IS NO 0'TH PAGE.."<<endl;
                pageNumber=0;
            }
            else {
                displayByPage(lineNode, pageNumber);
            }
        }
        else if (words[0]=="delete"){
            *lineNode=deleteLine(lineNode, stoi(words[1]));
            displayByPage(lineNode, pageNumber);
        }
        else if (words[0]=="insert"){
            string insertedString;
            int i=2;
            while (words[i]!="\0"){
                insertedString+=words[i];
                insertedString+=" ";
                i++;
            }
            insertLine(lineNode, stoi(words[1]), insertedString);
            displayByPage(lineNode, pageNumber);
            i=0;
            while (words[i]!="\0"){
                words[i]="";
                i++;
            }
        }
        else if (words[0]=="replace"){
            string replacedString;
            int j=2;
            while (words[j]!="\0"){
                replacedString+=words[j];
                replacedString+=" ";
                j++;
            }
            replaceLine(lineNode, stoi(words[1]), replacedString);
            displayByPage(lineNode, pageNumber);
            j=0;
            while (words[j]!="\0"){
                words[j]="";
                j++;
            }
        }
        else if (words[0]=="display"){
            displayAll(lineNode);
        }
        else if (words[0]=="move"){
            moveLine(lineNode, stoi(words[1]), stoi(words[2]));
            displayByPage(lineNode, pageNumber);
        }
        else if (words[0]=="exit"){
            exit=1;
            break;
        }
    }
return 0;
}
