#include <iostream>
#include<vector>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class PrintConsole : public LogCommand {
public:
    explicit PrintConsole() {    }

    void print(const std::string& message)  {
        std::cout << "Print Console (" << message << ")\n";
    }
};

class PrintFile : public LogCommand {
private:

    std::string path_;
public:
    explicit PrintFile(std::string path) : path_(path){    }

    void print(const std::string& message) {
        std::string file_path = path_; 
        file_path += "output.txt";
        std::cout << file_path << std::endl;
        std::ofstream outputFile(file_path); 

        if (outputFile.is_open()) { 
            outputFile << message << std::endl; 
            outputFile.close();
            std::cout << "Data was written to output.txt\n";
        }
        else {
            std::cerr << "Error opening file\n";
        }
    }
};



void print(LogCommand& cmd) {
    cmd;
}

int main() {
    /*impleCommand sC("Say Hi!");
    SimpleCommand2 sC2("Say Bye!");
    PrintControl prnt;
    prnt.print(&sC);
    prnt.print(&sC2);*/

    PrintConsole PC;
    PC.print("Hello");

    PrintFile PF("C:/Users/");
    PF.print("Hello");

    print(PC);
    print(PF);

    // invoker;
    //invoker.print(&PC);
    

    //delete invoker;
 //   delete receiver;



    //delete sC;
    //delete remote;
   // delete invoker;
   // delete receiver;

    return 0;
}

