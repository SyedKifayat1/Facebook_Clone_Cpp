#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class User;

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

class User {
private:
    std::string name;
    std::vector<Message*> inbox;

public:
    // Constructor
    User(const std::string& name) : name(name) {}

    // Function to receive a message
    void receiveMessage(Message* message) {
        inbox.push_back(message);
    }

    // Function to delete a received message
    void deleteReceivedMessage(Message* message) {
        auto it = std::find(inbox.begin(), inbox.end(), message);
        if (it != inbox.end()) {
            inbox.erase(it);
        }
    }

    // Getter for user name
    std::string getName() const {
        return name;
    }

    // Function to display inbox messages
    void displayInbox() {
        std::cout << "Inbox for " << name << ":" << std::endl;
        for (const auto& message : inbox) {
            std::cout << "  - " << message->getText() << std::endl;
        }
    }
};

int main() {
    // Create users
    User user1("SenderUser");
    User user2("RecipientUser");

    // Create and send a message
    Message message(&user1, &user2, "Hello, how are you?");
    message.sendMessage();

    // Display recipient's inbox before deleting
    user2.displayInbox();

    // Delete the message
    message.deleteMessage();

    // Display recipient's inbox after deleting
    user2.displayInbox();

    return 0;
}
