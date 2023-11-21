/*
    EVERY CLASS SHOULD HAVE ONLY ONE RESPONSIBILITY
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Journal
{
    string title;
    vector<string> entries;

    explicit Journal(const string &title) : title{title} {}

    void add(const string &entry)
    {
        static int count = 1;
        entries.push_back(to_string(count++) + ": " + entry);
    }
};

struct PersistenceManager
{
    static void save(const Journal &j, const string &filename)
    {
        ofstream ofs(filename);
        for (auto &s : j.entries)
            ofs << s << endl;
    }
};

int main()
{
    Journal myJournal("My Journal");
    myJournal.add("Entry 1");
    myJournal.add("Entry 2");

    for (const string &entry : myJournal.entries)
    {
        cout << entry << endl;
    }

    PersistenceManager::save(myJournal, "journal.txt");

    return 0;
}