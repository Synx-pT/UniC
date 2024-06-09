
def ggt(x, y):
    tempx: int = 0
    compare: int = 0
    x: int
    y: int

    while True:
        if y - 1 < 0:
            return x

        compare = x - y
        tempx = x

        if compare < 0:
            x = y
            y = tempx

        print(x, y)

        x = x - y


print(ggt(10, 4))


# def ggt(x, y):
#     # Calculating the greatest common divider
#     while True:

#         # tempx = x

#         # comp = x - y

#         # # Wenn das wahr ist, ist y größer.
#         # if comp < 0:
#         #     # Deshalb werden hier x, y vertauscht, sodass x größer ist.
#         #     x, y = y, x

#         # print(x, y)

#         # # Return Condition
#         # if (x - (y + 1)) < 0:
#         #     return x

#         # #
#         # if x > 0:
#         #     y = tempx

#         tempx = x

#         print(x, y)

#         if y == 0:
#             return tempx

#         x = max(x, y) - min(x, y)
#         y = min(x, y)


# print(ggt(10, 5))
