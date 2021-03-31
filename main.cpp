// C++ program to encode and decode a string using
// Huffman Coding.
#include <bits/stdc++.h>
#include <fstream>
#define MAX_TREE_HT 256
using namespace std;
  

struct Node
{
    char data;             // Char 
    int freq;             // No of Time Char appears in string
    Node *left, *right; // Node Child Items
  
    Node(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
  
class HuffmanAlgorithem
{

    // utility function for the priority queue
    struct compare
    {
        bool operator()(Node *l, Node *r)
        {
            return (l->freq > r->freq);
        }
    };


    vector<string> Data;
    map<char, int> freq;
    map<char, string> codes;
    string EncodedString;
    priority_queue<Node *, vector<Node *>, compare> minHeap;
    Node *root;
    string DecodedString;

    void EncodedStr()
    {
        string str = GetStrData();
        for (auto i : str)
            EncodedString += codes[i];
    }
    void ReadFile(string fileName)
    {
        string myText;
        ifstream MyReadFile(fileName);
        while (getline(MyReadFile, myText))
        {
            Data.push_back(myText);
        }

        MyReadFile.close();
    }

    string GetStrData()
    {
        string str;
        for(auto item:Data)
        {
            str+=item;
            if(item != Data.back())
                str+='\n';
        }
        return str;
    }


    void CalculateFrequecies()
    {
        string str = GetStrData();
        for (int i = 0; i < str.size(); i++)
            freq[str[i]]++;
    }

    void GenerateTree()
    {
        struct Node *left, *right, *top;
        for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
            minHeap.push(new Node(v->first, v->second));
        while (minHeap.size() != 1)
        {
            left = minHeap.top();
            minHeap.pop();
            right = minHeap.top();
            minHeap.pop();
            top = new Node('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }
        root = minHeap.top();
        populateLeafs(root, "");
    }

    void populateLeafs(struct Node *Root, string str)
    {
        if (Root == NULL)
            return;
        if (Root->data != '$')
            codes[Root->data] = str;
        populateLeafs(Root->left, str + "0");
        populateLeafs(Root->right, str + "1");
    }

    void DisplayCodes(struct Node *root, string str)
    {
        if (!root)
            return;
        if (root->data != '$')
            cout << root->data << ": " << str << "\n";
        DisplayCodes(root->left, str + "0");
        DisplayCodes(root->right, str + "1");
    }

    void decode_file(struct Node *root, string s)
    {
        DecodedString = "";
        struct Node *curr = root;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '0')
                curr = curr->left;
            else
                curr = curr->right;

            if (curr->left == NULL and curr->right == NULL)
            {
                DecodedString += curr->data;
                curr = root;
            }
        }
    }

    public:
        HuffmanAlgorithem()
        {
            root = nullptr;
        }

        void EncodeFile(string fileName)
        {
            ReadFile(fileName);
            CalculateFrequecies();
            GenerateTree();
            EncodedStr();
        }


        void DisplaySymbols()
        {

            cout << "\033[1;31m";
            cout << endl;
            cout << " Symbols: " << endl;
            cout << "\033[0m";

            cout << "\033[0;32m";
            cout << "-----------------------------------------------------------------" << std::endl;
            for (auto v = codes.begin(); v != codes.end(); v++)
            {
                if (v->first != '\n')
                    cout << "| "
                         << "\t\t" << v->first << "\t\t"
                         << " | "
                         << "\t\t" << v->second << "\t\t"
                         << " | " << endl;
                 }
                 cout << "-----------------------------------------------------------------"  << std::endl;

            cout << endl;
            cout << "\033[0m";
        }

        void DisplayAverageWordCode()
        {
            cout << endl;

            int len=0;
            for (auto v = codes.begin(); v != codes.end(); v++)
            {
                len+= freq[v->first] * v->second.length();
            }

            cout << "\033[1;33m";

            cout << "-----------------------------------------------------------------" << std::endl;
            cout << " Total Length: "<<"\t\t" << len << endl;
            cout << "-----------------------------------------------------------------" << std::endl;

            int count = 0;

            for (auto v : freq)
            {
                count += v.second;
            }

            cout << " Average Count: "
                 << "\t\t" << (len*1.0)/count << endl;
            cout << "-----------------------------------------------------------------" << std::endl;


            cout << endl;

            cout << "\033[0m";
        }

        void DisplayEndodedFile()
        {

            cout << "\033[1;37m";
            cout<<endl;
            cout << "-----------------------------------------------------------------" << std::endl;
            cout << " Encoded File: "
                 << "\n" << EncodedString << endl;
            cout << "-----------------------------------------------------------------" << std::endl;
            cout << endl;

            cout << "\033[0m";
        }

        void DisplayDecodedFile()
        {
            cout << "\033[1;37m";
            cout << endl;
            cout << "-----------------------------------------------------------------" << std::endl;
            cout << " Decoded File: "
                 << "\n" << DecodedString << endl;
            cout << "-----------------------------------------------------------------" << std::endl;
            cout << endl;

            cout << "\033[0m";
        }

        void SaveEncodedFile(string fileName)
        {
            ofstream out;
            out.open(fileName,ios::trunc);
            out << EncodedString;
            out.close();
        }

        void SaveDecodedFile(string fileName)
        {
            ofstream out;
            out.open(fileName, ios::trunc);
            out << DecodedString;
            out.close();
        }

        void DecodeFile(string fileName)
        {
            string myText;
            ifstream MyReadFile(fileName);
            getline(MyReadFile, myText);
            MyReadFile.close();
            decode_file(root,myText);
        }

        void CompareFiles(string originalFile,string DecodeFile)
        {
            string str1;
            string str2;
            ifstream OrigReadFile(originalFile);
            ifstream DecodedReadFile(DecodeFile);

            cout << "\033[0;33m";
            cout<<endl;
            cout << "-----------------------------------------------------------------" << std::endl;
            cout<<"Comparison Results"<<endl;
            bool identcal = true;
            while(true)
            {
                if (getline(OrigReadFile, str1) && getline(DecodedReadFile, str2))
                {
                    if(str1 != str2)
                        {
                            cout << "\033[1;31m";
                            cout << "Original File : " << str1 << "\t|\t"
                                 << "DecodedFile : " << str2 << endl;
                            identcal = false;
                            
                        }
                }
                else
                {
                    break;
                }
            }

            if(identcal)
            {
                cout << "\033[1;32m";
                cout<<"Files are identical"<<std::endl;
                
            }
            cout << "\033[0;33m";
            cout << "-----------------------------------------------------------------" << std::endl;
            cout << endl;
            cout << "\033[0m";
        }
};
  
int main()
{

    

    HuffmanAlgorithem A;
    A.EncodeFile("data.txt");
    A.DisplaySymbols();
    A.DisplayAverageWordCode();
    A.DisplayEndodedFile();
    A.SaveEncodedFile("EncodedFile.txt");
    A.DecodeFile("EncodedFile.txt");
    A.DisplayDecodedFile();
    A.SaveDecodedFile("DecodedFile.txt");

    cout << "\033[1;32m";
    cout<<"Starting File Comparison"<<std::endl;
    cout << "\033[0m";

    A.CompareFiles("data.txt","DecodedFile.txt");

    cout << "\033[1;31m";
    cout<<"Introducing Bit Error In File"<<endl;
    cout << "\033[0m";

    string myText;
    ifstream MyReadFile("EncodedFile.txt");
    getline(MyReadFile, myText);
    MyReadFile.close();

    for(int i=0;i<5;i++)
    {
        int random = rand() % myText.length();
        if(myText[random]=='0')
            myText[random] = '1';
        else
            myText[random] = '0';
    }

    ofstream out;
    out.open("CorruptedEncodedFile.txt", ios::trunc);
    out << myText;
    out.close();

    A.DecodeFile("CorruptedEncodedFile.txt");
    A.SaveDecodedFile("CorruptedDecodedFile.txt");
    A.CompareFiles("data.txt", "CorruptedDecodedFile.txt");

    return 0;
}
