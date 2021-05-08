
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>
#include <functional>

namespace vlnk {

class Container {

protected:

  ulong size = 0;

public:

  virtual ~Container() = default; //Destructor

  Container& operator=(const Container&) = delete; //Copy assignment's not possible
  Container& operator=(Container&&) noexcept = delete; //Move assignment's not possible

  //Comparison operators are not possible
  Container& operator==(const Container&) const noexcept = delete;
  Container& operator!=(const Container&) const noexcept = delete; 

  //Check if container is empty
  virtual inline bool Empty() const noexcept {

    return (size==0); //Returns true if size is equal to zero

  }

  virtual inline ulong Size() const noexcept {

    return size; //returns container's size

  }

  //Used to clear out the container
  virtual void Clear() = 0; //pure virtual ( thanks to Clear() pure virtual function, Container class is now abstract )

};

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public Container {

public:

  virtual ~LinearContainer() = default; //Destructor

  LinearContainer& operator=(const LinearContainer&) = delete; //Copy assignment's not possible
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; //Move assignment's not possible

  //Comparison operators are not possible
  bool operator==(const LinearContainer&) const noexcept = delete;
  bool operator!=(const LinearContainer&) const noexcept = delete;

  virtual Data& Front() const = 0; //Returns the first element
  virtual Data& Back() const = 0; //Returns the last element

  virtual Data& operator[](const ulong) const = 0;

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer: virtual public Container {

public:

  virtual ~TestableContainer() = default; //Destructor

  TestableContainer& operator=(const TestableContainer&) = delete; //Copy assignment's not possible
  TestableContainer& operator=(TestableContainer&&) noexcept = delete; //Move assignment's not possible

  //Comparison operators are not possible
  bool operator==(const TestableContainer&) const noexcept = delete;
  bool operator!=(const TestableContainer&) const noexcept = delete;

  virtual bool Exists(const Data&) const noexcept = 0; //Returns true if a certain data exists

};

/* ************************************************************************** */

template <typename Data>
class MappableContainer: virtual public Container {

public:

  virtual ~MappableContainer() = default; //Destructor

  MappableContainer& operator=(const MappableContainer&) = delete; //Copy assignment's not possible
  MappableContainer& operator=(MappableContainer&&) noexcept = delete; //Move assignment's not possible

  //Comparison operators are not possible
  bool operator==(const MappableContainer&) const noexcept = delete;
  bool operator!=(const MappableContainer&) const noexcept = delete;

  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void MapPreOrder(const MapFunctor, void*) = 0;
  virtual void MapPostOrder(const MapFunctor, void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer: virtual public TestableContainer<Data> {

public:

  virtual ~FoldableContainer() = default; //Destructor

  FoldableContainer& operator=(const FoldableContainer&) = delete; //Copy assignment's not possible
  FoldableContainer& operator=(FoldableContainer&&) noexcept = delete; //Move assignment's not possible

  //Comparison operators are not possible
  bool operator==(const FoldableContainer&) const noexcept = delete;
  bool operator!=(const FoldableContainer&) const noexcept = delete;

  //Specific member functions
  typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;

  virtual void FoldPreOrder(const FoldFunctor, const void*, void*) const = 0;
  virtual void FoldPostOrder(const FoldFunctor, const void*, void*) const = 0;

  virtual bool Exists(const Data&) const noexcept override;

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
