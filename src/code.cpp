// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Terren Foster";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
    : value(newValue), prevPtr(nullptr), nextPtr(nullptr)
{
        // TODO: move the initialization of all three fields into an initializer list
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    // TODO: return the value field
    return value;
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    // TODO: return the prevPtr field
    return prevPtr;
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    // TODO: return the nextPtr field
    return nextPtr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    // TODO: assign the field
    prevPtr = newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    // TODO: assign the field
    nextPtr = newNextPtr;
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
    :headPtr(nullptr), tailPtr(nullptr), count(0)
{
    // TODO: initialize all three fields (use an initializer list)
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    // TODO: walk through the list and delete every node
    DoubleNode* current = headPtr;
    while (current != nullptr)
    {
        DoubleNode* next = current->getNext();
        delete current;
        current = next;
    }
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    // TODO: implement
    if (headPtr == nullptr)
    {
        return nullptr;
    }
    DoubleNode *node = headPtr;
    headPtr = headPtr->getNext();
    if (headPtr != nullptr)
    {
        headPtr->setPrev(nullptr);
    }
    else
    {
        tailPtr = nullptr;
    }
    node->setPrev(nullptr);
    node->setNext(nullptr);
    count --;
    return node;
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    // TODO: implement
    if (tailPtr == nullptr)
    {
         return nullptr;
    }
    DoubleNode *node = tailPtr;
        tailPtr = tailPtr->getPrev();
    if (tailPtr != nullptr)
    {
        tailPtr->setNext(nullptr);
    }
    else
    {
        tailPtr = nullptr;
    }
    node->setPrev(nullptr);
    node->setNext(nullptr);
    count --;
    return node;

}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    // TODO: implement
    if (headPtr == nullptr)
    {
        return nullptr;
    }
    DoubleNode *current = headPtr;
    while (current != nullptr)
    {
        if (current->getValue() == value)
        {
            if (current == headPtr)
            {
                return detachFirst();
            }
            if (current == tailPtr)
            {
                return detachLast();
            }
            DoubleNode *prev = current->getPrev();
            DoubleNode *next = current->getNext();
            prev->setNext(next);
            next->setPrev(prev);
            current->setPrev(nullptr);
            current->setNext(nullptr);
            count--;
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}
// I used Geeks for Geeks to insert a new node
/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    // TODO: implement
    DoubleNode *newNode = new DoubleNode(value);
    if (headPtr == nullptr)
    {
        headPtr = newNode;
        tailPtr = newNode;
    }
    else
    {
        newNode->setNext(headPtr);
        headPtr->setPrev(newNode);
        headPtr = newNode;
    }
    count++;
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    // TODO: implement
    DoubleNode *newNode = new DoubleNode(value);
    if (tailPtr == nullptr)
    {
        headPtr = newNode;
        tailPtr = newNode;
    }
    else
    {
        newNode->setNext(tailPtr);
        tailPtr->setPrev(newNode);
        tailPtr = newNode;
    }
    count++;
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{
    // TODO: implement
    if (headPtr == nullptr)
    {
        return std::nullopt;
    }
    DoubleNode *node = detachFirst();
    NodeValue value = node->getValue();
    delete node;
    return value;
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    // TODO: implement
    if (headPtr == nullptr)
    {
        return std::nullopt;
    }
    DoubleNode *node = detachLast();
    NodeValue value = node->getValue();
    delete node;
    return value;
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    DoubleNode *node = detachValue(value);
    if (node == nullptr)
    {
        return false;
    }
    delete node;
    return true;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    DoubleNode *current = headPtr;
    while (current != nullptr)
    {
        if (current->getValue() == value)
        {
            return true;
        }
        current = current->getNext();
    }
    return false;
}
//I used both copilot and geeks for geeks for the visit function.
/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    // TODO: implement
    int countPrinted = 0;
    DoubleNode *current = headPtr;
    while (current != nullptr)
    {
        std::visit([](const auto& value)
        {
            std::cout << value << " ";
        }, current->getValue());
        countPrinted++;
        current = current->getNext();
    }
    std::cout << std::endl;
    return countPrinted;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    // TODO: implement
    int countPrinted = 0;
    DoubleNode *current = tailPtr;
    while (current != nullptr)
    {
        std::visit([](const auto& value)
        {
            std::cout << value << " ";
        }, current->getValue());
        countPrinted++;
        current = current->getPrev();
    }
    std::cout << std::endl;
    return countPrinted;
}

/// Return count.
int DoublyLinkedList::length() const
{
    // TODO: implement
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    // TODO: implement
    data.push_front(value);
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    // TODO: implement
    data.push_back(value);
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    // TODO: implement
    if (data.empty())
    {
        return std::nullopt;
    }
    NodeValue value = data.front();
    data.pop_front();
    return value;
}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    // TODO: implement
    if (data.empty())
    {
        return std::nullopt;
    }
    NodeValue value = data.back();
    data.pop_back();
    return value;
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    // TODO: implement
    auto it = std::find(data.begin(), data.end(), value);
    if (it == data.end())
    {
        return false;
    }
    data.erase(it);
    return true;
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    auto it = std::find(data.begin(), data.end(), value);
    return it != data.end();
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    // TODO: implement
   int countPrinted = 0;
   for (const auto &value : data)
   {
    std::visit([](const auto &v)
    {
        std::cout << v << " ";
    }, value);
    countPrinted++;
   }
   std::cout << std::endl;
   return countPrinted;
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    // TODO: implement
    int countPrinted = 0;
    auto it = data.end();
    while (it != data.begin())
    {
        --it;
        std::visit([](const auto& value)
    {
        std::cout << value << " ";
    }, *it);
    countPrinted++;
    }
    std::cout << std::endl;
    return countPrinted;
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    // TODO: implement
    return static_cast<int>(data.size());
}
// ===== END PART 3 (do not remove this marker) =====
