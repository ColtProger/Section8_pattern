#include <iostream>
#include<vector>
#include<memory>
#include<fstream>

class Observer {
public:
    virtual ~Observer() = default;


    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

class Observed {
public:
    void Warning(std::string msg) {
        for (auto &observer : observers_) {
            if (auto strong_ptr = observer.lock()) {
                strong_ptr->onWarning(msg);
            }
        }
    }
    void Error(std::string msg) {
        for (auto observer : observers_) {
            if (auto strong_ptr = observer.lock()) {
                strong_ptr->onError(msg);
            }
         }
    }

   void FatalError(std::string msg) {
        for (auto observer : observers_) {       
            if (auto strong_ptr = observer.lock()) {
                strong_ptr->onFatalError(msg);
            }
         }
    }

    void AddObserver(std::weak_ptr<Observer> observer) {
        observers_.push_back(observer);
        observer.lock();
    }

    //void RemoveObserver(Observer* observer) {
    //    auto it = remove(observers_.begin(), observers_.end(), observer);
    //    observers_.erase(it, observers_.end());
   // }

    void CreateMessage(std::string message = "Empty") {
        this->msg = message;
        Warning(msg);
    }
private:
    std::vector<std::weak_ptr<Observer>> observers_;
    std::string msg;
};

class WarningDisplay : public Observer 
{
public:
    WarningDisplay() {};
    void onWarning(const std::string& message) override {
        std::cout << "WarningDisplay: " << message << std::endl;
    }

};

class ErrorDisplay : public Observer
{
private:

    std::string path_;
public:
    ErrorDisplay(std::string path) : path_(path) {    }

    void onError(const std::string& message) {
        std::string file_path = path_;
        file_path = "output.txt";
        std::ofstream outputFile(file_path);

        if (outputFile.is_open()) {
            outputFile << message << std::endl;
            outputFile.close();
            std::cout << "Error message was written only to output.txt\n";
        }
        else {
            std::cerr << "Error opening file\n";
        }
    }

};

class FatalErrorDisplay : public Observer
{
private:

    std::string path_;
public:
    FatalErrorDisplay(std::string path) : path_(path) {    }

    void onFatalError(const std::string& message) {
        std::cout << "Fatal Error on Console: " << message << std::endl;
        std::string file_path = path_;
        file_path = "output.txt";
        std::ofstream outputFile(file_path);

        if (outputFile.is_open()) {
            outputFile << message << std::endl;
            outputFile.close();
            std::cout << "Fatal Error message was written to output.txt\n";
        }
        else {
            std::cerr << "Error opening file\n";
        }
    }

};
int main()
{
    std::weak_ptr<WarningDisplay> WD;
    auto shared_WD= std::make_shared<WarningDisplay>();
    WD = shared_WD;

    std::weak_ptr<ErrorDisplay> ED;
    auto shared_ED = std::make_shared<ErrorDisplay>("C:\\User");
    ED = shared_ED;

    std::weak_ptr<FatalErrorDisplay> FED;
    auto shared_FED = std::make_shared<FatalErrorDisplay>("C:\\User");
    FED = shared_FED;
  
    Observed Ob;
    Ob.AddObserver(WD);
    Ob.Warning("Warning Message");

    Ob.AddObserver(ED);
    Ob.Error("Error Message");

    Ob.AddObserver(FED);
    Ob.FatalError("FatalError Message");


  //  Ob.RemoveObserver(&WD);
   // Ob.RemoveObserver(&ED);
    //Ob.RemoveObserver(&FED);
}
