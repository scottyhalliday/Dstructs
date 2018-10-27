package arrayList

import "fmt"

type strListStruct struct {
  maxSize int
  length  int
  aList   []string
}

// ----------------------------------------------------------------------------

// Initializes the array list and its structure components and returns the
// initialized struct
func StrArrayList(aSize int) strListStruct {

  var list strListStruct
  var indx int

  // Initialize the array list structure elements
  list.maxSize = aSize
  list.length  = 0

  indx = 0
  for indx < aSize {
      list.aList   = append(list.aList, "")
      indx = indx+1
  }

  return list
}

// ----------------------------------------------------------------------------

// Returns if the list is is full
func StrArrayListIsFull(list strListStruct) bool {

  var result bool

  result = false

  if list.length == list.maxSize {
    result = true
  }
  return result

}

// ----------------------------------------------------------------------------

// Returns if the list is is empty
func StrArrayListIsEmpty(list strListStruct) bool {

  var result bool

  result = false

  if list.length == 0 {
    result = true
  }
  return result

}

// ----------------------------------------------------------------------------

// Returns the maximum size of the array list
func StrArrayListMaxSize(list strListStruct) int {
  return list.maxSize
}

// ----------------------------------------------------------------------------

// Returns the current length of the list
func StrArrayListLength(list strListStruct) int {
  return list.length
}

// ----------------------------------------------------------------------------

// Search for an item in the list and return the index if it exists
func SearchStrArrayList(value string, list strListStruct) int {

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
func StrArrayListInsertAtEnd(value string, list *strListStruct) int {

  // Is the list full?
  if StrArrayListIsFull(*list) == true {
    fmt.Println("insertAtEnd Error: List is full cannot add new item")
    return 1
  }

  // Does the list already have the value
  if SearchStrArrayList(value, *list) > -1 {
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
func StrArrayListInsertAtIndex(index int, value string, list *strListStruct) int {

  var i int

  // Is the list full?
  if StrArrayListIsFull(*list) == true {
    fmt.Println("insertAtEnd Error: List is full cannot add new item")
    return 1
  }

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("insertAtEnd Error: Index given is outside the range of list")
    return 1
  }

  // Does the list already have the value
  if SearchStrArrayList(value, *list) > -1 {
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
func StrArrayListRemoveAtIndex(index int, list *strListStruct) int {

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
func StrArrayListRemove(value string, list *strListStruct) int {

  var i     int
  var index int

  // Get the index of the value in the list.  If -1 is returned then the
  // value does not exist in the list
  index = SearchStrArrayList(value, *list)

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
func StrArrayListGetItemAtIndex(index int, list strListStruct) map[string]string {

  result := make(map[string]string)

  // Is the index valid?
  if (index < 0 || index > list.length) {
    fmt.Println("GetItemAtIndex Error: Index is not in valid range")
    result["valid"] = "0"
    result["value"] = ""
    return result
  }

  result["valid"] = "1"
  result["value"] = list.aList[index]

  return result
}

// ----------------------------------------------------------------------------

// Check if an item is equal at an index
func StrArrayListIsItemAtEqual(index int, value string, list strListStruct) bool {

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
func PrintStrArrayList(list strListStruct) {

  var indx int

  fmt.Println("STRING ARRAY LIST: ")

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
func ClearStrArrayList(list *strListStruct) {
  list.length = 0
}
