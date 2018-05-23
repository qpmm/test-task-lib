#include "test_task_lib.h"
#include <unistd.h>
#include <cstdlib>
#include <locale>

reader::reader(void* _owner)
{
    owner = _owner;
    callback_send_data = nullptr;
    callback_finished = nullptr;
    setlocale(LC_NUMERIC, "Russian");
}

bool reader::init(const char* _filepath)
{
    input.open(_filepath);
    return input.is_open();
}

void reader::set_callbacks(func_send_data _send_data, func_finished _finished)
{
    callback_send_data = _send_data;
    callback_finished = _finished;
}

void reader::start()
{
    set_finished(false);
    thread_read_data = std::thread(&reader::read_data, this);
    thread_send_data = std::thread(&reader::send_data, this);
}

void reader::stop()
{
    set_finished(true);
    thread_read_data.join();
    thread_send_data.join();
}

reader::~reader()
{
    if (input.is_open())
    {
        input.close();
    }
}

void reader::read_data()
{
    char* s;
    point p;

    while (input.good() && !finished)
    {
        if (queue.size() > MAX_QUEUE_SIZE)
        {
            continue;
        }

        input.getline(buf, 32);

        if (!buf[0])
        {
            continue;
        }

        strtol(buf, &s, 10);
        p.x = strtof(s, &s);
        p.y = strtof(s, nullptr);
        queue.push(p);
    }

    set_finished(true);
}

void reader::send_data()
{
    while (!finished || !queue.empty())
    {
        usleep(50 * 1000);

        if (queue.empty())
        {
            continue;
        }

        callback_send_data(owner, queue.pop());
    }
}

void reader::set_finished(bool state)
{
    finished = state;

    if (finished)
        callback_finished();
}
