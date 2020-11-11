#include "catch.hpp"
#include "fakeit.hpp"
#include "IMyInterface.h"
#include "ClassA.h"
#include "ClassB.h"

using namespace fakeit;

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