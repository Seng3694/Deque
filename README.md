# Simple Deque in C #
Simple implementation of a [double-ended queue (deque)][2] in C.

This implementation uses a single array with a single allocation. You can use the `Deque_Resize` function to resize it or enable dynamic resizing.

## How to use ##

```C
#include <deque.h>

int main(void)
{
    //create a deque with capacity 10
    Deque* deque = Deque_Create(10);

    //get the size of the deque
    assert(Deque_GetSize(deque) == 0);
    //get the capacity of the deque
    assert(Deque_GetCapacity(deque) == 10);

    //push something back
    Deque_PushBack(deque, 1);
    //push something front
    Deque_PushFront(deque, 2);

    assert(Deque_GetSize(deque) == 2);
    assert(Deque_GetCapacity(deque) == 10);

    //peek which value is at the back (without removing it)
    assert(Deque_PeekBack(deque) == 1);

    //peek which value is at the front (without removing it)
    assert(Deque_PeekFront(deque) == 2);

    assert(Deque_GetSize(deque) == 2);
    assert(Deque_GetCapacity(deque) == 10);

    //pop value at the back
    assert(Deque_PopBack(deque) == 1);

    //pop value at the front
    assert(Deque_PopFront(deque) == 2);
    
    assert(Deque_GetSize(deque) == 0);
    assert(Deque_GetCapacity(deque) == 10);

    //resize internal array to 5
    Deque_Resize(deque, 5);
    assert(Deque_GetCapacity(deque) == 5);

    //cleanup
    Deque_Destroy(deque);

    return 0;
}
```

For more insight you can check the [tests][4].

If you are building with [CMake][1] you can enable the `DYNAMIC_DEQUE` option with `-DDYNAMIC_DEQUE=ON`. 
This automatically resizes the deque when you push values to it without enough capacity. An automatic resize resizes the internal array by 1.5 times the capacity.
For example you are pushing a value to a deque with a size and capacity of 10, the capacity will be resized to 15.

This option is **disabled** by default.

## Build ##

Project uses [CMake][1].

You can include this project as a submodule:

```
git submodule add "https://github.com/Seng3694/Deque"
```

And then add the directory to your CMakeLists:
```CMake
add_subdirectory(Deque)
```

And link it with your application:
```CMake
target_link_libraries(YOUR_TARGET Deque)
```

Or just embed it manually.

Example cmake command for the dynamic deque:

```
cmake -G"Visual Studio 15" -DDYNAMIC_DEQUE=ON  YOUR/PROJECT/DIRECTORY
```

You can also just enable it in CMake before including the subdirectory:
```CMake
option(DYNAMIC_DEQUE ON)
```

## License ##
This Code is licensed under the MIT License. See [LICENSE][3] for more information.

[1]:http://www.cmake.org/
[2]:https://en.wikipedia.org/wiki/Double-ended_queue
[3]:LICENSE
[4]:src/test.c