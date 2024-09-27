#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAs() const = 0;
    //virtual std::string printAsText() const = 0;
    //virtual std::string printAsJSON() const = 0;
};


class DataHTML : public Printable
{
public:
    DataHTML(std::string data) : data_(std::move(data)) {}

    std::string printAs() const override
    {
        return "<html>" + data_ + "<html/>";
    }
private:
    std::string data_;
};

//class PrintableAsText
//{
//public:
//    virtual ~PrintableAsText() = default;
//    virtual std::string printAsText() const = 0;
//};

class DataText : public Printable
{
public:
    DataText(std::string data) : data_(std::move(data)) {}

    std::string printAs() const override
    {
        return data_;
    }
private:
    std::string data_;
};

//class PrintableAsJSON
//{
//public:
//    virtual ~PrintableAsJSON() = default;
//
//    virtual std::string printAsJSON() const = 0;
//};

class DataJson : public Printable
{
public:
    DataJson(std::string data) : data_(std::move(data)) {}

    std::string printAs() const override
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
private:
    std::string data_;
};

void saveTo(std::ofstream& file, const Printable& printable)
{
        file << printable.printAs();
        file << "\n";
}

//void saveToAsHTML(std::ofstream& file, const Printable& printable) {
//    saveTo(file, printable, Data::Format::kHTML);
//}
//
//void saveToAsJSON(std::ofstream& file, const Printable& printable) {
//    saveTo(file, printable, Data::Format::kJSON);
//}
//
//void saveToAsText(std::ofstream& file, const Printable& printable) {
//    saveTo(file, printable, Data::Format::kText);
//}

int main() {

    std::ofstream outputFile("output.txt");

    DataText DT("Hello world");
    DataHTML DH("Hello world");
    DataJson DJ("Hello world");
    saveTo(outputFile, DT);
    saveTo(outputFile, DH);
    saveTo(outputFile, DJ);

    outputFile.close();
    return 0;
}