#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
using namespace std;
class User;

class Notification {
private:
    User* user;
    std::string type;  // e.g., "new post", "comment", "like"
    bool isRead;
    bool isDismissed;

public:
    // Constructor
    Notification(User* user, const std::string& type)
        : user(user), type(type), isRead(false), isDismissed(false) {}

    // Function to mark the notification as read
    void markAsRead() {
        isRead = true;
        std::cout << "Notification marked as read for user: " << user->getName() << std::endl;
    }

    // Function to dismiss the notification
    void dismissNotification() {
        isDismissed = true;
        std::cout << "Notification dismissed for user: " << user->getName() << std::endl;
    }

    // Getter for notification type
    std::string getType() const {
        return type;
    }

    // Getter for read status
    bool getReadStatus() const {
        return isRead;
    }

    // Getter for dismissed status
    bool getDismissedStatus() const {
        return isDismissed;
    }
};

class User {
private:
    std::string name;
    std::vector<Notification*> notifications;

public:
    // Constructor
    User(const std::string& name) : name(name) {}

    // Function to receive a notification
    void receiveNotification(Notification* notification) {
        notifications.push_back(notification);
    }

    // Function to remove a notification
    void removeNotification(Notification* notification) {
        auto it = std::remove(notifications.begin(), notifications.end(), notification);
        notifications.erase(it, notifications.end());
        delete notification;
    }

    // Getter for user name
    std::string getName() const {
        return name;
    }

    // Function to display notifications
    void displayNotifications() {
        std::cout << "Notifications for " << name << ":" << std::endl;
        for (const auto& notification : notifications) {
            std::cout << "  - Type: " << notification->getType() << ", Read: " << (notification->getReadStatus() ? "Yes" : "No")
                      << ", Dismissed: " << (notification->getDismissedStatus() ? "Yes" : "No") << std::endl;
        }
    }

    // Destructor to free memory
    ~User() {
        for (const auto& notification : notifications) {
            delete notification;
        }
    }
};

// Comment class representing a comment on a post
class Comment {
private:
    User* author;
    std::string text;
    std::time_t timestamp;

public:
    Comment(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Getter for comment text
    std::string getText() const {
        return text;
    }

    // Getter for comment author
    User* getAuthor() const {
        return author;
    }

    // Getter for comment timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }
};

// Post class representing a post on the platform
class Post {
private:
    User* author;
    std::string text;
    std::unordered_set<User*> likes;
    std::vector<Comment> comments;
    std::time_t timestamp;

public:
    // Constructor
    Post(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Function to add a like to the post by a specific user
    void addLike(User* user) {
        likes.insert(user);
        std::cout << user->getName() << " liked the post." << std::endl;
    }

    // Function to add a comment to the post
    void addComment(const Comment& comment) {
        comments.push_back(comment);
        std::cout << comment.getAuthor()->getName() << " commented: " << comment.getText() << std::endl;
    }

    // Function to edit the post content (only allowed for the author)
    void editPost(const std::string& newText) {
        if (author != nullptr) {
            text = newText;
            std::cout << "Post edited successfully by " << author->getName() << "." << std::endl;
        } else {
            std::cerr << "Error: Post author not specified." << std::endl;
        }
    }

    // Function to delete the post from the platform (only allowed for the author)
    void deletePost() {
        if (author != nullptr) {
            std::cout << "Post deleted successfully by " << author->getName() << "." << std::endl;
            // Additional logic for deleting the post from the platform
        } else {
            std::cerr << "Error: Post author not specified." << std::endl;
        }
    }

    // Getter for post text
    std::string getText() const {
        return text;
    }

    // Getter for post author
    User* getAuthor() const {
        return author;
    }

    // Getter for post timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort comments by timestamp (using insertion sort for simplicity)
    void sortCommentsByTimestamp() {
        std::sort(comments.begin(), comments.end(), [](const Comment& a, const Comment& b) {
            return a.getTimestamp() < b.getTimestamp();
        });
    }
};





// Define a simple timestamp structure
struct Timestamp {
    int year, month, day, hour, minute, second;
};


// Content class
class Content {
private:
    static int nextContentID;
    int contentID;

public:
    // Constructor
    Content() : contentID(nextContentID++) {}

    // Getter for Content ID
    int getContentID() const {
        return contentID;
    }
};

// Share class
class Share {
private:
    static int nextShareID;
    int shareID;
    const User* userID;
    const Content* sharedContentID;
    Timestamp timestamp;

public:
    // Constructor
    Share(const User* user, const Content* content)
        : shareID(nextShareID++), userID(user), sharedContentID(content) {
        // Get the current timestamp
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        struct tm* parts = std::localtime(&now_c);

        // Populate timestamp structure
        timestamp.year = 1900 + parts->tm_year;
        timestamp.month = 1 + parts->tm_mon;
        timestamp.day = parts->tm_mday;
        timestamp.hour = parts->tm_hour;
        timestamp.minute = parts->tm_min;
        timestamp.second = parts->tm_sec;
    }

    // Function to display share details
    void displayShare() const {
        std::cout << "Share ID: " << shareID << std::endl;
        std::cout << "User ID: " << userID->getUserID() << std::endl;
        std::cout << "Shared Content ID: " << sharedContentID->getContentID() << std::endl;
        std::cout << "Timestamp: " << timestamp.year << "-"
                  << timestamp.month << "-"
                  << timestamp.day << " "
                  << timestamp.hour << ":"
                  << timestamp.minute << ":"
                  << timestamp.second << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
};


class Message {
private:
    User* sender;
    User* recipient;
    std::string text;
    bool isDeleted;

public:
    // Constructor
    Message(User* sender, User* recipient, const std::string& text)
        : sender(sender), recipient(recipient), text(text), isDeleted(false) {}

    // Function to send a private message to another user
    void sendMessage() {
        if (!isDeleted) {
            std::cout << sender->getName() << " sent a message to " << recipient->getName() << ": \"" << text << "\"."
                      << std::endl;
            recipient->receiveMessage(this);
        }
    }

    // Function to delete the message from the sender's and recipient's inbox
    void deleteMessage() {
        isDeleted = true;
        std::cout << sender->getName() << "'s message to " << recipient->getName() << " has been deleted." << std::endl;
        recipient->deleteReceivedMessage(this);
    }

    // Getter for the message text
    std::string getText() const {
        return text;
    }
};


class Like {
private:
    User* user;
    std::string targetType;  // "post" or "comment"
    unsigned int targetID;   // ID of the liked post or comment
    std::time_t timestamp;

public:
    // Constructor
    Like(User* user, const std::string& targetType, unsigned int targetID)
        : user(user), targetType(targetType), targetID(targetID), timestamp(std::time(nullptr)) {}

    // Getter for the user who liked
    User* getUser() const {
        return user;
    }

    // Getter for the type of target ("post" or "comment")
    std::string getTargetType() const {
        return targetType;
    }

    // Getter for the ID of the liked post or comment
    unsigned int getTargetID() const {
        return targetID;
    }

    // Getter for the timestamp of the like
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to display information about the like
    void displayLikeInfo() const {
        std::cout << user->getName() << " liked a " << targetType << " with ID " << targetID
                  << " at " << std::asctime(std::localtime(&timestamp));
    }
};

// Function to display all likes in a vector
void displayAllLikes(const std::vector<Like>& likes) {
    for (const Like& like : likes) {
        like.displayLikeInfo();
        std::cout << std::endl;
    }
}


class Group {
private:
    std::string name;
    std::string description;
    std::vector<User*> members;
    std::vector<std::string> posts;

public:
    // Constructor
    Group(const std::string& name, const std::string& description)
        : name(name), description(description) {}

    // Function to add a member to the group
    void addMember(User* user) {
        members.push_back(user);
        std::cout << user->getName() << " has joined the group: " << name << std::endl;
    }

    // Function to remove a member from the group
    void removeMember(User* user) {
        auto it = std::find(members.begin(), members.end(), user);
        if (it != members.end()) {
            members.erase(it);
            std::cout << user->getName() << " has left the group: " << name << std::endl;
        }
    }

    // Function to create a post within the group
    void createPost(const std::string& text) {
        posts.push_back(text);
        std::cout << "New post created in group " << name << ": " << text << std::endl;
    }

    // Function to read (display) posts in the group
    void readPosts() const {
        std::cout << "Posts in group " << name << ":" << std::endl;
        for (const auto& post : posts) {
            std::cout << "  - " << post << std::endl;
        }
    }
};



struct Node {
    User* friendUser;
    Node* next;

    Node(User* friendUser) : friendUser(friendUser), next(nullptr) {}
};

// LinkedList class to manage friends
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a new friend to the linked list
    void addFriend(User* friendUser) {
        Node* newNode = new Node(friendUser);
        newNode->next = head;
        head = newNode;
    }
};

// User class representing a user with a list of friends
class User {
private:
    std::string name;
    std::string email;
    std::string password;
    LinkedList friendsList;

public:
    User(std::string name, std::string email, std::string password)
        : name(name), email(email), password(password) {}

    std::string getEmail() const {
        return email;
    }

    // Authenticate the user based on the hashed password
    bool authenticate(std::string enteredPassword) const {
        // Replace with actual secure password authentication logic
        return enteredPassword == password;
    }

    // Add a friend to the user's friends list
    void addFriend(User* friendUser) {
        friendsList.addFriend(friendUser);
    }
};

// Graph class representing relationships between users
class Graph {
private:
    std::unordered_map<std::string, User*> users;

public:
    // Add a new user to the graph
    void addUser(User* user) {
        users[user->getEmail()] = user;
    }

    // Add a friendship between two users
    void addFriendship(User* user1, User* user2) {
        user1->addFriend(user2);
        user2->addFriend(user1);
    }

    // Authenticate a user based on email and password
    User* authenticateUser(std::string email, std::string password) const {
        auto it = users.find(email);
        if (it != users.end() && it->second->authenticate(password)) {
            return it->second;
        }
        return nullptr; // User not found or authentication failed
    }
};


class FriendshipGraph {
private:
    std::unordered_map<User*, std::unordered_set<User*>> adjacencyList;

public:
    // Function to add a user to the graph
    void addUser(User* user) {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            adjacencyList[user] = std::unordered_set<User*>();
        }
    }

    // Function to add a friendship (undirected edge)
    void addFriendship(User* user1, User* user2) {
        adjacencyList[user1].insert(user2);
        adjacencyList[user2].insert(user1);
    }

    // Function to display friends of a user
    void displayFriends(User* user) {
        std::cout << "Friends of " << user->getName() << ": ";
        for (const auto& friendNode : adjacencyList[user]) {
            std::cout << friendNode->getName() << " ";
        }
        std::cout << std::endl;
    }
};

class Friendship {
private:
    User* user1;
    User* user2;
    std::string status;  // "pending", "accepted", "rejected", "cancelled"

public:
    // Constructor
    Friendship(User* user1, User* user2) : user1(user1), user2(user2), status("pending") {}

    // Function to add a friend (send a friendship request)
    void addFriend(FriendshipGraph& graph) {
        if (status == "pending" || status == "rejected" || status == "cancelled") {
            status = "pending";
            std::cout << user1->getName() << " sent a friend request to " << user2->getName() << "." << std::endl;
            graph.addFriendship(user1, user2);
        }
    }

    // Function to accept a pending friendship request
    void acceptFriendship() {
        if (status == "pending") {
            status = "accepted";
            std::cout << user1->getName() << " and " << user2->getName() << " are now friends." << std::endl;
        }
    }

    // Function to reject a pending friendship request
    void rejectFriendship() {
        if (status == "pending") {
            status = "rejected";
            std::cout << user1->getName() << "'s friendship request to " << user2->getName() << " is rejected."
                      << std::endl;
        }
    }

    // Function to cancel an existing friendship
    void cancelFriendship() {
        if (status == "accepted") {
            status = "cancelled";
            std::cout << user1->getName() << " and " << user2->getName() << " are no longer friends." << std::endl;
        }
    }
};


// Forward declaration of User class (assuming it is defined elsewhere in the code)
class User;

// Reply class representing a reply to a comment
class Reply {
private:
    User* author;
    std::string text;
    std::time_t timestamp;

public:
    Reply(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Getter for reply text
    std::string getText() const {
        return text;
    }

    // Getter for reply author
    User* getAuthor() const {
        return author;
    }

    // Getter for reply timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }
};

// Comment class representing a comment on a post
class Comment {
private:
    User* author;
    std::string text;
    std::unordered_set<Reply*> replies; // Efficient storage for unique replies
    std::time_t timestamp;

public:
    // Constructor
    Comment(User* author, const std::string& text) : author(author), text(text), timestamp(std::time(nullptr)) {}

    // Destructor to free memory occupied by replies
    ~Comment() {
        for (auto reply : replies) {
            delete reply;
        }
    }

    // Function to add a reply to the comment
    void addReply(Reply* reply) {
        replies.insert(reply);
        std::cout << reply->getAuthor()->getName() << " replied: " << reply->getText() << std::endl;
    }

    // Function to edit the comment text (only allowed for the author)
    void editComment(const std::string& newText) {
        if (author != nullptr) {
            text = newText;
            std::cout << "Comment edited successfully by " << author->getName() << "." << std::endl;
        } else {
            std::cerr << "Error: Comment author not specified." << std::endl;
        }
    }

    // Function to delete the comment from the post (only allowed for the author)
    void deleteComment() {
        if (author != nullptr) {
            std::cout << "Comment deleted successfully by " << author->getName() << "." << std::endl;
            // Additional logic for deleting the comment from the post
        } else {
            std::cerr << "Error: Comment author not specified." << std::endl;
        }
    }

    // Getter for comment text
    std::string getText() const {
        return text;
    }

    // Getter for comment author
    User* getAuthor() const {
        return author;
    }

    // Getter for comment timestamp
    std::time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort replies by timestamp (using insertion sort for simplicity)
    void sortRepliesByTimestamp() {
        std::vector<Reply*> sortedReplies(replies.begin(), replies.end());
        std::sort(sortedReplies.begin(), sortedReplies.end(), [](const Reply* a, const Reply* b) {
            return a->getTimestamp() < b->getTimestamp();
        });

        // Output sorted replies
        for (auto sortedReply : sortedReplies) {
            std::cout << "Sorted Reply: " << sortedReply->getAuthor()->getName() << " - " << sortedReply->getText() << std::endl;
        }
    }
};

// Initialize static variables
int Share::nextShareID = 1;
int User::nextUserID = 1;
int Content::nextContentID = 1;

int main()
{
    
}