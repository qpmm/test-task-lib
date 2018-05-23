#ifndef TEST_TASK_LIB_GLOBAL_H
#define TEST_TASK_LIB_GLOBAL_H

class reader;

struct point
{
    float x;
    float y;
};

typedef void(*func_send_data)(void*, point);
typedef void(*func_finished)();

typedef bool(*func_init)(const char*, void*);
typedef void(*func_control)();

extern "C"
{
    bool global_init(void* owner, const char* filepath);
    void global_cleanup();
    void global_set_callbacks(func_send_data send_data, func_finished finished);
    void global_start();
    void global_stop();
}

#endif // TEST_TASK_LIB_GLOBAL_H
