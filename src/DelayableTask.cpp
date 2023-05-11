#include "DelayableTask.h"

DelayableTask *DelayableTask::_instance = nullptr;

DelayableTask *DelayableTask::getInstance() {
    if (DelayableTask::_instance == nullptr) {
        DelayableTask::_instance = new DelayableTask();
    }
    return DelayableTask::_instance;
}

void DelayableTask::queue(std::function<void(void)> e) {
    this->_queue.push_back(e);
}

void DelayableTask::linkInstance(std::function<void(StatefulClass*)> link) {
    link(DelayableTask::getInstance());
}

void DelayableTask::update() {
    std::vector<std::function<void(void)>> queue_copy = this->_queue;
    this->_queue.clear();

    // run all the delayed runnables
    for (const std::function<void(void)> &delayed_function : queue_copy) delayed_function();
}