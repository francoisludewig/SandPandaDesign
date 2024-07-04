#ifndef MESSAGEPRESENTER_H
#define MESSAGEPRESENTER_H

#include <string>
#include <queue>
#include <thread>

class QLabel;

class MessagePresenter
{
public:
    static MessagePresenter& getInstance();
    void SetLabel(QLabel *messageLabel);
    void AddMessage(std::string message);

    ~MessagePresenter();

private:
    MessagePresenter();
    void runDisplay();

    QLabel *messageLabel;
    std::queue<std::string> messages{};
    bool running = true;
    std::thread* display;

};

#endif // MESSAGEPRESENTER_H
