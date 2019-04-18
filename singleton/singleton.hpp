/*
 * In C++11, this design is thread safe. 
 * - According to the standard, §6.7 [stmt.dcl] p4:
 *   If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization.
 *
 * GCC and VS support for the feature (Dynamic Initialization and Destruction with Concurrency, also known as Magic Statics on MSDN) is as follows:
 * - Visual Studio: supported since Visual Studio 2015
 * - GCC: supported since GCC 4.3
 *
 */

class Singleton {
private:
    //make the constructor private
    Singleton() {
        //TODO: add custom logic to allocate resources
    }; 

public:
    Singleton(const Singleton &) = delete ; //disable copy constructor
    void operator=(const Singleton &) = delete; //disable assignment operator

    virtual ~Singleton() {
        //TODO: add custom logic to dellocate resources
    };

    /*
     * static method to get the instance
     * instance is static inside the method, quarantee release
     **/
    static Singleton *getInstance() {
        static Singleton instance;
        return &instance;
    };
};
