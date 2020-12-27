import math

DEFAULT_BUCKET_SIZE = 5

def insertionSort(b): 
    for i in range(1, len(b)): 
        up = b[i] 
        j = i - 1
        while j >= 0 and b[j] > up:  
            b[j + 1] = b[j] 
            j -= 1
        b[j + 1] = up      

  
myList = [] 
  
# number of elemetns as input 
n = int(input("Enter number of elements : ")) 
  
# iterating till the range 
for i in range(0, n): 
    ele = float(input()) 
  
    myList.append(ele) 
print("Original Array")
print(myList)

minValue = myList[0]
maxValue = myList[0]
bucketSize = DEFAULT_BUCKET_SIZE
    # For finding minimum and maximum values
for i in range(0, len(myList)):
    if myList[i] < minValue:
        minValue = myList[i]
    elif myList[i] > maxValue:
        maxValue = myList[i]
print("Max value")
print(maxValue)
print("min value")
print(minValue)
    # Initialize buckets
bucketCount = math.floor((maxValue - minValue) / bucketSize) + 1
print(bucketCount)
buckets = []
for i in range(0, bucketCount):
    buckets.append([])

    # For putting values in buckets
for i in range(0, len(myList)):
    #print((myList[i] - minValue) / bucketSize)
    buckets[math.floor((myList[i] - minValue) / bucketSize)].append(myList[i])
print(buckets)
    # Sort buckets and place back into input array
sortedArray = []
for i in range(0, len(buckets)):
    insertionSort(buckets[i])
    for j in range(0, len(buckets[i])):
        sortedArray.append(buckets[i][j])


print(sortedArray)