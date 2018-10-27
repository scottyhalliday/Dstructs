package arrayList

import "fmt"

type dblListStruct struct {
  maxSize int
  length  int
  aList   []float64
}

// ----------------------------------------------------------------------------

// Initializes the array list and its structure components and returns the
// initialized struct
func DblArrayList(aSize int) dblListStruct {

  var list dblListStruct
  var indx int

  // Initialize the array list structure elements
  list.maxSize = aSize
  list.length  = 0

  indx = 0
  for indx < aSize {
      list.aList   = append(list.aList, 0.0)
      indx = indx+1
  }

  return list
}

// ----------------------------------------------------------------------------

// Returns if the list is is full
func DblArrayListIsFull(list dblListStruct) bool {

  var result bool

  result = false

  if list.length == list.maxSize {
    result = true
  }
  return result

}

// ----------------------------------------------------------------------------

// Returns if the list is is empty
func DblArrayListIsEmpty(list dblListStruct) bool {

  var result bool

  result = false

  if list.length == 0 {
    result = true
  }
  return result

}

// ----------------------------------------------------------------------------

// Returns the maximum size of the array list
func DblArrayListMaxSize(list dblListStruct) int {
  return list.maxSize
}

// ----------------------------------------------------------------------------

// Returns the current length of the list
func DblArrayListLength(list dblListStruct) int {
  return list.length
}

// ----------------------------------------------------------------------------

// Search for an item in the list and return the index if it exists
func SearchDblArrayList(value float64, list dblListStruct) int {

  var indx int

  for indx < list.length {
    if value == list.aList[indx] {
      return indx
    }
    indx++
  }

  return -1
}

// ----------------------------------------------------------------------------

// Adds an item at the end of the list.  The item cannot already exist and
// the list cannot be full.
func DblArrayListInsertAtEnd(value float64, list *dblListStruct) int {

  // Is the list full?
  if DblArrayListIsFull(*list) == true {
    fmt.Println("insertAtEnd Error: List is full cannot add new item")
    return 1
  }

  // Does the list already have the value
  if SearchDblArrayList(value, *list) > -1 {
    fmt.Println("insertAtEnd Error: List already has the value ", value)
    return 1
  }

  list.aList[list.length] = value
  list.length++

  return 0
}

// ----------------------------------------------------------------------------

// Adds an item into the list at the specified index.  If the list is full,
// or the value is already in the list or the index given is invalid then
// nothing is added
func DblArrayListInsertAtIndex(index int, value float64, list *dblListStruct) int {

  var i int

  // Is the list full?
  if DblArrayListIsFull(*list) == true {
    fmt.Println("insertAtEnd Error: List is full cannot add new item")
    return 1
  }

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("insertAtEnd Error: Index given is outside the range of list")
    return 1
  }

  // Does the list already have the value
  if SearchDblArrayList(value, *list) > -1 {
    fmt.Println("insertAtEnd Error: List already has the value ", value)
    return 1
  }

  // Shift the contents over by one after index
  i = list.length
  for i > index {
    list.aList[i] = list.aList[i-1]
    i--
  }

  list.aList[index] = value
  list.length++

  return 0
}

// ----------------------------------------------------------------------------

// Removes the item at specified index.  The index must be valid
func DblArrayListRemoveAtIndex(index int, list *dblListStruct) int {

  var i int

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("insertAtEnd Error: Index given is outside the range of list")
    return 1
  }

  // Shift the contents over by one after index
  i = index
  for i < list.length-1 {
    list.aList[i] = list.aList[i+1]
    i++
  }

  list.length--

  return 0
}

// ----------------------------------------------------------------------------

// Searchs for a value in the list and removes it.  If the item does not exist
// then nothing is done.
func DblArrayListRemove(value float64, list *dblListStruct) int {

  var i     int
  var index int

  // Get the index of the value in the list.  If -1 is returned then the
  // value does not exist in the list
  index = SearchDblArrayList(value, *list)

  // Is the index valid?
  if (index == -1) {
    fmt.Println("Remove Error: Value ", value, " does not exist in list.  Cannot remove")
    return 1
  }

  // Shift the contents over by one after index
  i = index
  for i < list.length-1 {
    list.aList[i] = list.aList[i+1]
    i++
  }

  list.length--

  return 0
}

// ----------------------------------------------------------------------------

// Searchs for a value in the list and removes it.  If the item does not exist
// then nothing is done.  Returns a map which identifies if value was found
// and the value itself.  If not found then zero's are returned
func DblArrayListGetItemAtIndex(index int, list dblListStruct) map[string]float64 {

  result := make(map[string]float64)

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("GetItemAtIndex Error: Index is not in valid range")
    result["valid"] = 0
    result["value"] = 0
    return result
  }

  result["valid"] = 1
  result["value"] = list.aList[index]

  return result
}

// ----------------------------------------------------------------------------

// Check if an item is equal at an index
func DblArrayListIsItemAtEqual(index int, value float64, list dblListStruct) bool {

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("IsItemAtEqual Error: Index is not in valid range")
    return false
  }

  if list.aList[index] == value {
    return true
  }

  return false
}

// ----------------------------------------------------------------------------

// Print the contents of the array list
func PrintDblArrayList(list dblListStruct) {

  var indx int

  fmt.Println("DOUBLE ARRAY LIST: ")

  for indx < list.length {
    if indx % 10 == 0 && indx != 0 {
      fmt.Println("")
    }
    fmt.Print(list.aList[indx], ", ")
    indx = indx + 1
  }
  fmt.Println("")

}

// ----------------------------------------------------------------------------

// Clear the array list
func ClearDblArrayList(list *dblListStruct) {
  list.length = 0
}
