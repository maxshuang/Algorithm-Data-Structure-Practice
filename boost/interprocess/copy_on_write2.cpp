#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>
#include <iostream>

int main ()
{
   using namespace boost::interprocess;
    const char *managed_file  = "MySharedMemory2";
   //Remove shared memory on construction and destruction
   struct shm_remove
   {
      shm_remove() { 
            shared_memory_object::remove("MySharedMemory2"); 
        }
      ~shm_remove(){ 
            //shared_memory_object::remove("MySharedMemory"); 
        }
   } remover;


   //Shared memory front-end that is able to construct objects
   //associated with a c-string. Erase previous shared memory with the name
   //to be used and create the memory segment at the specified address and initialize resources
   managed_shared_memory segment(create_only, managed_file, 65536);          //segment size in bytes
   //segment.construct<int>("MyInt1")(1);
   
   //Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
   //so the allocator must allocate that pair.
   typedef int    KeyType;
   typedef float  MappedType;
   typedef std::pair<const int, float> ValueType;

   //Alias an STL compatible allocator of for the map.
   //This allocator will allow to place containers
   //in managed shared memory segments
   typedef allocator<ValueType, managed_shared_memory::segment_manager>
      ShmemAllocator;

   //Alias a map of ints that uses the previous STL-like allocator.
   //Note that the third parameter argument is the ordering function
   //of the map, just like with std::map, used to compare the keys.
   typedef map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MyMap;

   //Initialize the shared memory STL-compatible allocator
   ShmemAllocator alloc_inst (segment.get_segment_manager());

    const char *map_obj="MyMap";
   //Construct a shared memory map.
   //Note that the first parameter is the comparison function,
   //and the second one the allocator.
   //This the same signature as std::map's constructor taking an allocator
   MyMap *mymap =
      segment.construct<MyMap>(map_obj)      //object name
                                 (std::less<int>() //first  ctor parameter
                                 ,alloc_inst);     //second ctor parameter

   //Insert data in the map
   for(int i = 0; i < 100; ++i){
      mymap->insert(std::pair<const int, float>(i, (float)i));
   }
    std::cout << "parent MyMap pre:" << (*mymap)[1] << std::endl;
    std::cout << "parent MyMap pre:" << mymap->size() << std::endl;

    if(0==fork()) {
        // child process 1, copy the entire segment to child1 if it makes changes
        managed_shared_memory segment_child1
            (open_copy_on_write
            ,managed_file //segment name
            );
        MyMap *mymap = segment_child1.find<MyMap>(map_obj).first;
        (*mymap)[1]=11.0;
        (*mymap)[2]=12.0;
        mymap->erase(98);

        std::cout << "child1 MyMap:" << (*mymap)[1] << std::endl;
        std::cout << "child1 MyMap:" << mymap->size() << std::endl;
        return 0;
    }

    if(0==fork()) {
        ::sleep(1);
        // child process 2
        managed_shared_memory segment_child2
            (open_read_only
            ,managed_file//segment name
            );
        MyMap *mymap = segment_child2.find<MyMap>(map_obj).first;

        std::cout << "child2 MyMap:" << (*mymap)[1] << std::endl;
        std::cout << "child2 MyMap:" << mymap->size() << std::endl;
        return 0;
    }

    int sleep = 5;
    while (--sleep) {
        std::cout << "parent sleeping..." << std::endl;
        ::sleep(1);
    }
    std::cout << "parent MyMap:" << (*mymap)[1] << std::endl;
    std::cout << "parent MyMap:" << mymap->size() << std::endl;
    segment.destroy<MyMap>(map_obj);

    return 0;
}