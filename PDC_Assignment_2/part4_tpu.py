import tensorflow as tf
import time

def readAndPerformMultiplication(filepath):
    with open(filepath, 'r') as file:
        lines = file.readlines()
        third_line = lines[2].strip()

    print(third_line)

    dimensions = list(map(int, third_line.split('X')))
    rows, col = dimensions
    matrix1 = []
    matrix2 = []
    with open(filepath, 'r') as file:
      
        count = 0
        for line in file:
            if count == 1 and third_line not in line.strip():
                matrix1.append(line.split(','))  
            elif third_line in line.strip():
                count += 1
            elif count == 2:
                matrix2.append(line.split(','))  

   
    matrix1 = [[float(val) for val in row] for row in matrix1]
    matrix2 = [[float(val) for val in row] for row in matrix2]

    a = tf.constant(matrix1, dtype=tf.float32)
    b = tf.constant(matrix2, dtype=tf.float32)

    start_time = time.time()  # Start time measurement
    result = tf.matmul(a, b)
    end_time = time.time()  # End time measurement


    print("Time taken:", end_time - start_time, "seconds")

readAndPerformMultiplication('./inputFIle.txt')
