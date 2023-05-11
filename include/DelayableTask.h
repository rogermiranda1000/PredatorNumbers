#pragma once

#include <functional>
#include <vector>
#include "StatefulClass.h"

class DelayableTask : public StatefulClass {
private:
    static DelayableTask *_instance;
    std::vector<std::function<void(void)>> _queue;

public:
    static DelayableTask *getInstance();
    void queue(std::function<void(void)> e);
    static void linkInstance(std::function<void(StatefulClass*)> link);
    void update();
};