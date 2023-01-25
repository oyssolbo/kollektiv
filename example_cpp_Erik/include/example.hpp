#pragma once

/**
 * Examples of public header functions
 * 
 * Also example of overloading a function. Overloading -> same name but different arguments 
 */
void public_header_function();
void public_header_function(int arg);


class ExampleClass
{
private:
  int data;
  int* data_ptr;

  void private_class_func();
  
public:
  ExampleClass(int data_arg) 
  : data(data_arg) {
    data_ptr = new int(data_arg + 69);
  };
  ~ExampleClass() 
  {
    delete data_ptr;
  };

  void pub_class_func();
};


