arr = [] 
  
# number of elemetns as input 
n = int(input("Enter number of elements : ")) 
  
# iterating till the range 
for i in range(0, n): 
    ele = int(input()) 
    arr.append(ele) # adding the element 
print(arr) 
#arr = [-5, -10,-10,0,-5, 6, 0, -3, 8, 5, -1, 10] 
arr2 = [10 ,-30 ,4]

max_element = int(max(arr)) 
min_element = int(min(arr)) 
range_of_elements = max_element - min_element + 1
    
count_arr = [0 for _ in range(range_of_elements)]
print("initial count array") 
print(count_arr)
output_arr = [0 for _ in range(len(arr))] 
print("initial output array")
print(output_arr)
    # Store count of each character 
for i in range(0, len(arr)): 
    a = arr[i]-min_element
    count_arr[a] += 1
print("Count array after find element")
print(count_arr)  
  
for i in range(1, len(count_arr)): 
    count_arr[i] += count_arr[i-1] 
print("count array after cumultive frequency")
print(count_arr)
    # Build the output character array 
for i in range(len(arr)-1, -1, -1): 
    a = arr[i] - min_element
    output_arr[count_arr[a] - 1] = arr[i]
    count_arr[a] -= 1
    #output_arr[count_arr[a] - 1] = arr[i] 
print(count_arr)
print(output_arr)

for i in range(0, len(arr)): 
    arr[i] = output_arr[i] 
  
print("Sorted character array is " + str(arr)) 