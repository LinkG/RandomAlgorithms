import copy
import re

class token():
    def __init__(self, argument, bse, tk):
        self.argument = argument
        self.bse = int(bse)
        self.func = tk;
        self.inproduct = []
    
    
    def multiply(self, token2):
        self.bse = self.bse * token2.bse
        token2.bse = 1
        self.inproduct.append(token2)
        
    
    def diff(self):
        if self.func == '^':
            if not isinstance(self.argument, token):
                self.bse = self.bse * int(self.argument)
                self.argument = str(int(self.argument) - 1)
        elif self.func == 'sin':
            self.func = 'cos'
            if isinstance(self.argument, token):
                t_new = copy.deepcopy(self.argument)
                t_new.diff()
                self.multiply(t_new)
        elif self.func == 'cos':
            self.bse = self.bse * -1;
            self.func = 'sin'
            if isinstance(self.argument, token):
                t_new = copy.deepcopy(self.argument)
                t_new.diff()
                self.multiply(t_new)
    
    
    def __str__(self):
        return self.getToken()
    
    
    def getToken(self):
        ret = ''
        if self.func == '^':
            if str(self.argument) == '0':
                return '1'
            if str(self.bse) != '1':
                if self.bse == -1:
                    ret = ret + '-'
                else:
                    ret = ret + str(self.bse)
            ret = ret + 'x'
            if self.argument != '1':
                ret = ret + '^'
                if isinstance(self.argument, token):
                    ret = ret + '(' + self.argument.getToken() + ')'
                else:
                    ret = ret + self.argument
        if self.func in ['sin', 'cos']:
            if self.bse != 1:
                if self.bse == -1:
                    ret = ret + '-'
                else:
                    ret = ret + str(self.bse)
            ret = ret + self.func + '(' + str(self.argument) + ')'
        for t in self.inproduct:
            if isinstance(t, token):
                te = t.getToken()
            if not te == '1':
                ret = ret + '.' + t.getToken()
        return ret
        

def parseToken(string):
    if string[0] == '(' and string[-1] == ')':
        string = string[1:len(string) - 1]
    bse = 0
    while 0 <= ord(string[bse]) - ord('0') <= 9 or string[bse] == '-':
        bse = bse + 1
        if bse == len(string):
            return string
    ch = bse
    bse = string[:ch]
    if bse == '':
        bse = '1'
    if bse == '-':
        bse = '-1'
    string = string[ch:]
    t = token('', '0', '')

    #Linear
    if string == 'x':
        t.func = '^'
        t.bse = int(bse)
        t.argument = '1'
        return t
    
    #Exponent
    rgx = re.compile(r'x?\((.*)\)?\^(.*)')
    out = rgx.finditer(string)
    for q in out:
        if q.start() == 0:
            t.func = '^'
            t.bse = int(bse)
            t.argument = parseToken(q.group(1))
            return t             
    
    #sin
    rgx = re.compile(r'sin\((.*)\)')
    out = rgx.finditer(string)
    for q in out:
        if q.start() == 0:
            t.func = 'sin'
            t.bse = int(bse)
            t.argument = parseToken(q.group(1))
            return t

    #cos
    rgx = re.compile(r'cos\((.*)\)')
    out = rgx.finditer(string)
    for q in out:
        if q.start() == 0:
            t.func = 'cos'
            t.bse = int(bse)
            t.argument = parseToken(q.group(1))
            return t


def product_multiple(tokens):
    answer = []
    for i in range(0, len(tokens)):
        current_t = copy.deepcopy(tokens[i])
        current_t.diff()
        for j in range(0, len(tokens)):
            if j == i:
                continue
            current_t.inproduct.append(copy.deepcopy(tokens[j]))
        answer.append(current_t)
    return answer
    
    

def main():
    string = 'sin(x).x^2'
    if 'x' not in string:
        print('0')
        return
    tokens_str = string.split('.')
    tokens_d = []
    for t in tokens_str:
        toke = parseToken(t)
        tokens_d.append(toke)
    ans = product_multiple(tokens_d)
    for i in range(0, len(ans)):
        t = ans[i].getToken()
        if i == len(ans) - 1:
            if t[0] != '-':
                print('+' + t)
            else:
                print(t)
            break
        if t[0] != '-':
            print('+' + t, end='')
        else:
            print(t, end='')
        
        
if __name__ == '__main__':
    main()
    