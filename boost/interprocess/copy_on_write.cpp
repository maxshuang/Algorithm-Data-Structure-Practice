#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/managed_shared_memory.hpp>
#include <functional>
#include <utility>
#include <iostream>

int main ()
{
   using namespace boost::interprocess;

   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { 
            shared_memory_object::remove("MySharedMemory"); 
        }
      ~shm_remove(){ 
            //shared_memory_object::remove("MySharedMemory"); 
        }
   } remover;

    const char *managed_file  = "MySharedMemory";
   //Shared memory front-end that is able to construct objects
   //associated with a c-string. Erase previous shared memory with the name
   //to be used and create the memory segment at the specified address and initialize resources
   managed_shared_memory segment(create_only, managed_file, 65536);          //segment size in bytes
    segment.construct<int>("MyInt1")(1);
    segment.construct<int>("MyInt2")(2);
    segment.construct<int>("MyInt3")(3);

    if(0==fork()) {
        // child process 1
        managed_shared_memory segment_child1
            (open_copy_on_write
            ,managed_file //segment name
            );
        int *myint1 = segment_child1.find<int>("MyInt1").first;
        *myint1=11;
        int *myint2 = segment_child1.find<int>("MyInt2").first;

        std::cout << "child1 MyInt1：" << *myint1 << std::endl;
        std::cout << "child1 MyInt2：" << *myint2 << std::endl;
        return 0;
    }

    if(0==fork()) {
        ::sleep(1);
        // child process 2
        managed_shared_memory segment_child2
            (open_read_only
            ,managed_file//segment name
            );
        int *myint1 = segment_child2.find<int>("MyInt1").first;
        int *myint2 = segment_child2.find<int>("MyInt2").first;

        std::cout << "child2 MyInt1：" << *myint1 << std::endl;
        std::cout << "child2 MyInt2：" << *myint2 << std::endl;
        return 0;
    }

    int sleep=5;
    while(--sleep) {
        std::cout << "parent sleeping..." << std::endl;
        ::sleep(1);
    }
    int *myint1 = segment.find<int>("MyInt1").first;
    int *myint2 = segment.find<int>("MyInt2").first;

    std::cout << "parent MyInt1：" << *myint1 << std::endl;
    std::cout << "parent MyInt2：" << *myint2 << std::endl;
    segment.destroy<int>("MyInt1");
    segment.destroy<int>("MyInt2");
    segment.destroy<int>("MyInt3");
    return 0;
}