def testFunc(numCols: int, numRows: int, e: int) -> list[int, int]:
    row = e // numCols

    if e % numCols == 0 & e != 0:
        col -= 1

    col = ((e - (row * numCols)))

    return [row + 1, col + 1]


