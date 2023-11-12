#include <iostream>
#include <string>
#include <vector>

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

int main() {
    // Create users
    User user1("NotificationUser");

    // Create and send a notification
    Notification* notification = new Notification(&user1, "new post");
    user1.receiveNotification(notification);

    // Display user's notifications before marking as read or dismissing
    user1.displayNotifications();

    // Mark the notification as read
    notification->markAsRead();

    // Dismiss the notification
    notification->dismissNotification();

    // Display user's notifications after marking as read and dismissing
    user1.displayNotifications();

    // Remove notifications and free memory
    user1.removeNotification(notification);

    return 0;
}
