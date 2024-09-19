#include <iostream>
#include<vector>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print() = 0;
};

class PrintConsole : public LogCommand {
private:
    std::string pay_load_;

public:
    explicit PrintConsole(std::string pay_load) : pay_load_(pay_load) {
    }
    void print() override {
        std::cout << "Print Console (" << this->pay_load_ << ")\n";
    }
};

class PrintFile : public LogCommand {
private:
    std::string pay_load_;

public:
    explicit PrintFile(std::string pay_load): pay_load_(pay_load) {
    }
    void print() override {
        std::cout << "Print to file (" << this->pay_load_ << ")\n";
    }
};


class PrintControl {
public:
    void print(LogCommand* cmd)
    {
        cmd->print();
    }

};


int main() {
    PrintConsole PC("Say Hi!");
    PrintFile PF("Say Bye!");

    PrintControl prnt;
    prnt.print(&PC);
    prnt.print(&PF);


    //delete sC;
    //delete remote;
   // delete invoker;
   // delete receiver;

    return 0;
}

