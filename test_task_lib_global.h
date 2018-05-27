#ifndef TEST_TASK_LIB_GLOBAL_H
#define TEST_TASK_LIB_GLOBAL_H

class reader;

struct point
{
    float x;
    float y;
};

typedef void(*fn_send_data)(void*, point);
typedef void(*fn_finished)(void*);
typedef void(*fn_set_callbacks)(fn_send_data, fn_finished);

typedef bool(*fn_init)(void*, const char*);
typedef void(*fn_control)();

extern "C"
{
    bool reader_init(void* sender, const char* filepath);
    void reader_cleanup();
    void reader_set_callbacks(fn_send_data send_data, fn_finished finished);
    void reader_start();
    void reader_stop();
}

#endif // TEST_TASK_LIB_GLOBAL_H
