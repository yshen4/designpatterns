import threading

'''
A singleton based on double checked lock:
- https://en.wikipedia.org/wiki/Double-checked_locking 
'''
class Singleton(object):
    __lock = threading.Lock()
    __instance = None

    @classmethod
    def instance(cls):
        if not cls.__instance:
            with cls.__lock:
                if not cls.__instance:
                    cls.__instance = cls()
        return cls.__instance

    def __init__(self):
        """ Virtually private constructor. """
        if not Singleton.__instance:
            raise Exception("This class is a singleton!")
        else:
            Singleton.__instance = self

class ElasticConnPool(Singleton):
     def __init__(self):
         self.name = "Elastic"

class RedisConnPool(Singleton):
     def __init__(self):
         self.name = "Redis"

if __name__ == "__main__":
    a1 = ElasticConnPool.instance()
    a2 = ElasticConnPool.instance()
    assert a1 is a2

    a3 = RedisConnPool.instance()
    a4 = RedisConnPool.instance()
    assert a3 is a4

    assert not a1 is a3

    try:
        a3 = ElasticConnPool()
    except Exeception as err:
        print (err)
