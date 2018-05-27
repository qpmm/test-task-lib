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
    void set_callback(fn_send_data _send_data);
    void start();
    void stop();

private:
    void read_data(); // чтение данных из файла в очередь
    void send_data(); // отправка данных из очереди в главное окно

    std::thread thread_read_data; // поток чтения данных
    std::thread thread_send_data; // поток отправки данных
    fn_send_data callback_send_data; // callback отправки данных
    std::atomic<bool> stopped; // флаг приостановки процесса

    void* sender; // объект главного окна
    std::ifstream input; // файл исходных данных
    thread_safe_queue<point> queue; // очередь для хранения данных
    char buf[32]; // буфер для обработки строк файла
};

#endif // TEST_TASK_LIB_H
