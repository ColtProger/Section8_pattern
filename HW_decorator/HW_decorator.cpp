#include <string>
#include <iostream>
#include <algorithm>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:

    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }

};

class Reversed : public DecoratedText {
public:

    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::string newdata = data;
        
        std::cout << "<r>";
        std::reverse(newdata.begin(), newdata.end());
        text_->render(newdata);
        std::cout << "</r>";
    }

};

class Link : public DecoratedText {
public:

    explicit Link(Text* text) : DecoratedText(text) {}
    void render(std::string ref, const std::string& data){
        std::string newdata = data;

        std::cout << "<a href = "<<ref <<">";
        text_->render(data);
        std::cout << "</a>";
    }

};

int main() {
    auto text_block = new ItalicText(new BoldText(new Text()));
    text_block->render("Hello world");

    std::cout << "\n\n";
    auto text_block2 = new Paragraph(new Text());
    text_block2->render("Hello world");

    std::cout << "\n\n";
    auto text_block3 = new Reversed(new Text());
    text_block3->render("Hello world");

    std::cout << "\n\n";
    auto text_block4 = new Link(new Text());
    text_block4->render("netology.ru", "Hello world");

}