#include "example.hpp"
#include <thread>    
#include <iostream>
 

// Functions used to showcase threrading in C++
void thread_foo() 
{
  std::cout << "thread_foo()" << std::endl;
}

void thread_bar(int x)
{
  std::cout << "thread_bar() with arg x = " << x << std::endl;
}


int main()
{
  // Public header functions
  public_header_function();
  public_header_function(69);


  // Exampleclass
  ExampleClass example_class(420);
  example_class.pub_class_func(); // Only possible to call the pubklic function class (obviously)
  // example_class.private_class_func(); // Not possible since private


  // Private function declared in the cpp file
  // private_cpp_function(); // Error: undefined function. Reason: not declared in scope




  // Example of threads
  // https://cplusplus.com/reference/thread/thread/

  // Spawn threads
  std::thread first (thread_foo);     
  std::thread second (thread_bar, 0); 

  
  // Wait for the threads to finish
  first.join();
  second.join();

  std::cout << "Done: exiting" << std::endl; 

  return 0;
}