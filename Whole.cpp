#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <unordered_map>
#include <chrono>
using namespace std;

// Forward declarations
class facebookAdmin;
class User;
class Post;
class Comment;
class Like;
class Notification;
class Message;
class Group;
class Share;
class Content;
class Reply;

// Define a simple timestamp structure
struct Timestamp {
    int year, month, day, hour, minute, second;
};

// User class representing a user with a list of friends
class User {
private:
    string name;
    string email;
    string password;
    vector<Message*> messages;
    //posts
    //date of birth
    // notifications

public:
    vector<User*> friends;
    User(const string& name, const string& email, const string& password)
        : name(name), email(email), password(password) {}

    // Authenticate the user based on the hashed password
    bool authenticate(const string& enteredPassword) const {
        // Replace with actual secure password authentication logic
        return enteredPassword == password;
    }

    // Add a friend to the user's friends list
    void addFriend(User* friendUser) {
        friends.push_back(friendUser);
    }

    // Send a private message to another user
    void sendMessage(User* recipient, const string& text);

    // Receive a private message
    void receiveMessage(User* sender, const string& text);

    void deleteReceivedMessage(Message* message)
    {
        auto it = find(messages.begin(), messages.end(), message);
        if (it != messages.end()) {
            messages.erase(it);
        }
    }

    // Display the user's friends
    void displayFriends() const;

    // Display all messages
    void displayMessages() const;

    // Getter for user name
    string getName() const {
        return name;
    }


    // Function to create and add a new post
    // void addPost(const string& postText);

    // // Display all posts
    // void displayPosts() const;
};

// Post class representing a post on the platform
class Post {
private:
    User* author;
    string text;
    unordered_set<User*> likes;
    vector<Comment*> comments;
    time_t timestamp;

public:
    // Constructor
    Post(User* author, const string& text)
        : author(author), text(text), timestamp(time(nullptr)) {}

    // Function to add a like to the post by a specific user
    void addLike(User* user);

    // Function to add a comment to the post
    void addComment(Comment* comment);

    // Function to edit the post content (only allowed for the author)
    void editPost(const string& newText);

    // Function to delete the post from the platform (only allowed for the author)
    void deletePost();

    // Getter for post text
    string getText() const {
        return text;
    }

    // Getter for post author
    User* getAuthor() const {
        return author;
    }

    // Getter for post timestamp
    time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort comments by timestamp
    void sortCommentsByTimestamp();
};  

// Comment class representing a comment on a post
class Comment {
private:
    User* author;
    string text;
    unordered_set<Reply*> replies;
    time_t timestamp;

public:
    // Constructor
    Comment(User* author, const string& text)
        : author(author), text(text), timestamp(time(nullptr)) {}

    // Function to add a reply to the comment
    void addReply(Reply* reply);

    // Function to edit the comment text (only allowed for the author)
    void editComment(const string& newText);

    // Function to delete the comment from the post (only allowed for the author)
    void deleteComment();

    // Getter for comment text
    string getText() const {
        return text;
    }

    // Getter for comment author
    User* getAuthor() const {
        return author;
    }

    // Getter for comment timestamp
    time_t getTimestamp() const {
        return timestamp;
    }

    // Function to sort replies by timestamp
    void sortRepliesByTimestamp();
};

// Reply class representing a reply to a comment
class Reply {
private:
    User* author;
    string text;
    time_t timestamp;

public:
    // Constructor
    Reply(User* author, const string& text)
        : author(author), text(text), timestamp(time(nullptr)) {}

    // Getter for reply text
    string getText() const {
        return text;
    }

    // Getter for reply author
    User* getAuthor() const {
        return author;
    }

    // Getter for reply timestamp
    time_t getTimestamp() const {
        return timestamp;
    }
};

// Like class representing a like on a post or comment
class Like {
private:
    User* user;
    string targetType;  // "post" or "comment"
    unsigned int targetID;   // ID of the liked post or comment
    time_t timestamp;

public:
    // Constructor
    Like(User* user, const string& targetType, unsigned int targetID)
        : user(user), targetType(targetType), targetID(targetID), timestamp(time(nullptr)) {}

    // Function to display information about the like
    void displayLikeInfo() const;
};

// Notification class representing a notification for a user
class Notification {
private:
    User* user;
    string type;  // e.g., "new post", "comment", "like"
    bool isRead;
    bool isDismissed;

public:
    // Constructor
    Notification(User* user, const string& type)
        : user(user), type(type), isRead(false), isDismissed(false) {}

    // Function to mark the notification as read
    void markAsRead();

    // Function to dismiss the notification
    void dismissNotification();

    // Getter for notification type
    string getType() const {
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

// Message class representing a private message between users
class Message {
private:
    User* sender;
    User* recipient;
    string text;
    bool isDeleted;

public:
    // Constructor
    Message(User* sender, User* recipient, const string& text)
        : sender(sender), recipient(recipient), text(text), isDeleted(false) {}

    // Function to send the message
    void sendMessage();

    // Function to delete the message
    void deleteMessage();

    bool getIsDeleted()
    {
        return isDeleted;
    }

    // Getter for the message text
    string getText() const {
        return text;
    }
    User* getSender()
    {
        return sender;
    }


};

// Group class representing a group on the platform
class Group {
private:
    string name;
    string description;
    vector<User*> members;
    vector<string> posts;

public:
    // Constructor
    Group(const string& name, const string& description)
        : name(name), description(description) {}

    // Function to add a member to the group
    void addMember(User* user);

    // Function to remove a member from the group
    void removeMember(User* user);

    // Function to create a post within the group
    void createPost(const string& text);

    // Function to read (display) posts in the group
    void readPosts() const;
};

// Share class representing the sharing of content on the platform
class Share {
private:
    static int nextShareID;
    int shareID;
    const User* userID;
    const Content* sharedContentID;
    Timestamp timestamp;

public:
    // Constructor
    Share(const User* user, const Content* content);

    // Function to display share details
    void displayShare() const;
};

// Content class representing shared content on the platform
class Content {
private:
    static int nextContentID;
    int contentID;

public:
    // Constructor
    Content();
    
    // Getter for Content ID
    int getContentID() const {
        return contentID;
    }
};

// Initialize static variables
int Share::nextShareID = 1;
int Content::nextContentID = 1;

// Implementation of various functions

void Post::addLike(User* user) {
    likes.insert(user);
    cout << user->getName() << " liked the post." << endl;
}

void Post::addComment(Comment* comment) {
    comments.push_back(comment);
    cout << comment->getAuthor()->getName() << " commented: " << comment->getText() << endl;
}

void Post::editPost(const string& newText) {
    if (author != nullptr) {
        text = newText;
        cout << "Post edited successfully by " << author->getName() << "." << endl;
    } else {
        cerr << "Error: Post author not specified." << endl;
    }
}

void Post::deletePost() {
    if (author != nullptr) {
        cout << "Post deleted successfully by " << author->getName() << "." << endl;
        // Additional logic for deleting the post from the platform
    } else {
        cerr << "Error: Post author not specified." << endl;
    }
}

void Post::sortCommentsByTimestamp() {
    sort(comments.begin(), comments.end(), [](const Comment* a, const Comment* b) {
        return a->getTimestamp() < b->getTimestamp();
    });
}

void Comment::addReply(Reply* reply) {
    replies.insert(reply);
    cout << reply->getAuthor()->getName() << " replied: " << reply->getText() << endl;
}

void Comment::editComment(const string& newText) {
    if (author != nullptr) {
        text = newText;
        cout << "Comment edited successfully by " << author->getName() << "." << endl;
    } else {
        cerr << "Error: Comment author not specified." << endl;
    }
}

void Comment::deleteComment() {
    if (author != nullptr) {
        cout << "Comment deleted successfully by " << author->getName() << "." << endl;
        // Additional logic for deleting the comment from the post
    } else {
        cerr << "Error: Comment author not specified." << endl;
    }
}

void Comment::sortRepliesByTimestamp() {
    vector<Reply*> sortedReplies(replies.begin(), replies.end());
    sort(sortedReplies.begin(), sortedReplies.end(), [](const Reply* a, const Reply* b) {
        return a->getTimestamp() < b->getTimestamp();
    });

    // Output sorted replies
    for (auto sortedReply : sortedReplies) {
        cout << "Sorted Reply: " << sortedReply->getAuthor()->getName() << " - " << sortedReply->getText() << endl;
    }
}

void Like::displayLikeInfo() const {
    cout << user->getName() << " liked a " << targetType << " with ID " << targetID
              << " at " << asctime(localtime(&timestamp));
}

void Notification::markAsRead() {
    isRead = true;
    cout << "Notification marked as read for user: " << user->getName() << endl;
}

void Notification::dismissNotification() {
    isDismissed = true;
    cout << "Notification dismissed for user: " << user->getName() << endl;
}

void Message::sendMessage() {
    if (!isDeleted) {
        cout << sender->getName() << " sent a message to " << recipient->getName() << ": \"" << text << "\"."
                  << endl;
        recipient->receiveMessage(sender, text);
    }
}

void Message::deleteMessage() {
    isDeleted = true;
    cout << sender->getName() << "'s message to " << recipient->getName() << " has been deleted." << endl;
    recipient->deleteReceivedMessage(this);
}

void User::sendMessage(User* recipient, const string& text) {
    Message* message = new Message(this, recipient, text);
    messages.push_back(message);
    recipient->receiveMessage(this, text);
}

void User::receiveMessage(User* sender, const string& text) {
    Message* message = new Message(sender, this, text);
    messages.push_back(message);
}

void User::displayFriends() const {
    cout << "Friends of " << name << ": ";
    for (const auto& friendUser : friends) {
        cout << friendUser->getName() << " ";
    }
    cout << endl;
}

void User::displayMessages() const {
    cout << "Messages for " << name << ":" << endl;
    for (const auto& message : messages) {
        cout << "  - From: " << message->getSender()->getName()
                  << ", Text: \"" << message->getText() << "\", Deleted: "
                  << (message->getIsDeleted() ? "Yes" : "No") << endl;
    }
}

void Group::addMember(User* user) {
    members.push_back(user);
    cout << user->getName() << " has joined the group: " << name << endl;
}

void Group::removeMember(User* user) {
    auto it = find(members.begin(), members.end(), user);
    if (it != members.end()) {
        members.erase(it);
        cout << user->getName() << " has left the group: " << name << endl;
    }
}

void Group::createPost(const string& text) {
    posts.push_back(text);
    cout << "New post created in group " << name << ": " << text << endl;
}

void Group::readPosts() const {
    cout << "Posts in group " << name << ":" << endl;
    for (const auto& post : posts) {
        cout << "  - " << post << endl;
    }
}
int main() {
    // Create some sample users and groups
    User user1("User1", "user1@example.com", "password1");
    User user2("User2", "user2@example.com", "password2");
    Group group1("Group1", "Description of Group1");
    
    // Add user2 as a friend of user1
    user1.addFriend(&user2);
    
    int choice;
    
    do {
        // Display menu options
        cout << "\n----- Menu -----\n";
        cout << "1. Display Friends\n";
        cout << "2. Send Message\n";
        cout << "3. Display Messages\n";
        cout << "4. Create Post in Group\n";
        cout << "5. Read Group Posts\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display user's friends
                user1.displayFriends();
                break;
                
            case 2: {
                // Send a message
                string recipientName, messageText;
                cout << "Enter recipient's name: ";
                cin >> recipientName;
                User* recipient = nullptr;
                // Find the recipient user
                for (auto friendUser:user1.friends ) {         //: user1.getFriends()    hopefully here will be error
                    if (friendUser->getName() == recipientName) {
                        recipient = friendUser;
                        break;
                    }
                } 
                if (recipient) {
                    cout << "Enter message text: ";
                    cin.ignore();  // Clear buffer
                    getline(cin, messageText);
                    user1.sendMessage(recipient, messageText);
                } else {
                    cout << "Recipient not found in friends list.\n";
                }
                break;
            }

            case 3:
                // Display user's messages
                user1.displayMessages();
                break;

            case 4: {
                // Create a post in a group
                string postText;
                cout << "Enter post text: ";
                cin.ignore();  // Clear buffer
                getline(cin, postText);
                group1.createPost(postText);
                break;
            }

            case 5:
                // Read group posts
                group1.readPosts();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
