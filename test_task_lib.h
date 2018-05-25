#ifndef TEST_TASK_LIB_H
#define TEST_TASK_LIB_H

#include "test_task_lib_global.h"
#include "thread_safe_queue.h"
#include <fstream>
#include <thread>
#include <atomic>

#define MAX_QUEUE_SIZE 100

class reader
{
public:
    reader(void* _sender);
    ~reader();

    bool init(const char* _filepath);
    void set_callbacks(fn_send_data _send_data, fn_finished _finished);
    void start();
    void stop();

private:
    void read_data();
    void send_data();

    std::thread thread_read_data;
    std::thread thread_send_data;
    fn_send_data callback_send_data;

    std::atomic<bool> stopped;
    fn_finished callback_finished;

    void* sender;
    std::ifstream input;
    thread_safe_queue<point> queue;
    char buf[32];
};

#endif // TEST_TASK_LIB_H
