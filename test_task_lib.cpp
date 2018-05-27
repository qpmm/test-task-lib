#include "test_task_lib.h"
#include <unistd.h>
#include <cstdlib>
#include <locale>
#include <QDebug>

reader::reader(void* _sender)
{
    sender = _sender;
    callback_send_data = nullptr;
    setlocale(LC_NUMERIC, "Russian");
}

bool reader::init(const char* _filepath)
{
    input.open(_filepath);
    return input.is_open();
}

void reader::set_callback(fn_send_data _send_data)
{
    callback_send_data = _send_data;
}

void reader::start()
{
    stopped = false;
    thread_read_data = std::thread(&reader::read_data, this);
    thread_send_data = std::thread(&reader::send_data, this);
}

void reader::stop()
{
    stopped = true;

    if (thread_read_data.joinable())
        thread_read_data.join();

    if (thread_send_data.joinable())
        thread_send_data.join();
}

reader::~reader()
{
    if (input.is_open())
        input.close();
}

void reader::read_data()
{
    char* s;
    point p;

    while (!stopped && !input.eof())
    {
        if (queue.size() > MAX_QUEUE_SIZE)
            continue;

        input.getline(buf, 32);

        if (!buf[0])
            continue;

        strtol(buf, &s, 10);
        p.x = strtof(s, &s);
        p.y = strtof(s, nullptr);
        queue.push(p);
    }

    stopped = true;
}

void reader::send_data()
{
    while (!stopped)
    {
        usleep(50 * 1000);

        if (!queue.empty())
            callback_send_data(sender, queue.pop());
    }
}
