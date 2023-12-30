#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include"User.h"
#include"Helpers.h"
class Graph {
private:
    unordered_map<string, User> user_vector;
    unordered_map<string, vector<string>> follower_edge;


    bool not_old_follower(vector<string> old_follower, string id);

public:
    void addUser(User u1);
    void printfollowers(string id);
    unordered_map<string, vector<string>> get_follower_edge();
    unordered_map<string, User> get_user_vector();
    // Analytical methods
    User most_influencer();
    User most_active();
    vector<User> mutual_followers(string id1, string id2);
    vector<User> follow_suggestion(string id);
    vector <string> post_search(string topic);

    //print
    void print();
    string print_mutual_followers (string id1, string id2);
    string print_follow_suggestion(string id);
    string print_post_search(string topic);
};

