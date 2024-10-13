#include <iostream>
#include <thread>

#include "absl_thread_safe_queue.h"

void producer(std::stop_token stoken, thread_safe_queue_t<int> &queue)
{
    int i{0};
    while (true)
    {
        if (stoken.stop_requested())
        {
            return;
        }

        queue.push(i++);

        if (i == 1)
        {
            break;
        }
    }
}

void consumer(std::stop_token stoken, thread_safe_queue_t<int> &queue)
{
    for (;;)
    {
        if (stoken.stop_requested())
        {
            return;
        }

        auto item = queue.pop();
        std::cout << "Consumed: " << item.value() << std::endl;
    }
}

auto main() -> int
{
    thread_safe_queue_t<int> queue;

    auto producerThread = std::jthread(producer, std::ref(queue));
    auto consumerThread = std::jthread(consumer, std::ref(queue));

    /*queue.print();*/

    producerThread.request_stop();
    consumerThread.request_stop();

    producerThread.join();
    consumerThread.join();

    return 0;
}
