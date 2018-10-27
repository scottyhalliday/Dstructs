package main

import (
  "fmt"
  "arrayList"
)

func main() {

  intValMap := make(map[string]int)

  fmt.Println("In main and imported ArrayList")
  intList := arrayList.IntArrayList(10)
  arrayList.PrintIntArrayList(intList)
  fmt.Println("Is the array list full? ", arrayList.IntArrayListIsFull(intList))
  fmt.Println("Is the array list empty? ", arrayList.IntArrayListIsEmpty(intList))
  arrayList.InsertAtEnd(99, &intList)
  arrayList.InsertAtEnd(100, &intList)
  arrayList.InsertAtEnd(101, &intList)
  arrayList.InsertAtEnd(102, &intList)
  arrayList.InsertAtEnd(103, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.InsertAtIndex(2, 3, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.RemoveAtIndex(1, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.Remove(102, &intList)
  arrayList.PrintIntArrayList(intList)

  intValMap = arrayList.GetItemAtIndex(3,intList)
  fmt.Println("Looking for item at index 3.  Is item Valid? ", intValMap["valid"], " Value is ", intValMap["value"])

  intValMap = arrayList.GetItemAtIndex(30,intList)
  fmt.Println("Looking for item at index 30.  Is item Valid? ", intValMap["valid"], " Value is ", intValMap["value"])

  fmt.Println("Is the item at index 1 equal to 3? ", arrayList.IsItemAtEqual(1,3,intList))

}
