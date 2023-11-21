/*
    The Builder pattern is concerned with the creation of complicated objects,
    that is, objects that cannot be built up in a single-line constructor call.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct HtmlElement{
    string name, text;
    vector<HtmlElement> elements;

    HtmlElement(){}
    HtmlElement(const string& name, const string& text): name(name), text(text)
    {

    }

    string str(int indent=0) const
    {
        string text = "";
        string indent_text = "";
        for (int i=0; i<indent; i++)
            indent_text += " ";

        text += indent_text+"<"+this->name+">"+((indent == 0)? "\n":"");
        text += indent_text+this->text;
        for (const HtmlElement& temp_element: this->elements)
            text += temp_element.str(indent+1);
        text += indent_text+"</"+this->name+">\n";
        return text;
    }
};

struct HtmlBuilder{
    HtmlElement root;
    
    HtmlBuilder(string root_name){
        root.name = root_name;
    }

    void add_child(string child_name, string child_text)
    {
        root.elements.emplace_back(child_name, child_text);
    }

    string str(){
        return root.str();
    }

};


int main()
{
    HtmlBuilder builder{"ul"};
    builder.add_child("li","Hello");
    builder.add_child("li","World");
    builder.add_child("li","!");
    cout << builder.str() << endl;
}