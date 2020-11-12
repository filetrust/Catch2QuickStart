# Catch2QuickStart
This is a quick start to utilising the Catch2 unit testing framework and demonstrates how we can unit test C++ code. Utilising Catch2 just requires a single header file downloadable from [Catch2](https://github.com/catchorg/Catch2) that needs to be compiled into a test project.

The Catch2QuickStart solution has two projects:

- A project to illustrate code under test
- A unit test project to illustrate unit testing with Catch2. 

### Code Under Test Project

Consider a project that has the following code that we would like to unit test:

- An interface called `IMyInterface`.

```
 #pragma once
 #include <iostream>
  
 class IMyInterface
 {
 public:
     virtual ~IMyInterface() {};
     virtual std::string f() = 0;
 };
```

- A class called `ClassA` derives from `IMyInterface` and has a method `Class::f()`  that returns a string

```
 #include "ClassA.h"
  
 std::string ClassA::f()
 {
     return "I am a real class A";
 }
```

- A class called `ClassB` that has a method `ClassB::g()` that returns a string using an instance of IMyInterface passed as a parameter.

```
 #include "ClassB.h"
  
 std::string ClassB::g(IMyInterface& myInterface)
 { 
     return myInterface.f(); 
 }
```

### The Unit Test Project

 A standard unit test project, a standard console executable, is created and then:

- The download catch2 header file, *catch.hpp*, is added to the project
- A *main.test.cpp* is created to include the *catch.hpp* **once** only.

```
 // tests-main.cpp
 // https://github.com/catchorg/Catch2/releases/tag/v2.13.1
 #define CATCH_CONFIG_MAIN
 #include "catch.hpp"
```

- Project properties are made to reference the include headers, library directory and object files for the code under test.
- A *ClassB.tests.cpp* is created to test class `ClassB` 

The *ClassB.tests.cpp* has two test cases using a modern [AAA](https://www.thephilocoder.com/unit-testing-aaa-pattern/) (Arrange, Act and Assert testing pattern layout).

**Test Case 1:**

```
 TEST_CASE("ClassB.using class A", "[ClassB]")
 {
     // Arrange
     ClassA classA;
     ClassB classB;
  
     // Act
     auto result = classB.g(classA);
  
     // Assert
     REQUIRE(result == "I am a real class A");
 }
```

- In the above test case, we **arrange** two classes
  - Our interest lies in `classB` which is the code that is under test
  - `ClassA` is used to help facilitate the testing of `classB`
- We **act** by calling `class.B.g` which relies on on an instance of `ClassA` being passed to it
- We **assert** that the string is returned by `classA`.

At this point, we can run the project test executable and we will see all our tests being run. 

There is a  [Catch2 Test Adaptors for Visual Studio](https://marketplace.visualstudio.com/items?itemName=JohnnyHendriks.ext01) that one can install to be able to take advantage of the Visual Studio Test Explorer. A *.runsettings* file just needs to be created at the root of the solution with  minimum content as follows.

```
<?xml version="1.0" encoding="utf-8"?>
<RunSettings>

<!-- Adapter Specific sections -->
<Catch2Adapter>
    <FilenameFilter>.*</FilenameFilter><!-- Regex filter -->
</Catch2Adapter>

</RunSettings>
```

Note: the *.runsettings* file will need to be loaded in Visual Studio via Test->Test Settings->Select Test Settings File before the tests are visible in the Visual Studio Test Explorer.

## FakeIt Mocking Framework

With a codebase that uses an OO language such as C++, a complimentary mocking framework should be used with the unit testing framework.  [FakeIt](https://github.com/eranpeer/FakeIt) is yet another single header only include.  Mocking provides us with an ability to remove the need to worry about creating classes, such as `ClassA`, and have better control over how they interact with the class under test, that is `ClassB`. 

**Test Case 2:**

```
 TEST_CASE("ClassB.using mock class A", "[ClassB]")
 {
     // Arrange
     Mock<IMyInterface> mockMyInterface;
     When(Method(mockMyInterface, f)).Return("I am a mock of class A");
     ClassB classB;
  
     // Act
     auto result = classB.g(mockMyInterface.get());
  
     // Assert
     REQUIRE(result == "I am a mock of class A");
 }
```

In our test 2, we now use `FakeIt` to arrange a mock of `ClassA`:

- Mocking a class is only possible if we use an interface: `ClassA` is an instance of IMyInterface
- The When(Method(...)) in the Arrange section is showing that our mock of `ClassA` must return this particular string when `ClassA::f()`  is invoked.
