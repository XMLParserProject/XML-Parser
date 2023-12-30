#include "user.h"

// Parameterized constructor
User::User(string Name, string ID, vector<string> follower, vector<pair<string, vector<string>>> post)
    : name(Name), id(ID), followers(follower), posts(post) {
    
}


// Default constructor
User::User() {}

// Accessor methods
string User::getName() {
    return name;
}

string User::getID() {
    return id;
}

vector<string> User::getFollowers() {
    return followers;
}

vector<pair<string, vector<string>>> User::getPosts() {
    return posts;
}

// Method to print user information
void User::printUser() const {
    cout << "Name is: " << name << endl;
    cout << "ID is: " << id << endl;
    cout << "Followers: ";
    for (const auto& follower : followers) {
        cout << follower << " ";
    }
    cout << endl;
    for (auto post : posts) {
        cout << "post: " << post.first << endl;
        cout << "topic: ";
        for (auto topic : post.second) {
            cout << topic << " ";
        }
        cout << endl;
    }
}

// Method to add a follower
void User::addFollower(string follower) {
    followers.push_back(follower);
}

void User::addPost(string postKey, vector<string> topics) {
    posts.push_back(make_pair(postKey, topics));
}

bool User::hasTopicInPosts(string topic) {
    for (auto post : posts) {
        for (auto postTopic : post.second) {
            if (postTopic == topic) {
                return true;
            }
        }
    }
    return false;
}