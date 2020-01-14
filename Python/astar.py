from colorama import Fore, Back, Style

class Node:
    def __init__(self, p1, p2):
        self.pos = p2
        self.parent = p1
        self.gscore = 0
        self.fscore = 0
        super().__init__()


def check_list(list, node):
    for i in range(0, len(list)):
        n = list[i]
        if n.pos == node.pos:
            if n.fscore < node.fscore:
                return -1
            else:
                return i
    return len(list)


def get_dist(t1, t2):
    return abs(t1[0] - t2[0]) + abs(t1[1] - t2[1])


def main():
    r,c = [int(x) for x in input().split(' ')]
    lines = []
    scoremap = []
    for i in range(0, r):
        lines.append(input())
        for j in range(0, c):
            if lines[i][j] == 'S':
                start = Node(0, (i, j))
            elif lines[i][j] == 'E':
                end = i, j
    ol = [start]
    cl = []
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    while len(ol) > 0:
        current = ol.pop(ol.index(min(ol, key=lambda t: t.fscore)))
        if current.pos == end:
                print('Done')
                break
        position = current.pos
        for dir in directions:
            if (position[0] + dir[0] >= r) or (position[0] + dir[0] < 0) or (position[1] + dir[1] >= c) or (position[1] + dir[1] < 0):
                continue
            succ_pos = position[0] + dir[0], position[1] + dir[1]
            if lines[succ_pos[0]][succ_pos[1]] == 'B':
                continue
            succ_h = get_dist(succ_pos, end)
            succ = Node(current, succ_pos)
            succ.gscore = current.gscore + 1
            succ.fscore = succ.gscore + succ_h
            decider = check_list(ol, succ), check_list(cl, succ)
            if decider[0] == -1 or decider[1] == -1:
                continue
            elif decider[0] == len(ol):
                ol.append(succ)
            else:
                ol.pop(decider[0])
                ol.append(succ)
            cl.append(current)
    
    if current.pos == end:
        link = current.parent
        path = []
        while link != 0:
            path.append(link.pos)
            link = link.parent
        start_pos = path.pop()    
        for i in range(0, r):
            for j in range(0, c):
                if lines[i][j] == '.':
                    print(Back.WHITE + ' ' + Back.RESET, end='')
                elif (i, j) == start_pos:
                    print(Back.GREEN + ' ' + Back.RESET, end='')
                elif lines[i][j] == 'E':
                    print(Back.RED + ' ' + Back.RESET, end='')
                else:
                    print(Back.BLACK + ' ' + Back.RESET, end='')
                    
            print('')
        print('\n\n')
        for i in range(0, r):
            for j in range(0, c):
                if (i, j) in path:
                    print(Back.BLUE + ' ' + Back.RESET, end='')
                elif lines[i][j] == '.':
                    print(Back.WHITE + ' ' + Back.RESET, end='')
                elif (i, j) == start_pos:
                    print(Back.GREEN + ' ' + Back.RESET, end='')
                elif lines[i][j] == 'E':
                    print(Back.RED + ' ' + Back.RESET, end='')
                else:
                    print(Back.BLACK + ' ' + Back.RESET, end='')
                    
            print('')
        print(len(path))
    else:
        print('No path')
if __name__ == '__main__':
    main()    