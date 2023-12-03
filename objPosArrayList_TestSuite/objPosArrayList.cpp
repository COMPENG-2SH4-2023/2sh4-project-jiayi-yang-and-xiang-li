#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on the heap
    listSize = 0;                      // notn valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;     // array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;//this is a list should be delete with square bracket
}                  //remmber to use delete[] to call the destructors of all instances in the array
                // otherwise only the first element will be properly deleted, leading to leak

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{   
    //still need error check - what if listsize is at capacity?
    if(listSize != ARRAY_MAX_CAP)// check if listsize is equal to arrayCapacity. if yes,at capacity,dont insert
    {
        for(int i = listSize; i > 0; i--)
        {
            aList[i].setObjPos(aList[i-1]); //this will shuffle all the elemetns towards the tail
        }
        aList[0].setObjPos(thisPos);
        listSize++; 
    }

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize != ARRAY_MAX_CAP)
    {   
        
        aList[listSize].setObjPos(thisPos); //do not need to shuffle
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    if(listSize != 0)
    {
        for(int i = 0; i < listSize; i++)
        {
            aList[i].setObjPos(aList[i+1]); //just shuffle and the first one will be overwrite which do not need to delete
        }
        listSize--;        
    }

}

void objPosArrayList::removeTail()
{   
    if(listSize != 0)
    {
        //do not need to shuffle
        listSize--;    
    }


}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);//need to check
}