#include "messagepresenter.h"

#include <QLabel>
#include <thread>

using namespace std::chrono_literals;

MessagePresenter& MessagePresenter::getInstance()
{
    static MessagePresenter instance{};
    return instance;
}

void MessagePresenter::SetLabel(QLabel *messageLabel)
{
    this->messageLabel = messageLabel;

    QPalette palette = messageLabel->palette();
    palette.setColor(messageLabel->foregroundRole(), Qt::red);
    messageLabel->setPalette(palette);
}

void MessagePresenter::AddMessage(std::string message)
{
    this->messages.push(message);
}

MessagePresenter::~MessagePresenter()
{
    running = false;
    display->join();
}

void MessagePresenter::runDisplay()
{
    while(running){
        while(messages.empty() && running) {std::this_thread::sleep_for(1000ms);}
        if(!running) {
            return;
        }
        auto msg = messages.front();
        messages.pop();
        messageLabel->setText(QString::fromStdString(msg));
        std::this_thread::sleep_for(2500ms);
        if(!running) {
            return;
        }
        messageLabel->setText(QString::fromStdString(" "));
    }
}

MessagePresenter::MessagePresenter()
{
    running = true;
    display = new std::thread([this] {this->runDisplay();});
}
