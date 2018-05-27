#include "test_task_lib_global.h"
#include "test_task_lib.h"

reader* readerer = nullptr;

bool reader_init(void* sender, const char* filepath)
{
    readerer = new reader(sender);
    return readerer->init(filepath);
}

void reader_cleanup()
{
    if (readerer)
    {
        delete readerer;
        readerer = nullptr;
    }
}

void reader_set_callback(fn_send_data send_data)
{
    readerer->set_callback(send_data);
}

void reader_start()
{
    readerer->start();
}

void reader_stop()
{
    readerer->stop();
}
