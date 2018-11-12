#
# arrayList.rb
# By Scott Hall
#
# Data structure for an Array List

class ArrayList

  # ---------------------------------------------------------------------------

  # Constructor for initializing the ArrayList.  The maximum size of the array
  # list is required.  If the list is to adhere to strict data types, meaning
  # only the array consists of the same data types, then set strict to true.
  # Otherwise the list will be a dynamic type list
  def initialize(maxSize, strict=false)
    @aList   = Array.new(maxSize)
    @maxSize = maxSize
    @length  = 0
    @strict  = strict
    @aType   = nil
  end

  # ---------------------------------------------------------------------------

  # Accessor method for retrieving the list maximum size
  def getMaxSize
    @maxSize
  end

  # ---------------------------------------------------------------------------

  # Check if the list is currently full
  def isFull()
    if @length == @maxSize
      return true
    else
      return false
    end
  end

  # ---------------------------------------------------------------------------

  # Check if the list is empty
  def isEmpty()
    if @length == 0
      return true
    else
      return false
    end
  end

  # ---------------------------------------------------------------------------

  # Clear the list.  This simply sets the @length aTypeattribute to zero which serves
  # to overwrite existing values in the array
  def clear()
    @length = 0
  end

  # ---------------------------------------------------------------------------

  # Does the list use strict data types
  def isStrict
    @strict
  end

  # ---------------------------------------------------------------------------

  # Search the array for the value specified value.  If not present then nil is
  # returned
  def searchArrayList(value)
    return @aList.index value
  end

  # ---------------------------------------------------------------------------

  # Insert an item at the end of the list if it is not already present and the
  # list is not full
  def insertAtEnd(value)

    # Is the list full?
    if isFull()
      puts "ERROR: insertAtEnd(): List is full cannot add additional items"
      return
    end

    # Is the value already in the list?
    if searchArrayList(value) != nil
      puts "ERROR: insertAtEnd(): List already contains '#{value}'"
      return
    end

    # If the list is set to consist of strict data types then check value
    # type as well
    if isStrict() == true

      # If the list is empty then the first item added will dictate the
      # list type
      if @aType == nil
        @aType = value.class
      else
        if value.class != @aType
          puts "ERROR: insertAtEnd(): List is set to strict data type '#{@aType}' and value passed is of type '#{value.class}'.  Cannot add new value."
          return
        end
      end
      # Otherwise the value can be added so proceed!
    end

    @aList[@length] = value
    @length += 1

  end

  # ---------------------------------------------------------------------------

  # Insert an item at the end of the list if it is not already present and the
  # list is not full
  def insertAtIndex(value, index)

    # Is the list full?
    if isFull()
      puts "ERROR: insertAtIndex(): List is full cannot add additional items"
      return
    end

    # Is the value already in the list?
    if searchArrayList(value) != nil
      puts "ERROR: insertAtIndex(): List already contains '#{value}'"
      return
    end

    # Is index valid?
    if (index < 0 || index > @length)
      puts "ERROR: insertAtIndex(): Index '#{index}' is outside range of list 0...'#{@length}'.  Cannot add value"
      return
    end

    # If the list is set to consist of strict data types then check value
    # type as well
    if isStrict() == true

      # If the list is empty then the first item added will dictate the
      # list type
      if @aType == nil
        @aType = value.class
      else
        if value.class != @aType
          puts "ERROR: insertAtIndex(): List is set to strict data type '#{@aType}' and value passed is of type '#{value.class}'.  Cannot add new value."
          return
        end
      end
      # Otherwise the value can be added so proceed!
    end

    # Use Ruby's built-in array insert method to handle this request
    @aList.insert(index, value)
    @length += 1

  end

  # ---------------------------------------------------------------------------

  # Remove the item located at the specified array index
  def removeAtIndex(index)

    # Check if index is in valid range
    if (index < 0 || index > @length)
      puts "ERROR: removeAtIndex(): Index '#{index}' is outside range of list 0...'#{@length}'.  Cannot add value"
      return
    end

    @aList.delete_at(index)
    @length -= 1

  end

  # ---------------------------------------------------------------------------

  # Remove the specified value from the list.  If it does not exist then
  # nothing is done.
  def remove(value)

    index = searchArrayList(value)

    if index == nil
      puts  "ERROR: remove(): Value '#{value}' does not exist in the list.  Cannot remove!"
      return
    end

    @aList.delete_at(index)
    @length -= 1

  end

  # ---------------------------------------------------------------------------

  # Check if a value in the list equals the value specified
  def itemAtEqual(index, value)

    # Check if index is in valid range
    if (index < 0 || index > @length)
      puts "ERROR: itemAtEqual(): Index '#{index}' is outside range of list 0...'#{@length}'.  Cannot add value"
      return
    end

    if @aList[index] == value
      return true
    end
    return false
  end

  # ---------------------------------------------------------------------------

  # Return the item at the specified index
  def getItemAtIndex(index)

    # Check if index is in valid range
    if (index < 0 || index > @length)
      puts "ERROR: itemAtEqual(): Index '#{index}' is outside range of list 0...'#{@length}'.  Cannot add value"
      return
    end

    return @aList[index]

  end

  # ---------------------------------------------------------------------------

  # Print the contents of the list
  def printList()

    puts "ARRAY LIST:\n"

    i = 0
    while i < @length
      print "#{@aList[i]}, "
      i+=1
      if i % 10 == 0 && i != 0
        puts ""
      end
    end
    puts ""

  end

end

# -----------------------------------------------------------------------------

# MAIN - Test functionality of the data structure

# Create a strict Integer array list
puts "INTEGER STRICT LIST\n"
intArrayList = ArrayList.new(10,true)

puts "Let's add '56' and '100' to the list"
intArrayList.insertAtEnd(56)
intArrayList.insertAtEnd(100)
intArrayList.printList()

puts "Let's add '99' to index 1 in the list.  Should work"
intArrayList.insertAtIndex(99,1)
intArrayList.printList()

puts "Let's try to add a non-Integer data type to the list.  Should fail"
intArrayList.insertAtEnd("DONT ADD!!!")

puts "Let's fill up the list"
intArrayList.insertAtEnd(1)
intArrayList.insertAtEnd(2)
intArrayList.insertAtEnd(3)
intArrayList.insertAtEnd(4)
intArrayList.insertAtEnd(5)
intArrayList.insertAtEnd(6)
intArrayList.insertAtEnd(7)
intArrayList.printList()

puts "Let's try to add one more item.  Should fail since list is full"
intArrayList.insertAtEnd(50)

puts "Then let's remove an item so we can make room"
intArrayList.removeAtIndex(4)
intArrayList.printList()

puts "Let's try to add one more item.  Should work since we made room"
intArrayList.insertAtEnd(50)
intArrayList.printList()

puts "Let's remove '100' from the list"
intArrayList.remove(100)
intArrayList.printList()

puts "Let's check if the value at index 0 is equal to 56"
puts intArrayList.itemAtEqual(0,56)

puts "Let's check if the value at index 0 is equal to 16"
puts intArrayList.itemAtEqual(0,16)

puts "Let's try to fetch something from the list"
puts intArrayList.getItemAtIndex(1)

# Create a non-strict list
puts "\nNON-STRICT LIST\n"
arrayList = ArrayList.new(10)
arrayList.insertAtEnd(1)
arrayList.insertAtEnd(3.14156)
arrayList.insertAtEnd("Hi There!")
arrayList.insertAtEnd(4)
arrayList.insertAtEnd(5)
arrayList.insertAtEnd(6)
arrayList.insertAtEnd("More nonsense")
arrayList.insertAtEnd(8.99923)
arrayList.insertAtEnd(7)
arrayList.insertAtEnd(8)
arrayList.printList()

puts "Let's try to insert another item into a full list"
arrayList.insertAtEnd("Uh Oh")

puts "Let's remove an item"
arrayList.remove("Hi There!")
arrayList.printList()
