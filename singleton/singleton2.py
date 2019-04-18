'''
http://elbenshira.com/blog/singleton-pattern-in-python/
'''
import threading, time


'''
Ensure a class has only one instance per process.
1. 
'''
def singleton(cls):
    __instances = {}
    __lock = threading.Lock()

    def getinstance():
        if cls not in __instances:
            with __lock:
                if cls not in __instances:
                    __instances[cls] = cls()
        return __instances[cls]

    return getinstance

@singleton
class RedisConnPool(object):
    def __init__(self):
        pass

@singleton
class ElasticConnPool(object):
    def __init__(self):
        pass

def print_elastic():
    inst = ElasticConnPool() 
    time.sleep(1)
    print inst

def print_redis():
    inst = RedisConnPool() 
    time.sleep(1)
    print inst

if __name__ == "__main__":
    threads = []
    for i in range(5):
        t = threading.Thread(target = print_elastic)
        threads.append(t)
        t.start()
    for t in threads:
        t.join()

    threads = []
    for i in range(5):
        t = threading.Thread(target = print_redis)
        threads.append(t)
        t.start()
    for t in threads:
        t.join()
    threads = []
