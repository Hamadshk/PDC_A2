import numpy as np

def generate_matrix(dimensions, data_type):
    if data_type == 1:  
        return np.random.randint(-2147483648, 2147483647, dimensions, dtype=np.int32)
    elif data_type == 2:  
        return np.random.rand(*dimensions).astype(np.float32)
    elif data_type == 3:  
        return np.random.randint(-9223372036854775808, 9223372036854775807, dimensions, dtype=np.int64)
    elif data_type == 4:  
        return np.random.rand(*dimensions).astype(np.float64)
    else:
        raise ValueError("Invalid data type")

def insert_matrix_data(file_path, matrix_data, marker):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    # Find the line number where the marker occurs
    marker_line_number = lines.index(f"{marker}\n")

    # Move the cursor to the beginning of the file
    with open(file_path, 'w') as file:
        file.seek(0)

        file.writelines(lines[:marker_line_number + 1])

        file.seek(0, 2)  # Move to the end of the file
        file.seek(file.tell() - len(lines[marker_line_number]), 0)

        matrix_lines = [",".join(map(str, row)) + "\n" for row in matrix_data]
        file.writelines(matrix_lines)

        file.writelines(lines[marker_line_number + 1:])



def main():
    matrix_dimensions = (1024,1024)
    matrix_data_type = 1  

    matrix_data_1 = generate_matrix(matrix_dimensions, matrix_data_type)
    matrix_data_2 = generate_matrix(matrix_dimensions, matrix_data_type)


    insert_matrix_data('/home/hamad/Desktop/PDC_Assignment_2/inputFIle.txt', matrix_data_1, "//matrix data 1")
    insert_matrix_data('/home/hamad/Desktop/PDC_Assignment_2/inputFIle.txt', matrix_data_2, "//matrix data 2")

if __name__ == "__main__":
    main()
