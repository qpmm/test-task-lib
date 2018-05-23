#include "test_task_lib_global.h"
#include "test_task_lib.h"

reader* readerer = nullptr;

bool global_init(void* owner, const char* filepath)
{
    readerer = new reader(owner);
    return readerer->init(filepath);
}

void global_cleanup()
{
    if (readerer)
    {
        delete readerer;
        readerer = nullptr;
    }
}

void global_set_callbacks(func_send_data send_data, func_finished finished)
{
    readerer->set_callbacks(send_data, finished);
}

void global_start()
{
    readerer->start();
}

void global_stop()
{
    readerer->stop();
}
