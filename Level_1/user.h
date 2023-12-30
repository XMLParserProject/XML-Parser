#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class User {
private:
    string name;
    string id;
    vector<string> followers;
    vector<pair<string, vector<string>>> posts; // string for post and vector of string for topic

public:
    User(string Name, string ID, vector<string> follower, vector<pair<string, vector<string>>> posts);
    User();

    string getName() ;
    string getID() ;
    vector<string> getFollowers() ;
    vector<pair<string, vector<string>>> getPosts() ;

    void printUser() const;
    void addFollower( string follower);
    void addPost(string postKey, vector<string> topics);
    bool hasTopicInPosts(string topic);
};
