package main

import (
  "fmt"
  "arrayList"
)

func main() {

  intValMap := make(map[string]int)
  dblValMap := make(map[string]float64)
  strValMap := make(map[string]string)

  fmt.Println("")
  fmt.Println("")
  fmt.Println("INTEGER ARRAYLIST")
  intList := arrayList.IntArrayList(10)
  arrayList.PrintIntArrayList(intList)
  arrayList.IntArrayListInsertAtEnd(99, &intList)
  arrayList.IntArrayListInsertAtEnd(100, &intList)
  arrayList.IntArrayListInsertAtEnd(101, &intList)
  arrayList.IntArrayListInsertAtEnd(102, &intList)
  arrayList.IntArrayListInsertAtEnd(103, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.IntArrayListInsertAtIndex(2, 3, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.IntArrayListRemoveAtIndex(1, &intList)
  arrayList.PrintIntArrayList(intList)

  arrayList.IntArrayListRemove(102, &intList)
  arrayList.PrintIntArrayList(intList)

  intValMap = arrayList.IntArrayListGetItemAtIndex(3,intList)
  fmt.Println("Looking for item at index 3.  Is item Valid? ", intValMap["valid"], " Value is ", intValMap["value"])

  intValMap = arrayList.IntArrayListGetItemAtIndex(30,intList)
  fmt.Println("Looking for item at index 30.  Is item Valid? ", intValMap["valid"], " Value is ", intValMap["value"])

  fmt.Println("Is the item at index 1 equal to 3? ", arrayList.IntArrayListIsItemAtEqual(1,3,intList))

  fmt.Println("")
  fmt.Println("")
  fmt.Println("DOUBLE ARRAYLIST")
  dblList := arrayList.DblArrayList(10)
  arrayList.DblArrayListInsertAtEnd(1.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(2.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(3.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(4.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(5.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(6.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(7.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(8.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(9.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(10.1, &dblList)
  arrayList.DblArrayListInsertAtEnd(11.1, &dblList) // Can't add list is full!
  arrayList.PrintDblArrayList(dblList)

  fmt.Println("\nLet's remove value 6.1 from the list")
  arrayList.DblArrayListRemove(6.1, &dblList)
  arrayList.PrintDblArrayList(dblList)

  fmt.Println("\nLet's remove value 106.1 from the list.  Should fail since it doesn't exist")
  arrayList.DblArrayListRemove(106.1, &dblList)
  arrayList.PrintDblArrayList(dblList)

  fmt.Println("\nLet's add 3.14156 to index 2")
  arrayList.DblArrayListInsertAtIndex(2, 3.14156, &dblList)
  arrayList.PrintDblArrayList(dblList)

  dblValMap = arrayList.DblArrayListGetItemAtIndex(3,dblList)
  fmt.Println("\nLooking for item at index 3.  Is item Valid? ", dblValMap["valid"], " Value is ", dblValMap["value"])

  fmt.Println("")
  fmt.Println("")
  fmt.Println("STRING ARRAYLIST")
  strList := arrayList.StrArrayList(10)
  arrayList.StrArrayListInsertAtEnd("Hello", &strList)
  arrayList.StrArrayListInsertAtEnd("there", &strList)
  arrayList.StrArrayListInsertAtEnd("this",  &strList)
  arrayList.StrArrayListInsertAtEnd("is",    &strList)
  arrayList.StrArrayListInsertAtEnd("a",     &strList)
  arrayList.StrArrayListInsertAtEnd("string",&strList)
  arrayList.StrArrayListInsertAtEnd("list",  &strList)
  arrayList.StrArrayListInsertAtEnd("Hope",  &strList)
  arrayList.StrArrayListInsertAtEnd("it",    &strList)
  arrayList.StrArrayListInsertAtEnd("works", &strList)
  arrayList.StrArrayListInsertAtEnd("Oops",  &strList) // Can't add list is full!
  arrayList.PrintStrArrayList(strList)

  fmt.Println("\nLet's remove value 'string' from the list")
  arrayList.StrArrayListRemove("string", &strList)
  arrayList.PrintStrArrayList(strList)

  fmt.Println("\nLet's remove value 'BIGSTRING' from the list.  Should fail since it doesn't exist")
  arrayList.StrArrayListRemove("BIGSTRING", &strList)
  arrayList.PrintStrArrayList(strList)

  fmt.Println("\nLet's add 'Hiya' to index 2")
  arrayList.StrArrayListInsertAtIndex(2, "Hiya", &strList)
  arrayList.PrintStrArrayList(strList)

  strValMap = arrayList.StrArrayListGetItemAtIndex(3,strList)
  fmt.Println("\nLooking for item at index 3.  Is item Valid? ", strValMap["valid"], " Value is ", strValMap["value"])

}
