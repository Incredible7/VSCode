import blog_spider
import threading
import time


def single_thread():
    print("single thread begins:")
    for url in blog_spider.urls:
        blog_spider.craw(url)
    print("single thread ends:")


def multi_thread():
    print("multi thread begins:")
    threads = []
    for url in blog_spider.urls:
        threads.append(threading.Thread(target=blog_spider.craw, args=(url, )))

    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    print("multi thread ends:")


if __name__ == "__main__":
    start = time.time()
    single_thread()
    end = time.time()
    print(end - start)

    start = time.time()
    multi_thread()
    end = time.time()
    print(end - start)
