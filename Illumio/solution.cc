#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

void constructMap(string filename, unordered_map<string, pair<string, int>>& map)
{
    ifstream inFile;
    inFile.open(filename, ios::in);
    string line, source, destination;
    int idx = 1;
    while(getline(inFile, line))
    {
        for(int i = 0; i < line.size(); ++i) 
        {
            if(line[i] == ',') {
                source = line.substr(0, i);
                destination = line.substr(i+1, line.size()-i-1);
                break;
            }
        }
        map[source] = pair<string, int>(destination, idx);
        ++idx;
    }
}

void constructFlow(string filename, vector<string>& flow) 
{
    ifstream inFile;
    inFile.open(filename, ios::in);
    string line;
    while(getline(inFile, line))
        flow.emplace_back(line);
}

void nat(vector<string>& flow, unordered_map<string, pair<string, int>>& map)
{
    string ip, port;
    for(auto it = flow.begin(); it != flow.end(); ++it) 
    {
        pair<string, int> p1("", map.size()), p2("", map.size()), p3("", map.size());
        if(map.count(*it))
            p1 = map[*it];
        for(int i = 0; i < (*it).size(); ++i)
        {
            if((*it)[i] == ':')
            {
                ip = (*it).substr(0, i);
                port = (*it).substr(i+1, (*it).size()-i-1);
                break;
            }
        }
        string s1= ip+":*", s2 = "*:"+port;
        if(map.count(s1))
            p2 = map[s1];
        else if(map.count(s2))
            p3 = map[s2];
        if(p1.first.empty() && p2.first.empty() && p3.first.empty())
        {
            cout << "No nat match for" << *it << endl;
            continue;
        }
        if(p1.second <= p2.second && p1.second <= p3.second)
            cout << *it << " -> " << p1.first << endl;
        else if(p2.second <= p1.second && p2.second <= p3.second)
            cout << *it << " -> " << p2.first << endl;
        else
            cout << *it << " -> " << p3.first << endl;
    }
}

int main()
{
    unordered_map<string, pair<string, int>> map;
    constructMap("input.txt", map);    
    vector<string> flow;
    constructFlow("flow.txt", flow);
//    for(auto it = map.begin(); it != map.end(); ++it)
//        cout << it->first << " " << (it->second).first << " " << (it->second).second << endl;
//    for(auto it = flow.begin(); it != flow.end(); ++it)
 //       cout << *it << endl; 
    nat(flow, map);
    return 0;
}
