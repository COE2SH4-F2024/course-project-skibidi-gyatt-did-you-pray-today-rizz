#include "objPosArrayList.h"
#include <stdexcept> // for std::out_of_range exception

using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = 200;
    aList = new objPos[arrayCapacity];

    for (int i = 0; i < listSize; i++)
        aList[i] = objPos();
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
    aList = nullptr;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= arrayCapacity)
        return;

    for(int i = listSize; i > 0; i--)   
        aList[i] = aList[i - 1];

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
        return;

    aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
        return;
    else if(listSize == 1) {
        aList[0] = objPos();
        listSize--;
        return;
    }

    for(int i = 0; i < listSize - 1; i++)   
        aList[i] = aList[i + 1];

    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
        return;

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0)
        throw out_of_range("Index out of bounds.");

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0)
        throw out_of_range("Index out of bounds.");
    
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0 || index >= arrayCapacity)
        throw out_of_range("Index out of bounds.");

    return aList[index];
}