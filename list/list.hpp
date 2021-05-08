
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace vlnk {

/* ************************************************************************** */

template <typename Data>
class List: virtual public LinearContainer<Data>,
            virtual public MappableContainer<Data>,
            virtual public FoldableContainer<Data> { 

protected:

  using LinearContainer<Data>::size;

  struct Node
  {

    // Data
    Data value;
    Node* nextptr = nullptr;

    Node() = default;

    // Specific constructors
    Node(const Data&);

    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&) noexcept;

    // Destructor
    virtual ~Node() = default;

  };

  Node* head = nullptr;
  Node* tail = nullptr;

public:

  // Default constructor
  List() = default;

  // Specific constructor
  List(const LinearContainer<Data>&);

  /* ************************************************************************ */

  // Copy constructor
  List(const List&);

  // Move constructor
  List(List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List& operator=(const List&);

  // Move assignment
  List& operator=(List&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List&) const noexcept;
  inline bool operator!=(const List&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data&);
  void InsertAtFront(Data&&) noexcept;

  void InsertAtBack(const Data&);
  void InsertAtBack(Data&&) noexcept;

  void RemoveFromFront();
  Data FrontNRemove();

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override;

  // Specific member functions (inherited from LinearContainer)
  Data& Front() const override;
  Data& Back() const override;
  Data& operator[](const ulong) const override;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;
  void MapPreOrder(const MapFunctor, void*) override;
  void MapPostOrder(const MapFunctor, void*) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void FoldPreOrder(const FoldFunctor, const void*, void*) const override;
  void FoldPostOrder(const FoldFunctor, const void*, void*) const override;

protected:

  // Auxiliary member functions (for MappableContainer) (Recursive use)

  // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for FoldableContainer) (Recursive use)

  // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
