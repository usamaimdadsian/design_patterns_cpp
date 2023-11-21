/*
    It is same as simple builder just changed the add_child function in HtmlBuilder
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct HtmlBuilder
{
    HtmlElement root;

    // HtmlBuilder(string root_name)
    // {
    //     root.name = root_name;
    // }

    HtmlBuilder &add_child(string child_name, string child_text)
    {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    string str()
    {
        return root.str();
    }
};

struct HtmlElement
{
    string name, text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;


    static unique_ptr<HtmlBuilder> create(const string& root_name)
    {
        return make_unique<HtmlBuilder>(root_name);
    }

    

    string str(int indent = 0) const
    {
        string text = "";struct HtmlBuilder
{
    HtmlElement root;

    // HtmlBuilder(string root_name)
    // {
    //     root.name = root_name;
    // }

    HtmlBuilder &add_child(string child_name, string child_text)
    {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    string str()
    {
        return root.str();
    }
};
        string indent_text = "";
        string temp_indent_text = " ";
        for (int j = 0; j < this->indent_size-1; j++)
            temp_indent_text += temp_indent_text;
        for (int i = 0; i < indent; i++)
            indent_text += temp_indent_text;

        text += indent_text + "<" + this->name + ">" + ((this->elements.size() > 0) ? "\n" + indent_text : "");
        text += this->text;
        for (const HtmlElement &temp_element : this->elements)
            text += temp_element.str(indent + 1);
        text += ((this->elements.size() > 0) ? indent_text : "") + "</" + this->name + ">\n";
        return text;
    }

protected:
    HtmlElement() {}
    HtmlElement(const string &name, const string &text) : name(name), text(text)
    {
    }
};



int main()
{
    auto builder = HtmlElement::create("ul");
    builder.add_child("li", "Hello").add_child("li", "World").add_child("li", "!");
    cout << builder.str() << endl;
}