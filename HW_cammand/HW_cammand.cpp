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
        file_path = "output.txt"; //+= "output.txt";
        std::ofstream outputFile(file_path); 

        if (outputFile.is_open()) { 
            outputFile << message << std::endl; 
            outputFile.close();
            std::cout <<"Message \"" << message << "\" was written to output.txt\n";
        }
        else {
            std::cerr << "Error opening file\n";
        }
    }
};

void print(LogCommand& command, std::string message) {
    command.print(message);
};

int main() {
    
    PrintConsole PC;
    PrintFile PF("C:/Users/");
   
    print(PC, "Hello");
    print(PF, "Hello");


    return 0;
}

