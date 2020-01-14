class Node:
    def __init__(self):
        self.nxt = [-1] * 26
        self.end = False
        super().__init__()                
                

trie = [Node()] #root
outputs = {}
failure = []

def add_words(words):
    states = 1
    for word in words:
        current_state = 0
        for letter in word:
            ch = ord(letter) - ord('a')
            if trie[current_state].nxt[ch] == -1:
                trie[current_state].nxt[ch] = states
                trie.append(Node())
                states += 1
            current_state = trie[current_state].nxt[ch]
        trie[current_state].end = True
        outputs[current_state] = [word]
    for i in range(0, 26):
        if trie[0].nxt[i] == -1:
            trie[0].nxt[i] = 0
    failure.extend([-1] * states)             


def make_failures():
    q = []
    for i in range(0, 26):
        if trie[0].nxt[i] != 0:
            failure[trie[0].nxt[i]] = 0
            q.append(trie[0].nxt[i])
    
    while len(q) > 0:
        current = q.pop(0)
        for i in range(0, 26):
            if trie[current].nxt[i] != -1:
                fail = failure[current]
                
                while trie[fail].nxt[i] == -1:
                    fail = failure[fail]
                
                fail = trie[fail].nxt[i]
                failure[trie[current].nxt[i]] = fail
                if fail in outputs.keys():
                    if trie[current].nxt[i] not in outputs.keys():
                        outputs[trie[current].nxt[i]] = []
                    outputs[trie[current].nxt[i]].extend(outputs[fail])
                    trie[trie[current].nxt[i]].end = True
                q.append(trie[current].nxt[i])
    

def get_next_state(cur_state, letter):
    ch = ord(letter) - ord('a')
    next_state = cur_state
    
    while trie[next_state].nxt[ch] == -1:
        next_state = failure[next_state]
    
    return trie[next_state].nxt[ch]


def main():
    dic = [x for x in input().split(' ')]
    text = input()
    add_words(dic)
    make_failures()
    locations = {}
    current_state = 0
    for i in range(0, len(text)):
        current_state = get_next_state(current_state, text[i])
        if trie[current_state].end == True:
            for wrd  in outputs[current_state]:
                if wrd not in locations.keys():
                    locations[wrd] = []
                locations[wrd].append(i - len(wrd) + 1)
    
    for k in locations.keys():
        print('Found {} -> {}'.format(k, locations[k]))
        
    

if __name__ == '__main__':
    main()
    