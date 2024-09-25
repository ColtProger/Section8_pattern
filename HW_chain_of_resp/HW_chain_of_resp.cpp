#include <iostream>
#include <fstream>
#include <exception>

enum class Type {
    WARRING,
    ERROR,
    FATALERROR,
    UNKNOWN
};

class LogMessage {
public:
   
    virtual void LogRequest(Type type, std::string const& message) = 0;
    
    virtual void SetNextHandler(std::shared_ptr<LogMessage> handler)  = 0;

    Type type() const {
        return type_;
    };

    const std::string& message() const {
        return message_;
    };
private:
    Type type_;
    std::string message_;
};

class WarringHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage> NextHandler = nullptr;
    Type type_;
    std::string message_;
public:
    
    void SetNextHandler(std::shared_ptr<LogMessage> handler) override {
        NextHandler = handler;
    }
    
    void LogRequest(Type type, std::string const& message) override {
        //std::cout << __FUNCTION__ << message << "\n";
        if (type == Type::WARRING) {
            std::cout << "WARRING message " << message << "\n";
        }
        else if (NextHandler!=nullptr){
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown message " << message << "\n";
        }
    }

};

class ErrorHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:

    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
     
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
      //  std::cout << __FUNCTION__ << message << "\n";
        if (type == Type::ERROR) {
            std::ofstream outputFile("error.log");

            if (outputFile.is_open()) {
                outputFile << message << std::endl;
                outputFile.close();
                std::cout << "Message \"" << message << "\" was written to error.log\n";
            }
            else {
                std::cerr << "Error opening file\n";
            }
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type " << message << "\n";
        }
    }

};

class FatalHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:

    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
       
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
     //   std::cout << __FUNCTION__ << message << "\n";
        if (type == Type::FATALERROR) {
            std::ofstream outputFile("error.log");

            if (outputFile.is_open()) {
                outputFile << message << std::endl;
                outputFile.close();
                std::cout << "Message \"" << message << "\" was written to error.log\n";
            }
            else {
                std::cerr << "Error opening file\n";
            }
            throw std::exception("Exclusion due to the FATAL-ERROR-type message\n");
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type " << message << "\n";
        }
    }

};

class UnknownHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:

    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
      //  std::cout << __FUNCTION__ << message << "\n";
        if (type == Type::UNKNOWN) {
            throw std::exception("Exclusion due to the UNKNOWN-type message\n");
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type " << message << "\n";
        }
    }

};

int main()
{
    auto msg_warr = std::make_shared<WarringHandler>();
    auto msg_err = std::make_shared< ErrorHandler>();
    auto msg_fat = std::make_shared< FatalHandler>();
    auto msg_unkn = std::make_shared< UnknownHandler>();

    msg_warr->SetNextHandler(msg_err);
    msg_err->SetNextHandler(msg_fat);
    msg_fat ->SetNextHandler(msg_unkn);


    try {
        msg_warr->LogRequest(Type::WARRING, "Warring Message");
        std::cout << std::endl;
        msg_warr->LogRequest(Type::ERROR, "Error Message");
        std::cout << std::endl;
        //msg_warr->LogRequest(Type::UNKNOWN, "Fatal Error Message");
        //std::cout << std::endl;
        msg_warr->LogRequest(Type::FATALERROR, "Fatal Error Message");
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

