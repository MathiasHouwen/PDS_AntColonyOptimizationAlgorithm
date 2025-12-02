# tsp_to_txt_matrix.py
import math
import sys

def read_tsp_file(file_path):
    coords = []
    with open(file_path, "r") as f:
        lines = f.readlines()

    reading_nodes = False
    for line in lines:
        line = line.strip()
        if line == "NODE_COORD_SECTION":
            reading_nodes = True
            continue
        if line == "EOF":
            break
        if reading_nodes:
            parts = line.split()
            if len(parts) >= 3:
                coords.append( (float(parts[1]), float(parts[2])) )
    return coords

def compute_distance_matrix(coords):
    n = len(coords)
    matrix = [[0]*n for _ in range(n)]
    for i in range(n):
        x1, y1 = coords[i]
        for j in range(n):
            if i == j:
                matrix[i][j] = 0
            else:
                x2, y2 = coords[j]
                # Rond af op int, zoals je voorbeeld
                matrix[i][j] = int(round(math.sqrt( (x1-x2)**2 + (y1-y2)**2 )))
    return matrix

def save_matrix(matrix, out_file):
    n = len(matrix)
    with open(out_file, "w") as f:
        f.write(f"{n}\n")
        for row in matrix:
            f.write(" ".join(str(x) for x in row) + "\n")

def main():
    tsp_file = "tsp.txt"
    out_file = "graph.txt"

    coords = read_tsp_file(tsp_file)
    matrix = compute_distance_matrix(coords)
    save_matrix(matrix, out_file)
    print(f"Distance matrix opgeslagen in {out_file}")

if __name__ == "__main__":
    main()

# input files kunnen gehaald worden van:
# https://github.com/mastqe/tsplib/tree/master

# één van die tsp files in de tsp.txt zetten en dan deze script runnen,
# hierna kan de main gerunt worden op deze test data