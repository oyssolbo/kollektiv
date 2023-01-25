#include <iostream>
#include "example.hpp"

/** 
 * Example of forward-declaration of function in cpp file, such that other
 * functions can use it
 */
int private_cpp_function(int);




/**
 * Public functions declared in the header file
 * Also used to showcase forward-declare of private_cpp_function()  
 */
void public_header_function()
{
  std::cout << "public_header_function()" << std::endl;
}

void public_header_function(int arg)
{
  std::cout << "overloaded public_header_function(int) calling the private_cpp_function()" << std::endl;
  std::cout << private_cpp_function(arg) << std::endl;
}




/**
 * Definitions of private and public member functions
 * 
 * The private function can only be called from within the class 
 */

void ExampleClass::private_class_func()
{
  std::cout << "private member function of example class" << std::endl;
  std::cout << *data_ptr << std::endl;
}

void ExampleClass::pub_class_func()
{
  std::cout << "public member function of example class" << std::endl;
  std::cout << data << std::endl;

  std::cout << "invoking private function from public" << std::endl;
  private_class_func();
}






/**
 * Definition of the private function class 
 */
int private_cpp_function(int arg)
{
  std::cout << "private_cpp_function()" << std::endl;
  return arg * 69;
}
